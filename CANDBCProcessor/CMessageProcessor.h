#pragma once
#include "CMessageTemplate.h"

class CMessageProcessor
{
public:
  virtual void ProcessMessage( CMessageTemplate& message, const uint64_t& msg , size_t msgSize ) = 0;

protected:
  uint64_t ReverseBytes( uint64_t canData);
};