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
  m_rawValue = rawValue;
  m_value = m_offset + m_rawValue * m_scale;
}

void CSignalValueTemplate::SetValueDictionary( const std::string& dictionaryInitializerString)
{
  m_valueDictionary = std::make_shared<CValueDictionary>(dictionaryInitializerString);
}
