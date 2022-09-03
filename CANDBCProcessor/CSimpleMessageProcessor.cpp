#include "CSimpleMessageProcessor.h"

void CSimpleMessageProcessor::ProcessMessage( const unsigned int msgId, tSignalList& signals, const uint64_t& msg , size_t msgSize )
{
  for( auto signal : signals)
  {
    std::get<VALUE>(signal).UpdateValue( std::get<SIGNAL>(signal).ExtractValue(msg,msgSize) );

    for( auto listener : std::get<LISTENERS>(signal ) )
    {
      listener->NotifySignaReceived( msgId, std::get<VALUE>(signal) );
    }
  }
}