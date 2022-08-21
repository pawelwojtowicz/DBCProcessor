#include "CSignalValueTemplate.h"

CSignalValueTemplate::CSignalValueTemplate(const std::string& name, float offset , float scale, float min, float max , const std::string& unit, const std::string& receiver)
: CValue(name, offset , scale, min, max , unit, receiver)
{
}

CSignalValueTemplate::~CSignalValueTemplate()
{

}

void CSignalValueTemplate::SetDescription( const std::string& description)
{
  m_description = description;
}

void CSignalValueTemplate::AddProperty( const std::string& propertyName,  const std::string& propertyValue )
{
  m_signalPropertyMap.insert(CValue::tSignalPropertyMap::value_type(propertyName, propertyValue) );
}

void CSignalValueTemplate::UpdateValue( const uint64_t& rawValue )
{
  m_value = m_offset + rawValue * m_scale;
}
