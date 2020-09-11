#ifndef BORNAGAIN_TESTS_GTESTWRAPPER_GOOGLE_TEST_H
#define BORNAGAIN_TESTS_GTESTWRAPPER_GOOGLE_TEST_H

#ifdef _MSC_VER
#define _VARIADIC_MAX 10
#endif

#ifdef _WIN32
#pragma warning(push)
#pragma warning(disable : 4275)
#include <gtest/gtest.h>
#pragma warning(pop)
#else
#include <gtest/gtest.h>
#endif

#include <memory>

#endif // BORNAGAIN_TESTS_GTESTWRAPPER_GOOGLE_TEST_H
