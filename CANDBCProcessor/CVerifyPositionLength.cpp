#include "CVerifyPositionLength.h"
#include <tuple>

bool CVerifyPositionLength::VerifyMessage( const CMessageTemplate&  msgEntry )
{
  bool allFine(true);
  const auto& signals = msgEntry.GetMessageSignals();

  for ( const auto& signal : signals)
  {
    const auto startBit = std::get<SIGNAL>(signal).GetStartBit();
    const auto length = std::get<SIGNAL>(signal).GetLength();

    if ( startBit + length > 8*8 )
    {
      allFine = false;
      break;
    }
  }

  return allFine;
}