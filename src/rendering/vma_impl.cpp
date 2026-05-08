// Single translation unit for the Vulkan Memory Allocator implementation.
//
// Kept separate from vk_context.cpp because on AmigaOS4 the rest of the
// renderer is compiled with <proto/vulkan.h> active, which #defines bare
// `vkXxx` symbols as `IVulkan->vkXxx(args)` macros. VMA uses those names as
// struct fields and as function-pointer values, so the inline macros must
// be off in this file (the WOWEE_AMIGA_NO_VULKAN_INLINE define is set on
// this source via CMake's set_source_files_properties).

#ifdef __amigaos4__
// AmigaOS4 vulkan.library is dispatched through IVulkan — there are no bare
// `vkXxx` link-time symbols. Force VMA onto the dynamic-dispatch path so it
// resolves entry points via vkGetInstanceProcAddr / vkGetDeviceProcAddr that
// the renderer feeds it (typically obtained from SDL_Vulkan_GetVkGetInstanceProcAddr).
#  define VMA_STATIC_VULKAN_FUNCTIONS 0
#  define VMA_DYNAMIC_VULKAN_FUNCTIONS 1
#endif

#define VMA_IMPLEMENTATION
#include <vk_mem_alloc.h>
