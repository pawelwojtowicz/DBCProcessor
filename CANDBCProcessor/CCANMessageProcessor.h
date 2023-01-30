#pragma once
#include "DBCInfo.h"
#include <vector>
#include <memory>
#include "ILogger.h"

class ISignalListenerl;

class CCANMessageProcessor
{
public:
  void Initialize( const std::string& dbcFilePath , std::shared_ptr<Logger::ILogger> pLogger = {} );
  void Initialize(  const std::vector<std::string>& dbcList, std::shared_ptr<Logger::ILogger> pLogger = {}  );
  void Shutdown();

  const std::string& GetDBCVersion() const;

  const CMessage& ProcessMessage( const unsigned int msgId, const uint64_t& data);
  const CMessage& ProcessMessageByPGN( const unsigned int pgn, const uint64_t& data);

  bool DispatchCANSignal( const unsigned int, const uint64_t& data);
  bool DispatchCANSignalByPGN( const unsigned int, const uint64_t& data);


  bool SubscribeCANSignal( const unsigned int msgId, const std::string& signalName, ISignalListener& listener );
  bool SubscribeCANSignalByPGN( const unsigned int msgId, const std::string& signalName, ISignalListener& listener );
  void SubscribeAllMessages( IMessageListener& listener );
  bool SubscribeCANMessage( const unsigned int msgId, IMessageListener& listener);

  const std::string& GetProperty( const std::string& propertyName);
  const std::string& GetPropertyType( const std::string& propertyType);

private:
  uint64_t ReverseBytes( uint64_t canData);

private:
  DBCInfo m_dbcInfo;

private:
  std::shared_ptr<Logger::ILogger> m_pLogger;
};