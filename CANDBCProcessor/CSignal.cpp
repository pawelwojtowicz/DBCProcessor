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
    uint64_t rawValue = m_canSignalMask & ( canData >> (m_bitStart ) );

    if ( bigEndian == m_endiannes ) 
    {
        rawValue = m_canSignalMask & ( canData >> ( m_bitStart ) );
        uint64_t workingCopy(rawValue);   
        rawValue = 0;
        for ( int i = 0 ; i < m_byteCount ; ++i )
        {
            rawValue <<= 8;
            rawValue |= workingCopy & 0xFFULL;
            workingCopy >>= 8;
        }
    }
    else
    {
        rawValue = m_canSignalMask & ( canData >> (m_bitStart ) );
    }

    return rawValue;
}