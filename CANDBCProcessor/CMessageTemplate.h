#pragma once
#include "MessageDeserializerData.h"
#include "IMessageProcessor.h"
#include "CMessage.h"

class CMessageTemplate : public CMessage
{
public:
  CMessageTemplate(const int msgId, const std::string& name, size_t msgSize, const std::string& sender);
  virtual ~CMessageTemplate();
                  
  void AddSignal( const std::string& name,
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
  void SetSignalValueDictonary( const std::string& signalName, const std::string& initializerString);
  void SetMessageProcessor( std::shared_ptr<IMessageProcessor> msgProcessor );
  void AddMessageProperty( const std::string& name, const std::string& value);
  void BuildDefaultValueMap();

  bool IsMultiplexedMessage();

  bool SubscribeCANSignal( const std::string& signalName, ISignalListener& signalListener);
  void ProcessMessage( const uint64_t& msg , size_t msgSize );
private:
  std::shared_ptr<IMessageProcessor> m_messageProcessor;
  tSignalList m_signals;
};