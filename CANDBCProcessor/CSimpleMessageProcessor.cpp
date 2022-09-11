#include "CSimpleMessageProcessor.h"
#include "ISignalListener.h"

void CSimpleMessageProcessor::ProcessMessage( CMessageTemplate& message, const uint64_t& data , size_t msgSize )
{
  message.SetRawData(data);

  auto& signals( message.GetMessageSignals() );
  for( auto signal : signals)
  {
    std::get<VALUE>(signal).UpdateValue( std::get<SIGNAL>(signal).ExtractValue(data,msgSize) );

    for( auto listener : std::get<LISTENERS>(signal ) )
    {
      listener->NotifySignalReceived( message.GetMessageId(), std::get<VALUE>(signal) );
    }
  }
}