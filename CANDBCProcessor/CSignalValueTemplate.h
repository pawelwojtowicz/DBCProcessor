#pragma once
#include "CValue.h"

class CSignalValueTemplate : public CValue
{
public: 
  CSignalValueTemplate(const std::string& name, float offset , float scale, float min, float max , const std::string& unit, const std::string& receiver);
  virtual ~CSignalValueTemplate();

  void SetDescription( const std::string& description);

  void SetValueDictionary( const std::string& dictionaryInitializerString);

  void AddProperty( const std::string& propertyName,  const std::string& propertyValue );
  void UpdateValue( const uint64_t& rawValue );
};