#include "CSignal.h"
#include <iostream>
#include <bitset>

CSignal::CSignal( const int start, const int length, eEndiannes endian, tValueProperties valueProperties)
: m_bitStart(start)
, m_bitLength(length)
, m_canSignalMask ( (0x1ULL << m_bitLength ) -1 )
, m_byteCount( m_bitLength / 8 )
, m_endiannes( endian )
, m_description("")
, m_valueProperties(valueProperties)
{
    if ( m_bitLength != ( m_byteCount * 8 ) )
    {
        ++m_byteCount;
    }
}

CSignal::~CSignal()
{
}

void CSignal::SetDescription( const std::string& description)
{
    m_description = description;
}

const std::string& CSignal::GetName() const
{
    return m_signalName;
}

const std::string& CSignal::GetUnit() const
{
    return m_unit;
}

void CSignal::AddProperty( const std::string& propertyName,  const std::string& propertyValue )
{
    m_signalPropertyMap.insert(tSignalPropertyMap::value_type(propertyName, propertyValue) );
}

const std::string CSignal::GetProperty( const std::string& propertyName ) const
{
    const auto propertyIt = m_signalPropertyMap.find( propertyName );
    if ( m_signalPropertyMap.end() != propertyIt )
    {
        return propertyIt->second;
    }
    return std::string();
}

std::unique_ptr<CValue> CSignal::ExtractValue( const uint64_t& canData , size_t dataLength)
{
    uint64_t rawValue = m_canSignalMask & ( canData >> m_bitStart );

    if ( bigEndian == m_endiannes ) 
    {
        uint64_t workingCopy(rawValue);   
        rawValue = 0;
        for ( int i = 0 ; i < m_byteCount ; ++i )
        {
            rawValue <<= 8;
            rawValue |= workingCopy & 0xFFULL;
            workingCopy >>= 8;
        }
    }

    return CreateValue(rawValue);
}

std::unique_ptr<CValue> CSignal::CreateValue( const uint64_t rawValue )
{
    return std::move(std::make_unique<CValue>( rawValue, *this ));
}