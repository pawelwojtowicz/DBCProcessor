#include "CCANMessageProcessor.h"
#include "CDBCInfoBuilder.h"
#include "ISignalListener.h"

#include <iostream>

void CCANMessageProcessor::Initialize(  const std::vector<std::string>& dbcList )
{
    CDBCInfoBuilder dbcBuilder(m_dbcInfo);
    dbcBuilder.BuildDBCInfo(dbcList);
}

void CCANMessageProcessor::Shutdown()
{

}

bool CCANMessageProcessor::ProcessCANMessage( const unsigned int msgId, const uint64_t& data)
{
    const auto messageIter = m_dbcInfo.m_msgId2message.find( msgId );
    if (m_dbcInfo.m_msgId2message.end() != messageIter )
    {
        messageIter->second->ProcessMessage(data,8);
        return true;
    }

    return false;
}

bool CCANMessageProcessor::ProcessCANMessageByPGN( const unsigned int msgId, const uint64_t& data)
{
    const auto messageIter = m_dbcInfo.m_pgn2message.find( GET_PGN(msgId) );
    if (m_dbcInfo.m_pgn2message.end() != messageIter )
    {
      messageIter->second->ProcessMessage(data,8);
      return true;
    }

    return false;
}

bool CCANMessageProcessor::SubscribeCANSignal( const unsigned int msgId, const std::string& signalName, ISignalListener& listener )
{
    const auto messageIter = m_dbcInfo.m_msgId2message.find( msgId );
    if (m_dbcInfo.m_msgId2message.end() != messageIter )
    {
      return messageIter->second->SubscribeCANSignal(signalName,listener);
    }

    return false;
}



