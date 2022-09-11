#pragma once

class CValue;

class ISignalListener
{
public:
  ISignalListener() = default;
  virtual ~ISignalListener() = default;

  virtual void NotifySignalReceived( const unsigned int msgId, const CValue& value ) = 0;
};