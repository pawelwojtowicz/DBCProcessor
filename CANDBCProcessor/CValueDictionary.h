#pragma once
#include <string>
#include <map>

class CValueDictionary
{
  using tInt2StringDictionary = std::map<int, std::string>;
public:
  CValueDictionary(const std::string& initializerString );
  virtual ~CValueDictionary();

  const std::string& GetValueForInt( const int intValue);
  
private:
  tInt2StringDictionary m_dictionary;
};