#pragma once

#include <stdint.h>
#include <string>

class BTInterface
{
public:
    virtual bool init();
    virtual std::string read();
    virtual bool write(std::string s);
};