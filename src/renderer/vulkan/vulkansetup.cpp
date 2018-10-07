#include "vulkansetup.h"

#include <iostream>
#include "vulkanfunctions.h"

namespace page::vulkan {

////////////////////////////////////////////////////////////////////////////////////////////////////

TempVulkanSetupObject::TempVulkanSetupObject()
: m_extensionCount(0)
{
    std::cout << "I am a temporary Vulkan Setup object\n";
    m_isValid = init();
}

////////////////////////////////////////////////////////////////////////////////////////////////////

bool TempVulkanSetupObject::init()
{
    if (!initLibs() || !initProcAddr() || !loadGlobalLevelFunctions() || !setupLogicalDevice())
        return false;

    return true;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

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
    if (!vulkan_library) {
        std::cerr << "Could not connect with a Vulkan Runtime library.\n";
        return false;
    }

    std::cout << "\tSuccessfully connected with a Vulkan Runtime library.\n";
    return true;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

bool TempVulkanSetupObject::initProcAddr()
{
#ifdef VK_NO_PROTOTYPES
    std::cout << "\tVK_NO_PROTOTYPES is defined\n";
#else
    std::cout << "\tWARNING: VK_NO_PROTOTYPES is NOT defined. This may become a potential performance issue.\n";
#endif

#if defined _WIN32
#define LoadFunction GetProcAddress
#elif defined __linux
#define LoadFunction dlsym
#endif

#define EXPORTED_VULKAN_FUNCTION( name )                              \
    name = (PFN_##name)LoadFunction( vulkan_library, #name );         \
    if( name == nullptr ) {                                           \
        std::cout << "Could not load exported Vulkan function named: "\
            #name << std::endl;                                       \
        return false;                                                 \
    }

#include "listofvulkanfunctions.inl"

    return true;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

bool TempVulkanSetupObject::loadGlobalLevelFunctions()
{
#define GLOBAL_LEVEL_VULKAN_FUNCTION( name )                        \
    name = (PFN_##name)vkGetInstanceProcAddr( nullptr, #name );     \
    if( name == nullptr ) {                                         \
        std::cout << "Could not load global-level function named: " \
            #name << std::endl;                                     \
        return false;                                               \
    }

#include "listofvulkanfunctions.inl"

    return true;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

bool TempVulkanSetupObject::setupLogicalDevice()
{
    VkResult result = VK_SUCCESS;
    result = vkEnumerateInstanceExtensionProperties(nullptr, &m_extensionCount, nullptr);
    if (result != VK_SUCCESS || m_extensionCount == 0) {
        std::cout << "Could not get the number of Instance extensions." << std::endl;
        return false;
    }

    return true;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

} // namespace page::vulkan
