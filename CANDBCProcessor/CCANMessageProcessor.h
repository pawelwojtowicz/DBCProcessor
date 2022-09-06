#pragma once
#include "DBCInfo.h"
#include <vector>

class ISignalListenerl;

class CCANMessageProcessor
{
public:
  void Initialize(  const std::vector<std::string>& dbcList );
  void Shutdown();

  const std::string& GetDBCVersion() const;

  bool DispatchCANSignal( const unsigned int, const uint64_t& data);
  bool DispatchCANSignalByPGN( const unsigned int, const uint64_t& data);

  bool SubscribeCANSignal( const unsigned int msgId, const std::string& signalName, ISignalListener& listener );
  void SubscribeAllMessages( IMessageListener& listener );
  bool SubscribeCANMessage( const unsigned int msgId, IMessageListener& listener);

  const std::string& GetProperty( const std::string& propertyName);
  const std::string& GetPropertyType( const std::string& propertyType);

private:
  DBCInfo m_dbcInfo;
};