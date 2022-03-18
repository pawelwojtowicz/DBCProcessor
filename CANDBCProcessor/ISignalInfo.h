#pragma once
#include <string>

class ISignalInfo
{
public:
    ISignalInfo() {};
    virtual ~ISignalInfo() {};

    virtual const std::string& GetName() const = 0;
    virtual const std::string& GetUnit() const = 0;
    virtual const std::string GetProperty( const std::string& propertyName ) const = 0;

};