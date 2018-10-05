#pragma once

#if defined _WIN32
#include <windows.h>
#endif _WIN32

namespace page {
namespace vulkan {

class TempVulkanSetupObject {
public:
    TempVulkanSetupObject();
    bool isValid() { return m_isValid; }
private:
    bool init();
private:
    bool m_isValid;
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
