#pragma once
#include "CMessage.h"

class IMessageListener
{
public:
  virtual void NotifyMessageReceived( const CMessage& message) = 0;
};