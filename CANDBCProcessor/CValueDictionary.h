#pragma once
#include <map>

class CValueDictionary
{
  using tInt2StringDictionary = std::map<int, std::string>;
public:
  CValueDictionary(const std::string& initializerString );
  virtual ~CValueDictionary();
  CValueDictionary( const CValueDictionary& ) = delete;
  CValueDictionary& operator=(const CValueDictionary&) = delete;

  const std::string& GetValueForInt( const int intValue);

  
private:
  tInt2StringDictionary m_dictionary;
};