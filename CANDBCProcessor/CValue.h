#pragma once
#include <string>
#include <memory>
#include <list>
#include "ISignalInfo.h"

class CValue
{
public:
    CValue( const uint64_t& rawValue, const ISignalInfo& signal );
    virtual ~CValue();

    const ISignalInfo& GetSignalInfo();
    const uint64_t& GetRawValue() const;
    virtual bool GetValue( int& value ) const;
    virtual bool GetValue( float& value) const ;
    virtual bool GetValue( std::string& value ) const;
private:
    uint64_t m_rawValue;

    const ISignalInfo& m_signalInfo;
};

using tValues = std::list<std::unique_ptr<CValue>>;