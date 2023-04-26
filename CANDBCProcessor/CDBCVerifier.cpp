#include "CDBCVerifier.h"
#include "CVerifySignalOverlay.h"
#include "CVerifyMultiplexIndexes.h"
#include "CVerifyPositionLength.h"

CDBCVerifier::CDBCVerifier( const DBCInfo& dbcInfo )
: m_dbcContext( dbcInfo)
, m_verifiers {}
{
  m_verifiers.push_back( std::make_unique<CVerifySignalOverlay>());
  m_verifiers.push_back( std::make_unique<CVerifyMultiplexIndexes>());
  m_verifiers.push_back( std::make_unique<CVerifyPositionLength>());
}

CDBCVerifier::~CDBCVerifier()
{

}

bool CDBCVerifier::VerifyDBCInfo()
{
  int errorCount = 0;
  for( auto& msgEntry : m_dbcContext.msgId2message)
  {
    const auto& message = *(std::get<MESSAGE>(msgEntry.second));
    for ( auto& verifier : m_verifiers )
    {
      if (!verifier->VerifyMessage(message))
      {
        ++errorCount;
      }
    }
  }

  return ( 0 == errorCount );
}