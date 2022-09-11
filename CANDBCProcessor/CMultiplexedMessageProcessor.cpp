#include "CMultiplexedMessageProcessor.h"

void CMultiplexedMessageProcessor::ProcessMessage( const unsigned int msgId, tSignalList& signals, const uint64_t& msg , size_t msgSize )
{
  auto signalIter(signals.begin());

  //get the multiplexer field value
  std::get<VALUE>(*signalIter).UpdateValue( std::get<SIGNAL>(*signalIter).ExtractValue(msg,msgSize) );
  const auto multiplexedId = std::get<VALUE>(*signalIter).GetValueINT();
  ++signalIter;

  for ( ; signals.end() != signalIter;  ++signalIter)
  {
    const auto signalMultiplexId =  std::get<MULTIPLEXERID>(*signalIter);
    if (  signalMultiplexId < 0 || multiplexedId == signalMultiplexId )
    {
      std::get<VALUE>(*signalIter).UpdateValue( std::get<SIGNAL>(*signalIter).ExtractValue(msg,msgSize) );

      for( auto listener : std::get<LISTENERS>(*signalIter ) )
      {
        listener->NotifySignalReceived( msgId, std::get<VALUE>(*signalIter) );
      }
    }
  }
}