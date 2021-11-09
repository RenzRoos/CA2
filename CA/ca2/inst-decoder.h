/* rv64-emu -- Simple 64-bit RISC-V simulator
 *
 *    inst-decoder.h - RISC-V instruction decoder.
 *
 * Copyright (C) 2016,2019  Leiden University, The Netherlands.
 */

#ifndef __INST_DECODER_H__
#define __INST_DECODER_H__

#include "reg-file.h"

#include <stdexcept>
#include <cstdint>

const uint32_t R1 = 47;
const uint32_t R2 = 51;
const uint32_t R3 = 59;

const uint32_t I1 = 3;
const uint32_t I2 = 15;
const uint32_t I3 = 19;
const uint32_t I4 = 103;
const uint32_t I5 = 115;

const uint32_t S = 35;

const uint32_t B = 99;

const uint32_t U1 = 23;
const uint32_t U2 = 55;

const uint32_t J = 111;

/* TODO: add enums and constants necessary for your instruction decoder. */
enum Type{
  R_type, 
  I_type, 
  S_type, 
  B_type, 
  U_type, 
  J_type
};

/* Exception that should be thrown when an illegal instruction
 * is encountered.
 */
class IllegalInstruction : public std::runtime_error
{
  public:
    explicit IllegalInstruction(const std::string &what)
      : std::runtime_error(what)
    { }

    explicit IllegalInstruction(const char *what)
      : std::runtime_error(what)
    { }
};


/* InstructionDecoder component to be used by class Processor */
class InstructionDecoder
{
  public:
    void                setInstructionWord(const uint32_t instructionWord);
    uint32_t            getInstructionWord() const;

    RegNumber           getRS1() const;
    RegNumber           getRS2() const;
    RegNumber           getRD() const;
    RegNumber           getFunc3() const;
    RegNumber           getFunc7() const;
    RegNumber           getImm_I_U_J() const;
    RegNumber           getImm1_S_B() const;
    RegNumber           getImm2_S_B() const;
    RegNumber           getOpcode();

    void                setType(const uint32_t inst_typing);
    RegNumber           getType() const;
    /* TODO: probably want methods to get opcode, function code */

    /* TODO: need a method to obtain the immediate */

  private:
    uint32_t instructionWord;
    Type type;
};

std::ostream &operator<<(std::ostream &os, const InstructionDecoder &decoder);

#endif /* __INST_DECODER_H__ */
