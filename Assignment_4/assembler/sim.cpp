#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <cstdlib>
#include <cstring>
#include "format.h"

#ifdef __linux__
  #include <termios.h>
#endif

using namespace std;

const int MEM_SIZE = DEPTH;
unsigned short reg[NUM_REGS];
unsigned short mem[MEM_SIZE];

void usage() { exit(-1); }
string insn2str(inst insn);

int main(int argc, char** argv)
{
  bool verbose = false, insncount = false;
  string input_filename;
  for(int i = 1; i < argc; i++)
  {
    if(strcmp(argv[i],"-v") == 0)
      verbose = insncount = true;
    else if(strcmp(argv[i],"-n") == 0)
      insncount = true;
    else if(input_filename == "")
      input_filename = argv[i];
    else
      usage();
  }

  if(input_filename == "")
    usage();

  ifstream infile(input_filename.c_str());
  if(!infile)
  {
    cerr << "Could not open " << input_filename << endl;
    return -1;
  }

  string line;
  bool started = false;
  int lineno = 0;
  while(getline(infile,line))
  {
    lineno++;
    int addr, insn;
    char ch;

    istringstream in(line);

    if(line.length() == 0)
      continue;

    if(line.substr(0,3) == "END")
      break;

    if(!started)
    {
      if(line == "CONTENT BEGIN;")
        started = true;
      continue;
    }

    if(!(in >> hex >> addr))
    {
      cerr << "Syntax error on line " << lineno << endl;
      return -1;
    }

    if(addr < 0 || addr >= MEM_SIZE)
    {
      cerr << "Memory address out of bounds on line " << lineno << ": " << hex << addr << endl;
      return -1;
    }

    if(!(in >> ch) || ch != ':')
    {
      cerr << "Syntax error on line " << lineno << endl;
      return -1;
    }

    if(!(in >> hex >> insn))
    {
      cerr << "Syntax error on line " << lineno << endl;
      return -1;
    }

    if(!(in >> ch) || ch != ';')
    {
      cerr << "Syntax error on line " << lineno << endl;
      return -1;
    }

    mem[addr] = insn;
  }

  #ifdef __linux__
    termios old_termios_settings,new_termios_settings;
    tcgetattr(0,&old_termios_settings);
    new_termios_settings = old_termios_settings;
    new_termios_settings.c_lflag &= (~ICANON);
    new_termios_settings.c_lflag &= (~ECHO);
    new_termios_settings.c_cc[VTIME] = 0;
    new_termios_settings.c_cc[VMIN] = 1;
    tcsetattr(0,TCSANOW,&new_termios_settings);
  #endif

  long long count = 0;
  int pc = 0;
  bool quit = false;
  while(!quit)
  {
    inst insn;
    insn.bits = mem[pc];

    if(verbose)
    {
      cout << hex << setw((ADDR_BITS+3)/4) << setfill('0') << pc << ' ' << setw((ADDR_BITS+3)/4) << setfill('0') << insn.bits << dec;
      cout << ' ' << insn2str(insn) << endl;
    }

    pc++;
    count++;

    reg[ZERO_REG] = 0;
    reg[DATA_BASE_ADDR_REG] = DATA_BASE_ADDR;

    switch(insn.itype.opcode)
    {
      case OPCODE_ADD:
        reg[insn.rtype.rd] = reg[insn.rtype.rs] + reg[insn.rtype.rt];
        break;
      case OPCODE_LDI:
        reg[insn.itype.rt] = insn.itype.imm;
        break;
      case OPCODE_SUB:
        reg[insn.rtype.rd] = reg[insn.rtype.rs] - reg[insn.rtype.rt];
        break;
      case OPCODE_AND:
        reg[insn.rtype.rd] = reg[insn.rtype.rs] & reg[insn.rtype.rt];
        break;
      case OPCODE_XOR:
        reg[insn.rtype.rd] = reg[insn.rtype.rs] ^ reg[insn.rtype.rt];
        break;
      case OPCODE_ROTL:
        reg[insn.rtype.rd] = (reg[insn.rtype.rs] << insn.rtype.shamt) | (reg[insn.rtype.rs] >> (WORD_BITS-insn.rtype.shamt));
        break;
      case OPCODE_ROTR:
        reg[insn.rtype.rd] = (reg[insn.rtype.rs] >> insn.rtype.shamt) | (reg[insn.rtype.rs] << (WORD_BITS-insn.rtype.shamt));
        break;
      case OPCODE_LW:
        reg[insn.itype.rt] = mem[reg[insn.itype.rs] + insn.itype.imm];
        break;
      case OPCODE_SW:
        mem[reg[insn.itype.rs] + insn.itype.imm] = reg[insn.itype.rt];
        break;
      case OPCODE_BNEZ:
        if(insn.itype.rs == DATA_BASE_ADDR_REG && insn.itype.imm == -1)
        {
          if(insncount)
            cerr << dec << count << " dynamic instructions executed" << endl;
          quit = true;
          break;
        }
        if(reg[insn.itype.rs] != 0)
          pc += insn.itype.imm;
        break;
      case OPCODE_J:
        pc = (pc & ~MAX_JMP_ADDR) | insn.jtype.addr;
        break;
      case OPCODE_RET:
        pc = reg[LINK_REG];
        break;
      case OPCODE_JAL:
        reg[LINK_REG] = pc;
        pc = (pc & ~MAX_JMP_ADDR) | insn.jtype.addr;
        break;
      case OPCODE_OUTPUT:
        cout << (reg[insn.rtype.rs] == 0xD ? '\n' : (char)reg[insn.rtype.rs]);
        break;
      case OPCODE_INPUT:
        reg[insn.rtype.rt] = getchar();
        break;
      default:
        cerr << "Invalid opcode " << hex << insn.itype.opcode << " at pc " << pc-1 << "!" << endl;
        quit = true;
        break;
    }

    if(verbose)
    {
      for(int i = 0; i < NUM_REGS; i++)
        cout << hex << setw((WORD_BITS+3)/4) << setfill('0') << reg[i] << dec << ' ';
      cout << endl;
    }
  }

  #ifdef __linux__
    tcsetattr(0,TCSANOW,&old_termios_settings);
  #endif
}

string insn2str(inst insn)
{
  int index = 0;
  for(int i = 0; i < NUM_OPCODES; i++)
    if(opcode_arr[i].opcode == insn.itype.opcode)
      index = i;

  ostringstream oss;
  oss << opcode_arr[index].str;
  switch(opcode_arr[index].type)
  {
    case I:
    case IBranch:
      oss << " $r" << insn.itype.rs << ",$r" << insn.itype.rt << ',' << (short)insn.itype.imm;
      break;
    case I1Branch:
      oss << " $r" << insn.itype.rs << ',' << (short)insn.itype.imm;
      break;
    case I1:
      oss << " $r" << insn.itype.rt << ',' << (short)insn.itype.imm;
      break;
    case IDisp:
      oss << " $r" << insn.itype.rt << ',' << (short)insn.itype.imm << "($r" << insn.itype.rs << ')';
      break;
    case J:
      oss << ' ' << insn.jtype.addr;
      break;
    case R:
      oss << " $r" << insn.rtype.rd << ",$r" << insn.rtype.rs << ",$r" << insn.rtype.rt;
      break;
    case R0:
      break;
    case R1RS:
      oss << " $r" << insn.rtype.rs;
      break;
    case R1RT:
      oss << " $r" << insn.rtype.rt;
      break;
    case RSH:
      oss << " $r" << insn.rtype.rd << ",$r" << insn.itype.rs << ',' << (short)insn.rtype.shamt;
      break;
    default:
      break;
  }

  return oss.str();
}
