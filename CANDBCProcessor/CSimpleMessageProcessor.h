#pragma once
#include "IMessageProcessor.h"

class CSimpleMessageProcessor : public IMessageProcessor
{
public:
  void ProcessMessage( const unsigned int msgId, tSignalList& signals, const uint64_t& msg , size_t msgSize );
};