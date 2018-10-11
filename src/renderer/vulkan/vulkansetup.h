#pragma once

#include <stdint.h>
#include <vector>

#if defined _WIN32
#include <windows.h>
#endif _WIN32

struct VkExtensionProperties;

namespace page {
namespace vulkan {

class TempVulkanSetupObject {
public:
    TempVulkanSetupObject(std::vector<const char*>* desiredExtensions = nullptr);
    bool initialize(std::vector<const char*>* desiredExtensions);
    bool isValid() const { return m_isValid; }
    void debugPrintAvailableExtensions() const;
    static std::vector<const char*> getDefaultInstanceExtensions();

private: // variables
    bool m_isValid;
    static inline bool s_vulkanRTLFound = false;

#if defined _WIN32
    HMODULE vulkan_library;
#elif defined __linux
    void* vulkan_library;
#else
    void* vulkan_library;
#endif

private: // functions
    bool initLibs();
    bool initProcAddr();
    bool isExtensionSupported(const char* extension, std::vector<VkExtensionProperties>* availableExtensions = nullptr) const;
    bool loadGlobalLevelFunctions();
    bool createVulkanInstance(std::vector<const char*>* desiredExtensions);
    bool getAvailableInstanceExtensions(std::vector<VkExtensionProperties>& outAvailableExtensions) const;
};

} // namespace vulkan
} // namespace page
