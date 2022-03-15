#pragma once
#include <string>
#include <memory>
#include "ISignalInfo.h"

class CValue
{
public:
    CValue( const uint64_t& rawValue, std::shared_ptr<ISignalInfo> signal );
    virtual ~CValue();

    std::shared_ptr<ISignalInfo> GetSignalInfo();
    const uint64_t& GetRawValue() const;
    virtual bool GetValue( int& value ) const;
    virtual bool GetValue( float& value) const ;
    virtual bool GetValue( std::string& value ) const;
private:
    uint64_t m_rawValue;

    std::shared_ptr<ISignalInfo> m_signalInfo;
};