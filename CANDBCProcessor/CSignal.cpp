#include "CSignal.h"
#include <iostream>
#include <bitset>

CSignal::CSignal( const int start, const int length, eEndiannes endian )
: m_bitStart(start)
, m_bitLength(length)
, m_canSignalMask ( (0x1ULL << m_bitLength ) -1 )
, m_byteCount( m_bitLength / 8 )
, m_endiannes( endian )
{
    if ( m_bitLength != ( m_byteCount * 8 ) )
    {
        ++m_byteCount;
    }
}

CSignal::~CSignal()
{
}

uint64_t CSignal::ExtractValue( const uint64_t& canData , size_t dataLength)
{
    uint64_t rawValue(0);

    if ( bigEndian == m_endiannes ) 
    {
        uint64_t workingCopy(canData);
        for ( int i = 0 ; i < 8 ; ++i )
        {
            rawValue <<= 8;
            rawValue |= ( workingCopy & 0xFFULL );
            workingCopy >>= 8;
        }
        rawValue = m_canSignalMask & ( rawValue >> ( (7 - (m_bitStart/8 ) ) * 8 + m_bitStart%8) );
    }
    else
    {
        rawValue = m_canSignalMask & ( canData >> (m_bitStart ) );
    }

    return rawValue;
}