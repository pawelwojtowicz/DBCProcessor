#include "CCANMessageProcessor.h"
#include "CDBCInfoBuilder.h"
#include "ISignalListener.h"
#include "DBCProcessor.h"

#include <iostream>

const std::string& CCANMessageProcessor::GetDBCVersion() const
{
  return m_dbcInfo.dbcVersion;
}


void CCANMessageProcessor::Initialize(  const std::vector<std::string>& dbcList )
{
  CDBCInfoBuilder dbcBuilder(m_dbcInfo);
  dbcBuilder.BuildDBCInfo(dbcList);
}

void CCANMessageProcessor::Shutdown()
{

}

bool CCANMessageProcessor::DispatchCANSignal( const unsigned int msgId, const uint64_t& data)
{
  const auto messageIter = m_dbcInfo.msgId2message.find( msgId );
  if (m_dbcInfo.msgId2message.end() != messageIter )
  {
    std::get<MESSAGE>(messageIter->second)->ProcessMessage(data,8);

    auto specificMessageListeners = std::get<MSG_LISTENERS>(messageIter->second);
    for (auto& listener: specificMessageListeners)
    {
      listener->NotifyMessageReceived(*(std::get<MESSAGE>(messageIter->second)));
    }

    for ( auto& listener: m_dbcInfo.allMessageListeners)
    {
      listener->NotifyMessageReceived(*(std::get<MESSAGE>(messageIter->second)));
    }

    return true;
  }

  return false;
}

bool CCANMessageProcessor::DispatchCANSignalByPGN( const unsigned int msgId, const uint64_t& data)
{
  const auto messageIter = m_dbcInfo.pgn2message.find( GET_PGN(msgId) );
  if (m_dbcInfo.pgn2message.end() != messageIter )
  {
    std::get<MESSAGE>(messageIter->second)->ProcessMessage(data,8);
    return true;
  }

  return false;
}

bool CCANMessageProcessor::SubscribeCANSignal( const unsigned int msgId, const std::string& signalName, ISignalListener& listener )
{
  const auto messageIter = m_dbcInfo.msgId2message.find( msgId );

  if (m_dbcInfo.msgId2message.end() != messageIter )
  {
    return std::get<MESSAGE>(messageIter->second)->SubscribeCANSignal(signalName,listener);
  }

  return false;
}

bool CCANMessageProcessor::SubscribeCANSignalByPGN( const unsigned int msgId, const std::string& signalName, ISignalListener& listener )
{
  const auto messageIter = m_dbcInfo.pgn2message.find( GET_PGN(msgId) );
  if (m_dbcInfo.msgId2message.end() != messageIter )
  {
    return std::get<MESSAGE>(messageIter->second)->SubscribeCANSignal(signalName,listener);
  }

  return false;
}

void CCANMessageProcessor::SubscribeAllMessages( IMessageListener& listener )
{
  m_dbcInfo.allMessageListeners.push_back(&listener);
}

bool CCANMessageProcessor::SubscribeCANMessage( const unsigned int msgId, IMessageListener& listener)
{
  const auto messageIter = m_dbcInfo.msgId2message.find( msgId );
  if (m_dbcInfo.msgId2message.end() != messageIter )
  {
    std::get<MSG_LISTENERS>(messageIter->second).push_back(&listener);
    return true;
  }

  return false;
}


const std::string& CCANMessageProcessor::GetProperty( const std::string& propertyName)
{
  const auto propertyIter = m_dbcInfo.processorPropertyMap.find(propertyName);
  if (m_dbcInfo.processorPropertyMap.end() != propertyIter )
  {
    return propertyIter->second;
  }
  return emptyString;
}

const std::string& CCANMessageProcessor::GetPropertyType( const std::string& propertyName)
{
  const auto propertyTypeIter = m_dbcInfo.propertyTypesMap.find(propertyName);
  if (m_dbcInfo.propertyTypesMap.end() != propertyTypeIter )
  {
    return propertyTypeIter->second;
  }
  return emptyString;
}


