#include "CValueDictionary.h"
#include "DBCProcessor.h"
#include <regex>
#include <iostream>

CValueDictionary::CValueDictionary(const std::string& initializerString )
{
  std::regex keyValuePairRegExp("^(?:([0-9]+) \\\"([a-zA-Z0-9,\\.\\(\\)\\s]+)\\\")\\s*");
  std::string inputString( initializerString );
  
  std::smatch match;
  while ( std::regex_search( inputString, match, keyValuePairRegExp ))
  {
    const std::string& key = match[1];
    m_dictionary.insert(tInt2StringDictionary::value_type( atoi( key.c_str() ), match[2] ));
     inputString = inputString.substr(match[0].length() );
  }
}

CValueDictionary::~CValueDictionary()
{

}

const std::string& CValueDictionary::GetValueForInt( const int intValue)
{
  const auto iter = m_dictionary.find(intValue);

  if (m_dictionary.end() != iter )
  {
    return iter->second;
  }

  return emptyString;
}
