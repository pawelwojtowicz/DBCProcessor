#pragma once

class CValue
{
public:
    CValue( uint64_t rawValue );
    ~CValue();

    const uint64& GetRawValue() const;
    bool GetValue( unsigned int& value ) const;
    bool GetValue( int& value ) const;
    bool GetValue( floar& value ) const;
    bool GetValue( std::string& value ) const;
private:
    uint64_t m_rawValue
};