#include "vulkansetup.h"

#include <cstring>
#include <iostream>
#include "vulkanfunctions.h"

namespace page::vulkan {

////////////////////////////////////////////////////////////////////////////////////////////////////

TempVulkanSetupObject::TempVulkanSetupObject(std::vector<const char*>* desiredExtensions /* = nullptr */)
: m_isValid(false)
{
    std::cout << "I am a temporary Vulkan Setup object\n";
    m_isValid = initialize(desiredExtensions);
}

////////////////////////////////////////////////////////////////////////////////////////////////////

bool TempVulkanSetupObject::initialize(std::vector<const char*>* desiredExtensions)
{
    if (m_isValid) {
        std::cerr << "Trying to initialize TempVulkanSetupObject after it has already been initialized!" << std::endl;
        return false;
    }

    // Out as soon as something goes wrong
    if (!initLibs() ||
        !initProcAddr() ||
        !loadGlobalLevelFunctions() ||
        !createVulkanInstance(desiredExtensions))
    {
        return false;
    }

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
        s_vulkanRTLFound = false;
        return false;
    }

    std::cout << "\tSuccessfully connected with a Vulkan Runtime library.\n";
    s_vulkanRTLFound = true;
    return true;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

bool TempVulkanSetupObject::initProcAddr()
{
    // TODO: move this #ifdef part elsewhere?
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

bool TempVulkanSetupObject::getAvailableInstanceExtensions(std::vector<VkExtensionProperties>& outAvailableExtensions) const
{
    if (!s_vulkanRTLFound)
        return false;

    // Input should be an empty vector
    outAvailableExtensions.clear();

    VkResult result = VK_SUCCESS;
    uint32_t extensionCount = 0;

    // Get number of available extensions
    result = vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, nullptr);

    if (result != VK_SUCCESS || extensionCount == 0) {
        std::cerr << "Could not get the number of Instance extensions." << std::endl;
        return false;
    }

    outAvailableExtensions.resize(extensionCount);
    result = vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, &outAvailableExtensions[0]);

    if (result != VK_SUCCESS || outAvailableExtensions.size() == 0) {
        std::cerr << "Could not enumerate Instance extensions." << std::endl;
        return false;
    }

    return true;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void TempVulkanSetupObject::debugPrintAvailableExtensions() const
{
    std::vector<VkExtensionProperties> availableExtensions;

    if (!getAvailableInstanceExtensions(availableExtensions))
        return;

    std::cout << "The following extensions are available:\n";

    for (const VkExtensionProperties& extension : availableExtensions) {
        std::cout << "\t" << extension.extensionName << "\n";
    }
    std::cout << std::endl;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

bool TempVulkanSetupObject::createVulkanInstance(std::vector<const char*>* desiredExtensions)
{
    std::vector<VkExtensionProperties> availableExtensions;
    if (!getAvailableInstanceExtensions(availableExtensions)) {
        return false;
    }

    if (desiredExtensions) {
        for (const char* extension : *desiredExtensions) {
            if (!isExtensionSupported(extension, &availableExtensions)) {
                std::cerr << "Extension named '" << extension << "' is not supported." << std::endl;
                return false;
            }
        }
    }

    VkApplicationInfo applicationInfo;
    // The following could be set in an initializer list, but this is clearer for now
    applicationInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
    applicationInfo.pNext = nullptr;
    applicationInfo.pApplicationName = "NullNameApplication";
    applicationInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
    applicationInfo.pEngineName = "NullNameEngine";
    applicationInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
    applicationInfo.apiVersion = VK_MAKE_VERSION(1, 0, 0);

    VkInstanceCreateInfo instanceCreateInfo;
    // The following could be set in an initializer list, but this is clearer for now
    instanceCreateInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
    instanceCreateInfo.pNext = nullptr;
    instanceCreateInfo.flags = 0;
    instanceCreateInfo.pApplicationInfo = &applicationInfo;
    instanceCreateInfo.enabledLayerCount = 0;
    instanceCreateInfo.ppEnabledLayerNames = nullptr;
    instanceCreateInfo.enabledExtensionCount = desiredExtensions ? desiredExtensions->size() : 0;
    instanceCreateInfo.ppEnabledExtensionNames = desiredExtensions ? desiredExtensions->data() : nullptr;

    // TODO: make member variable?
    VkInstance instance;
    if ( (vkCreateInstance( &instanceCreateInfo, nullptr, &instance ) != VK_SUCCESS) || (instance == VK_NULL_HANDLE) ) {
        std::cout << "Could not create Vulkan Instance." << std::endl;
        return false;

    }

    return true;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

std::vector<const char*> TempVulkanSetupObject::getDefaultInstanceExtensions() {
    return {
        "VK_KHR_surface",
    // "VK_KHR_win32_surface",
    // "VK_KHR_external_memory_capabilities",
    // "VK_KHR_external_semaphore_capabilities",
    // "VK_KHR_external_fence_capabilities",
    // "VK_KHR_get_physical_device_properties2",
    // "VK_KHR_get_surface_capabilities2",
    // "VK_EXT_debug_report",
    // "VK_EXT_display_surface_counter",
    // "VK_NV_external_memory_capabilities",
    // "VK_EXT_debug_utils"
    };
}

////////////////////////////////////////////////////////////////////////////////////////////////////

bool TempVulkanSetupObject::isExtensionSupported(const char* extension, std::vector<VkExtensionProperties>* availableExtensionsPtr /* = nullptr*/) const
{
    std::vector<VkExtensionProperties> availableExtensions;
    if (!availableExtensionsPtr) {
        getAvailableInstanceExtensions(availableExtensions);
        availableExtensionsPtr = &availableExtensions;
    }

    for (VkExtensionProperties availableExtension : *availableExtensionsPtr) {
        if (strcmp(availableExtension.extensionName, extension) == 0)
            return true;
    }

    return false;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

} // namespace page::vulkan
