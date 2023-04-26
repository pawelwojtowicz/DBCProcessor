#include "CVerifyMultiplexIndexes.h"
#include "DBCProcessor.h"
#include <algorithm>

bool CVerifyMultiplexIndexes::VerifyMessage( const CMessageTemplate&  msgEntry )
{
  if (!msgEntry.IsMultiplexedMessage() )
  {
    return true;
  }
  const auto& signals = msgEntry.GetMessageSignals();

  return ( 2 > std::count_if( signals.begin(), 
                              signals.end(), 
                              [] (const auto& signal) { 
                                return ( cMultiplexerIndexField == std::get<MULTIPLEXERID>(signal ) );
                              }));
}