#include "CMessage.h"

CMessage::CMessage()
{

}

CMessage::~CMessage()
{

}

bool CMessage::ProcessMessage( const uint64_t& msg , size_t msgSize )
{
    for( auto signal : m_signalList)
    {
        signal.ExtractValue(msg,msgSize);
    }

    return true;
}