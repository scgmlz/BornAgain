#ifdef _MSC_VER
#define _VARIADIC_MAX 10
#endif
#include <gtest/gtest.h>

#include "testlist.h"
#include "ErrorStreamRedirect.h"

int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);

    // redirect std::cerr stream
    std::stringstream oss;
    ErrorStreamRedirect redirecter( oss.rdbuf() );
    (void)redirecter;

    // run all google tests
    return RUN_ALL_TESTS();
}
