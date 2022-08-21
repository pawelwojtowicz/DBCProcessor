#include "CValue.h"

CValue::CValue( const std::string& name, float offset , float scale, float min, float max, const std::string& unit, const std::string& receiver )
: m_name(name)
, m_rawValue(0)
, m_offset(offset)
, m_scale(scale)
, m_min(min)
, m_max(max)
, m_value(0)
, m_receiver(receiver)
, m_unit(unit)
, m_description("")
{
}

 CValue::~CValue()
 {

 }

const std::string& CValue::GetName() const
{
  return m_name;
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
  value = m_value;
  return true;
}

bool CValue::GetValue( std::string& value ) const
{
  return false;
}

const std::string& CValue::GetDescription() const
{
  return m_description;
}
