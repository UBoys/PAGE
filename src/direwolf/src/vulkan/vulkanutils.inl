#include "vulkanutils.h"

#include <iostream>
#include <sstream>
#include <string>

// TODO: fix namespaces
namespace page::vulkan {

// TODO: PRETTY PRINT SHOULDNT BE HERE
////////////////////////////////////////////////////////////////////////////////////////////////////
// PRETTY PRINT
template <typename T>
void prettyPrint(std::ostream& os, const T& t, uint8_t minWidth, const char* prefix, const char* suffix)
{
    os << prefix << std::setw(minWidth) << t << suffix;
}

} // namespace page::vulkan
