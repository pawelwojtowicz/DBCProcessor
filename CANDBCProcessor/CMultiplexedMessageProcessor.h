#pragma once
#include "IMessageProcessor.h"

class CMultiplexedMessageProcessor : public IMessageProcessor
{
public:
  void ProcessMessage( CMessageTemplate& message, const uint64_t& msg , size_t msgSize ) override;
};