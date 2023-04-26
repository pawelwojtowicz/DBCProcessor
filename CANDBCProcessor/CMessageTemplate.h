#pragma once
#include "CMessage.h"

#define MULTIPLEXERID 0
#define SIGNAL 1
#define VALUE 2
#define LISTENERS 3


class CMessageTemplate : public CMessage
{
public:
  using tSignalListeners = std::list<ISignalListener*>;
  using tSignalTuple = std::tuple<int,CSignal, CSignalValueTemplate, tSignalListeners>;
  using tSignalList = std::list<tSignalTuple>;

  CMessageTemplate(const unsigned int msgId, const std::string& name, size_t msgSize, const std::string& sender);
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
  void SetMessageId( const unsigned int msgId );
  void SetPGN( const unsigned int pgn);
  void SetRawData( const uint64_t& rawData);
  void BuildDefaultValueMap();

  bool IsMultiplexedMessage() const;

  bool SubscribeCANSignal( const std::string& signalName, ISignalListener& signalListener);

  const tSignalList& GetMessageSignals() const;
  tSignalList& GetMessageSignals();
private:
  tSignalList m_signals;
};