#pragma once
#include "CMessageTemplate.h"

class IMessageProcessor
{
public:
  virtual void ProcessMessage( CMessageTemplate& message, const uint64_t& msg , size_t msgSize ) = 0;
};