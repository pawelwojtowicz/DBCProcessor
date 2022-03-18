#include "CValue.h"
CValue::CValue( const uint64_t& rawValue, const ISignalInfo& signal )
: m_rawValue(rawValue)
, m_signalInfo(signal)
{
}

 CValue::~CValue()
 {

 }

const ISignalInfo& CValue::GetSignalInfo()
{
    return m_signalInfo;
}

const uint64_t& CValue::GetRawValue() const
{
    return m_rawValue;
}

bool CValue::GetValue( int& value ) const
{
    return false;
}

bool CValue::GetValue( float& value) const
{
    return false;
}

bool CValue::GetValue( std::string& value ) const
{
    return false;
}
