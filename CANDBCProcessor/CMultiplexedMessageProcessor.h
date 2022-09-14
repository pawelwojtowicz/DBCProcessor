#pragma once
#include "CMessageProcessor.h"

class CMultiplexedMessageProcessor : public CMessageProcessor
{
public:
  void ProcessMessage( CMessageTemplate& message, const uint64_t& msg , size_t msgSize ) override;
};