#ifndef ERRORSTREAMREDIRECT_H
#define ERRORSTREAMREDIRECT_H

#include <iostream>

struct ErrorStreamRedirect {
    ErrorStreamRedirect( std::streambuf* new_buffer )
        : old( std::cerr.rdbuf(new_buffer) )
    {}

    ~ErrorStreamRedirect() {
        std::cerr.rdbuf(old);
    }

private:
    std::streambuf* old;
};

#endif // ERRORSTREAMREDIRECT_H
