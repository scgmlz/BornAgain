#ifndef BA_TERROR_H
#define BA_TERROR_H

#include "RtypesCore.h"
#include <utility>
#include <sstream>
#include <iostream>
#include <cassert>

const Int_t kUnset    =  -1;
const Int_t kPrint    =   0;
const Int_t kInfo     =   1000;
const Int_t kWarning  =   2000;
const Int_t kError    =   3000;
const Int_t kBreak    =   4000;
const Int_t kSysError =   5000;
const Int_t kFatal    =   6000;

inline void insert_messages(std::stringstream& ss)
{
    (void)ss;
}

template <typename T, typename... Types>
void insert_messages(std::stringstream& ss, T var1, Types... var2)
{
    ss << var1;
    insert_messages(ss, var2...);
}

template<typename... Args>
void logHelperMessage(std::string severity, Args&&... args) {
  std::stringstream ss;
  insert_messages(ss, std::forward<Args>(args)...);
  std::cout << severity << " " << ss.str() << std::endl;
}


template<typename... Ts>
void Info(Ts&&... args)
{
    logHelperMessage("Info", std::forward<Ts>(args)...);
}

template<typename... Ts>
void Error(Ts&&... args)
{
    logHelperMessage("Error", std::forward<Ts>(args)...);
}

template<typename... Ts>
void Warning(Ts&&... args)
{
    logHelperMessage("Warning", std::forward<Ts>(args)...);
}

#endif
