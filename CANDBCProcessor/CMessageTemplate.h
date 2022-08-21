#pragma once
#include "CMessage.h"

class CMessageTemplate : public CMessage
{
public:
  CMessageTemplate(const std::string& name, size_t msgSize, const std::string& sender);
  virtual ~CMessageTemplate();

  void AddSignal( const std::string& name,
                  const unsigned int bitStart,
                  const size_t size,
                  const CSignal::eEndiannes endiannes,
                  const tSignalValueProperties& tValueProperties,
                  const std::string& unit,
                  const std::string& receiver);
                  
  void AddMultiplexedSignal(  const std::string& name,
                              const int multiplexId,
                              const unsigned int bitStart,
                              const size_t size,
                              const CSignal::eEndiannes endiannes,
                              const tSignalValueProperties& tValueProperties,
                              const std::string& unit,
                              const std::string& receiver);

  void SetDescription( const std::string& description );
  void SetSignalDescription( const std::string& signalName , const std::string& description);
  void SetSignalProperty( const std::string& signalName, const std::string& propertyName, const std::string& propertyValue);
  void AddMessageProperty( const std::string& name, const std::string& value);

  bool SubscribeCANSignal( const std::string& signalName, ISignalListener& signalListener);
  void ProcessMessage( const uint64_t& msg , size_t msgSize );
};