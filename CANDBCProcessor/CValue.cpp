#include "CValue.h"
#include <iostream>

CValue::CValue( const std::string& name, float offset , float scale, float min, float max, const std::string& unit, const std::string& receiver )
: m_name(name)
, m_description("")
, m_unit(unit)
, m_receiver(receiver)
, m_offset(offset)
, m_scale(scale)
, m_min(min)
, m_max(max)
, m_rawValue(0)
, m_value(0)
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

int CValue::GetValueINT( ) const
{
  return static_cast<int>(m_value);
}

float CValue::GetValueFLOAT( ) const
{
  return m_value;
}

std::string CValue::GetValueSTRING( ) const
{
  if (m_valueDictionary)
  {
    return m_valueDictionary->GetValueForInt( static_cast<int>( m_value));
  }
  return std::to_string(m_value);
}

const std::string& CValue::GetDescription() const
{
  return m_description;
}

const std::string& CValue::GetUnit() const
{
  return m_unit;
}