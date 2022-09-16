#pragma once
#include <string>
#include <regex>

class IDBCInfoBuilder;

class CDBCFileParser
{
public:
  CDBCFileParser( IDBCInfoBuilder& engineInitializer );
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
  std::regex m_signalValueMapper;
  std::regex m_versionInfo;

  IDBCInfoBuilder& m_rDBCProcessorInitializer;

};