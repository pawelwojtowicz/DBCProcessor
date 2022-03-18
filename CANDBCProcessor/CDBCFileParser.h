#pragma once
#include <string>
#include <regex>

class IDBCEngineInit;

class CDBCFileParser
{
public:
  CDBCFileParser( IDBCEngineInit& engineInitializer );
  ~CDBCFileParser();

  bool ReadDBCFile( const std::string& filename );
private:
  std::regex m_messageRegExp;
  std::regex m_signalRegExp;
  std::regex m_multiplexedSignalRegExp;
  std::regex m_messageCommentRegExp;
  std::regex m_signalCommentRegExp;
  std::regex m_signalPropertyTypeRegExp;
  std::regex m_messagePropertyTypeRegExp;
  std::regex m_generalPropertyTypeRegExp;
  std::regex m_valueDefaultPropertyRegExp;
  std::regex m_defineMsgProperty;
  std::regex m_defineSignalProperty;

  IDBCEngineInit& m_rDBCProcessorInitializer;

};