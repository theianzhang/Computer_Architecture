#ifndef _FORMAT_H
#define _FORMAT_H

enum instruction_type {I,IBranch,I1Branch,I1,IDisp,J,R,R0,R1RS,R1RT,RSH};
struct instruction_t
{
  unsigned short opcode;
  const char* str;
  instruction_type type;
  instruction_t() { str = 0; }
  instruction_t(unsigned short o, const char* s, instruction_type t) { opcode = o; str = s; type = t; }
};

#define OPCODE_ADD 0x1
#define OPCODE_LDI 0x2
#define OPCODE_SUB 0x3
#define OPCODE_AND 0x4
#define OPCODE_XOR 0x5
#define OPCODE_ROTL 0x6
#define OPCODE_ROTR 0x7
#define OPCODE_LW 0x8
#define OPCODE_SW 0x9
#define OPCODE_BNEZ 0xA
#define OPCODE_J 0xB
#define OPCODE_RET 0xC
#define OPCODE_JAL 0xD
#define OPCODE_INPUT 0xE
#define OPCODE_OUTPUT 0xF

instruction_t opcode_arr[] = {
instruction_t(OPCODE_ADD,"add",R),
instruction_t(OPCODE_LDI,"ldi",I1),
instruction_t(OPCODE_SUB,"sub",R),
instruction_t(OPCODE_AND,"and",R),
instruction_t(OPCODE_XOR,"xor",R),
instruction_t(OPCODE_ROTL,"rotl",RSH),
instruction_t(OPCODE_ROTR,"rotr",RSH),
instruction_t(OPCODE_LW,"lw",IDisp),
instruction_t(OPCODE_SW,"sw",IDisp),
instruction_t(OPCODE_BNEZ,"bnez",I1Branch),
instruction_t(OPCODE_J,"j",J),
instruction_t(OPCODE_RET,"ret",R0),
instruction_t(OPCODE_JAL,"jal",J),
instruction_t(OPCODE_OUTPUT,"output",R1RS),
instruction_t(OPCODE_INPUT,"input",R1RT)
};

const int NUM_OPCODES = sizeof(opcode_arr)/sizeof(instruction_t);
const int OPCODE_BITS = 4;
const int REG_BITS = 3;
const int SHIFT_AMT_BITS = 3;
const int IMM_BITS = 6;
const int JMP_ADDR_BITS = 12;
const int ADDR_BITS = 16;
const int WORD_BITS = 16;

const int IMEM_SIZE = 8192;
const int DMEM_SIZE = 16384;

const int LINK_REG = 7;
const int ZERO_REG = 0;
const int DATA_BASE_ADDR_REG = 6;
const int DATA_BASE_ADDR = 16384;

const int WIDTH = WORD_BITS;
const int DEPTH = 1<<ADDR_BITS;
const int NUM_REGS = 1<<REG_BITS;
const int MIN_IMM = -(1<<(IMM_BITS-1));
const int MAX_IMM = (1<<(IMM_BITS-1))-1;
const int MAX_JMP_ADDR = (1<<JMP_ADDR_BITS)-1;
const int MAX_SHIFT_AMT = (1<<SHIFT_AMT_BITS)-1;

struct type_i
{
  signed imm : IMM_BITS;
  unsigned rt : REG_BITS;
  unsigned rs : REG_BITS;
  unsigned opcode : OPCODE_BITS;
};

struct type_r
{
  unsigned shamt : SHIFT_AMT_BITS;
  unsigned rd : REG_BITS;
  unsigned rt : REG_BITS;
  unsigned rs : REG_BITS;
  unsigned opcode : OPCODE_BITS;
};

struct type_j
{
  unsigned addr : JMP_ADDR_BITS;
  unsigned opcode : OPCODE_BITS;
};

union inst
{
  type_i itype;
  type_r rtype;
  type_j jtype;
  unsigned short bits;
};

#endif
