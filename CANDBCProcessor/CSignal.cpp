#include "CSignal.h"
#include <iostream>
#include <bitset>

CSignal::CSignal( const int start, const int length, eEndiannes endian )
: m_bitStart(start)
, m_bitLength(length)
, m_canSignalMask ( (0x1ULL << m_bitLength ) -1 )
, m_endiannes( endian )
{
  if ( bigEndian == m_endiannes )
  {
    m_bitStart = (7 - (m_bitStart/8 ) ) * 8 + m_bitStart%8 ;  
  }
}

CSignal::~CSignal()
{
}

uint64_t CSignal::ExtractValue( const uint64_t& canData, const uint64_t& reversedData , size_t dataLength)
{
  uint64_t rawValue(bigEndian == m_endiannes ? reversedData : canData);
 
  return m_canSignalMask & ( rawValue >> m_bitStart );
}

int CSignal::GetStartBit() const
{
  return m_bitStart;
}

int CSignal::GetLength() const
{
  return m_bitLength;
}

CSignal::eEndiannes CSignal::GetEndiannes() const
{
  return m_endiannes;
}
