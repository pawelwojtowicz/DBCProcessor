#include "CVerifySignalOverlay.h"
#include <vector>
#include <set>
#include <string>

bool CVerifySignalOverlay::VerifyMessage( const CMessageTemplate&  msgEntry )
{
  bool overlayVerificationStatus = true;

  std::vector<std::set<std::string>> signalsLayout(64);

  const auto& signalsList = msgEntry.GetMessageSignals();

  for ( const auto& signalEntry : signalsList )
  {
    const CSignal& signalDesc = std::get<SIGNAL>(signalEntry);
    
    int startBit = signalDesc.GetStartBit();
    int bitLength = signalDesc.GetLength();
    CSignal::eEndiannes signalEndian = signalDesc.GetEndiannes();

    for ( int i = 0 ; i < bitLength ; ++i )
    {
      int currIndex = startBit + i;
      if ( CSignal::eEndiannes::bigEndian == signalEndian )
      {
        // reclaculate index for big endian
      }

      signalsLayout[currIndex].insert( std::get<VALUE>(signalEntry).GetName() );
    }
  }

  for ( const auto& messageBitSignals : signalsLayout)
  {
    if (messageBitSignals.size() > 1 )
    {
      overlayVerificationStatus = false;
    }
  }

  return overlayVerificationStatus;
}