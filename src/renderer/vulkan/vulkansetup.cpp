#include "vulkansetup.h"
#include <iostream>

namespace page::vulkan {

TempVulkanSetupObject::TempVulkanSetupObject()
{
    std::cout << "I am a temporary Vulkan Setup object\n";
    m_isValid = init();
}

bool TempVulkanSetupObject::init()
{
#ifdef VK_NO_PROTOTYPES
    std::cout << "\tVK_NO_PROTOTYPES is defined\n";
#else
    std::cout << "\tWARNING: VK_NO_PROTOTYPES is NOT defined. This may become a potential performance issue.\n";
#endif
    return initLibs();
}

bool TempVulkanSetupObject::initLibs()
{
#if defined _WIN32
    vulkan_library = LoadLibrary("vulkan-1.dll");
#elif defined __linux
    vulkan_library = dlopen("libvulkan.so.1", RTLD_NOW);
#else
    std::cerr << "The PAGE renderer is not yet setup for Vulkan on this platform. Supported operating systems are Linux and Windows" << std::endl;
    vulkan_library = nullptr;
#endif
    if (vulkan_library) {
        std::cout << "\tSuccessfully connected with a Vulkan Runtime library.\n";
        return true;
    }

    std::cerr << "Could not connect with a Vulkan Runtime library.\n";
    return false;
}

} // namespace page::vulkan