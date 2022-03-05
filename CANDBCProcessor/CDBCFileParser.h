#pragma once
#include <string>

class CDBCFileParser
{
public:
  CDBCFileParser();
  ~CDBCFileParser();

  bool ReadDBCFile( const std::string& filename );
private:
};