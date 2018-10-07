#pragma once

#include <stdint.h>

#if defined _WIN32
#include <windows.h>
#endif _WIN32

namespace page {
namespace vulkan {

class TempVulkanSetupObject {
public:
    TempVulkanSetupObject();
    bool isValid() const { return m_isValid; }
    uint32_t extensionCount() const { return m_extensionCount; }
    void printAvailableExtensions() const;

private:
    bool init();
    bool initLibs();
    bool initProcAddr();
    bool loadGlobalLevelFunctions();
    bool setupLogicalDevice();

private:
    bool m_isValid;
    uint32_t m_extensionCount;

#if defined _WIN32
    HMODULE vulkan_library;
#elif defined __linux
    void* vulkan_library;
#else
    void* vulkan_library;
#endif
};

} // namespace vulkan
} // namespace page
