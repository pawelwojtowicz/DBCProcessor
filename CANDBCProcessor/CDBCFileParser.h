#pragma once
#include <string>
#include <regex>

class CDBCFileParser
{
public:
  CDBCFileParser();
  ~CDBCFileParser();

  bool ReadDBCFile( const std::string& filename );
private:
  std::regex m_messageRegExp;
  std::regex m_signalRegExp;

};