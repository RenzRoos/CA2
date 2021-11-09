/* rv64-emu -- Simple 64-bit RISC-V simulator
 *
 *    inst-decoder.cc - RISC-V instruction decoder.
 *
 * Copyright (C) 2016,2019  Leiden University, The Netherlands.
 *
 */

#include "inst-decoder.h"

#include <functional>
#include <map>


/*
 * Class InstructionDecoder -- helper class for getting specific
 * information from the decoded instruction.
 */

void
InstructionDecoder::setInstructionWord(const uint32_t instructionWord)
{
  this->instructionWord = instructionWord;
}

uint32_t
InstructionDecoder::getInstructionWord() const
{
  return instructionWord;
}

RegNumber
InstructionDecoder::getRS1() const
{
  if(type == R_type || type == I_type || type == S_type || type == B_type){
    return (instructionWord & 0xf8000); 
  }
  return 0;  /* result undefined */
}

RegNumber
InstructionDecoder::getRS2() const
{
  if(type == R_type || type == S_type || type == B_type){
    return (instructionWord & 0x1f00000); 
  }
  return 0;  /* result undefined */
}

RegNumber
InstructionDecoder::getRD() const
{
  if(type == R_type || type == I_type || type == U_type || type == J_type){
    return (instructionWord & 0xf80); 
  }
  return 0; /* result undefined */
}

RegNumber
InstructionDecoder::getFunc3() const
{
  if(type == R_type || type == I_type || type == S_type || type == B_type){
    return (instructionWord & 0x7000); 
  }
  return 0;
}

RegNumber
InstructionDecoder::getFunc7() const
{
  if(type == R_type){
    return (instructionWord & 0xfe000000); 
  }
  
  return 0;
}

RegNumber
InstructionDecoder::getImm_I_U_J() const
{
  if(type == I_type){
    return (instructionWord & 0xfff0000000); 
  }
  else if(type == U_type || type == J_type){
    return (instructionWord & 0xfffffff000); 
  }
  
  return 0;
}


RegNumber
InstructionDecoder::getImm1_S_B() const
{
  if(type == S_type || type == B_type){
    return (instructionWord & 0xfe00000000); 
  }
  
  return 0;
}

RegNumber
InstructionDecoder::getImm2_S_B() const
{
  if(type == S_type || type == B_type){
    return (instructionWord & 0xf80); 
  }
  
  return 0;
}

void
InstructionDecoder::setType(const uint32_t inst_typing){

  switch (inst_typing)
  {
    case R1:
    case R2:
    case R3:
      this->type = R_type;
      break;
    case I1:
    case I2:
    case I3:
    case I4:
    case I5:
      this->type = I_type;
      break;
    case S:
      this->type = S_type;
      break;
    case B:
      this->type = B_type;
      break;
    case U1:
    case U2:
      this->type = U_type;
      break;
    case J:
      this->type = J_type;
      break;
  default:
    break;
  }
} 

RegNumber
InstructionDecoder::getType() const
{
  return this->type; 
}


RegNumber
InstructionDecoder::getOpcode() 
{
  setType(instructionWord & 0x7f);
  return (instructionWord & 0x7f); 

}


