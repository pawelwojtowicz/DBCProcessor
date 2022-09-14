#include "CMessageProcessor.h"

uint64_t CMessageProcessor::ReverseBytes( uint64_t canData)
{
  uint64_t reversedValue = 0;
  for ( int i = 0 ; i < 8 ; ++i )
  {
    reversedValue <<= 8;
    reversedValue |= ( canData & 0xFFULL );
    canData >>= 8;
  }
  return reversedValue;
}