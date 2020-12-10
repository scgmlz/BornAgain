#include "TUUID.h"
#include <string.h>

#include <iostream>
#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_generators.hpp>
//#include <boost/uuid/uuid_io.hpp>

namespace ROOT {

TUUID::TUUID() : fTimeLow(0)
{

}

// ROOT's implementation is removed in the favor of boost implementation
void TUUID::GetUUID(UChar_t uuid[16]) const
{
//   memcpy(uuid, fTimeLow, 16);
   boost::uuids::random_generator generator;
   boost::uuids::uuid boost_uuid = generator();
   memcpy(uuid, boost_uuid.begin(), 16);
//   std::cout << boost_uuid << "aaa" << uuid[0] << std::endl;
}

}
