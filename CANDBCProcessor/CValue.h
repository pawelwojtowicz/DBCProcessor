#pragma once
#include <string>
#include <memory>
#include <map>
#include "CValueDictionary.h"
#include "DBCProcessor.h"

class CValue
{
public:
  CValue( const std::string& name, float offset , float scale, float min, float max , const std::string& unit, const std::string& receiver);
  virtual ~CValue();

  const std::string& GetName() const;
  const std::string& GetDescription() const;
  const std::string& GetUnit() const;

  const uint64_t& GetRawValue() const;

  int GetValueINT( ) const;
  float GetValueFLOAT( ) const ;
  std::string GetValueSTRING( ) const;

protected:
  std::string m_name;
  std::string m_description;
  std::string m_unit;
  std::string m_receiver;
  float m_offset;
  float m_scale;
  float m_min;
  float m_max;
  tPropertyMap m_signalPropertyMap;

  std::shared_ptr<CValueDictionary> m_valueDictionary;

  uint64_t m_rawValue;
  float m_value;
};