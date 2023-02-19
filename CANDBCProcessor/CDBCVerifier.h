#pragma once
#include "DBCInfo.h"
#include "IDBCVerifier.h"

class CDBCVerifier
{
public:
  CDBCVerifier( const DBCInfo& dbcInfo );
  virtual ~CDBCVerifier();

  bool VerifyDBCInfo();
private:
  const DBCInfo& m_dbcContext;

  std::list<std::unique_ptr<IDBCVerifier>> m_verifiers;
};