#pragma once
#include "MessageDeserializerData.h"

class IMessageProcessor
{
public:
  virtual void ProcessMessage( const unsigned int msgId, tSignalList& signals, const uint64_t& msg , size_t msgSize ) = 0;
};