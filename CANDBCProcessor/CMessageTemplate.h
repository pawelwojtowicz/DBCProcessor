#pragma once
#include "CMessage.h"

class CMessageTemplate : public CMessage
{
  using tSignalListeners = std::list<ISignalListener*>;
  using tSignalTuple = std::tuple<int,CSignal, CSignalValueTemplate, tSignalListeners>;
  using tSignalList = std::list<tSignalTuple>;

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
  void AddMessageProperty( const std::string& name, const std::string& value);

  bool SubscribeCANSignal( const std::string& signalName, ISignalListener& signalListener);
  void ProcessMessage( const uint64_t& msg , size_t msgSize );
private:
  tSignalList m_signals;
  tSignalList::iterator m_multiplexingSignal;
};