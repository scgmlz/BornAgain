#ifndef BA_TNAMED_H
#define BA_TNAMED_H

#include <string>
#include "TObject.h"
#include "RtypesCore.h"

class TNamed {
public:
    TNamed(std::string name = {}, std::string descr = {})
        : m_name(name), m_description(descr){}

    virtual ~TNamed() = default;

private:
    std::string m_name;
    std::string m_description;
};

#endif
