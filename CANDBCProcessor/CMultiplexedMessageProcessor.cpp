#include "CMultiplexedMessageProcessor.h"
#include "ISignalListener.h"

void CMultiplexedMessageProcessor::ProcessMessage( CMessageTemplate& message, const uint64_t& data , size_t msgSize )
{
  message.SetRawData(data);
  auto& signals( message.GetMessageSignals() );
  auto signalIter(signals.begin());

  //get the multiplexer field value
  std::get<VALUE>(*signalIter).UpdateValue( std::get<SIGNAL>(*signalIter).ExtractValue(data,msgSize) );
  const auto multiplexedId = std::get<VALUE>(*signalIter).GetValueINT();
  ++signalIter;

  for ( ; signals.end() != signalIter;  ++signalIter)
  {
    const auto signalMultiplexId =  std::get<MULTIPLEXERID>(*signalIter);
    if (  signalMultiplexId < 0 || multiplexedId == signalMultiplexId )
    {
      std::get<VALUE>(*signalIter).UpdateValue( std::get<SIGNAL>(*signalIter).ExtractValue(data,msgSize) );

      for( auto listener : std::get<LISTENERS>(*signalIter ) )
      {
        listener->NotifySignalReceived( message.GetMessageId(), std::get<VALUE>(*signalIter) );
      }
    }
  }
}