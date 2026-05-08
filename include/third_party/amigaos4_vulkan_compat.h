#ifndef WOWEE_AMIGAOS4_VULKAN_COMPAT_H
#define WOWEE_AMIGAOS4_VULKAN_COMPAT_H

// AmigaOS4's vulkan_core.h ships a stripped-down API surface:
//   * legacy Vulkan 1.0 barrier structs (VkMemoryBarrier / VkBufferMemoryBarrier
//     / VkImageMemoryBarrier) are absent — only VkMemoryBarrier2 + VkDependencyInfo
//     are exposed, and vkCmdPipelineBarrier takes `const void*` for the barrier
//     pointers.
//   * the matching VK_STRUCTURE_TYPE_* values, VK_ACCESS_* flags, and most of the
//     VkPipelineStageFlagBits enumerators are missing.
//   * VkBufferUsageFlagBits / a few descriptor-pool flags are absent.
//
// imgui_impl_vulkan.cpp (and other third-party Vulkan code written against the
// upstream headers) still uses the 1.0 names, so we redeclare the missing
// symbols with their canonical Khronos values. The shared vulkan.library
// dispatched by SDL2 implements the legacy 1.0 barrier path natively.

#include <vulkan/vulkan_core.h>

// AmigaOS4 vulkan.library is dispatched through an IVulkan interface pointer.
// <proto/vulkan.h> + <inline4/vulkan.h> turn bare `vkXxx(args)` calls into
// `IVulkan->vkXxx(args)` invocations. WoWee's renderer makes direct calls
// like `vkDeviceWaitIdle(device)` so we want this on by default.
//
// However, third-party code such as VMA uses bare `vkXxx` identifiers as
// struct field names and as function-pointer values, which the macros break.
// Such translation units must define WOWEE_AMIGA_NO_VULKAN_INLINE *before*
// any include (passed via -D on the compiler command line) to opt out.
#if !defined(WOWEE_AMIGA_NO_VULKAN_INLINE)
#  include <proto/vulkan.h>
#endif

#ifdef __cplusplus
extern "C" {
#endif

#ifndef VK_STRUCTURE_TYPE_MEMORY_BARRIER
#define VK_STRUCTURE_TYPE_MEMORY_BARRIER         ((VkStructureType)46)
#endif
#ifndef VK_STRUCTURE_TYPE_BUFFER_MEMORY_BARRIER
#define VK_STRUCTURE_TYPE_BUFFER_MEMORY_BARRIER  ((VkStructureType)44)
#endif
#ifndef VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER
#define VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER   ((VkStructureType)45)
#endif

#ifndef VK_PIPELINE_STAGE_DRAW_INDIRECT_BIT
#define VK_PIPELINE_STAGE_DRAW_INDIRECT_BIT                    0x00000002u
#endif
#ifndef VK_PIPELINE_STAGE_VERTEX_INPUT_BIT
#define VK_PIPELINE_STAGE_VERTEX_INPUT_BIT                     0x00000004u
#endif
#ifndef VK_PIPELINE_STAGE_VERTEX_SHADER_BIT
#define VK_PIPELINE_STAGE_VERTEX_SHADER_BIT                    0x00000008u
#endif
#ifndef VK_PIPELINE_STAGE_TESSELLATION_CONTROL_SHADER_BIT
#define VK_PIPELINE_STAGE_TESSELLATION_CONTROL_SHADER_BIT      0x00000010u
#endif
#ifndef VK_PIPELINE_STAGE_TESSELLATION_EVALUATION_SHADER_BIT
#define VK_PIPELINE_STAGE_TESSELLATION_EVALUATION_SHADER_BIT   0x00000020u
#endif
#ifndef VK_PIPELINE_STAGE_GEOMETRY_SHADER_BIT
#define VK_PIPELINE_STAGE_GEOMETRY_SHADER_BIT                  0x00000040u
#endif
#ifndef VK_PIPELINE_STAGE_FRAGMENT_SHADER_BIT
#define VK_PIPELINE_STAGE_FRAGMENT_SHADER_BIT                  0x00000080u
#endif
#ifndef VK_PIPELINE_STAGE_EARLY_FRAGMENT_TESTS_BIT
#define VK_PIPELINE_STAGE_EARLY_FRAGMENT_TESTS_BIT             0x00000100u
#endif
#ifndef VK_PIPELINE_STAGE_LATE_FRAGMENT_TESTS_BIT
#define VK_PIPELINE_STAGE_LATE_FRAGMENT_TESTS_BIT              0x00000200u
#endif
#ifndef VK_PIPELINE_STAGE_COMPUTE_SHADER_BIT
#define VK_PIPELINE_STAGE_COMPUTE_SHADER_BIT                   0x00000800u
#endif
#ifndef VK_PIPELINE_STAGE_TRANSFER_BIT
#define VK_PIPELINE_STAGE_TRANSFER_BIT                         0x00001000u
#endif
#ifndef VK_PIPELINE_STAGE_HOST_BIT
#define VK_PIPELINE_STAGE_HOST_BIT                             0x00004000u
#endif
#ifndef VK_PIPELINE_STAGE_ALL_GRAPHICS_BIT
#define VK_PIPELINE_STAGE_ALL_GRAPHICS_BIT                     0x00008000u
#endif
#ifndef VK_PIPELINE_STAGE_ALL_COMMANDS_BIT
#define VK_PIPELINE_STAGE_ALL_COMMANDS_BIT                     0x00010000u
#endif

#ifndef VK_ACCESS_INDIRECT_COMMAND_READ_BIT
#define VK_ACCESS_INDIRECT_COMMAND_READ_BIT             0x00000001u
#endif
#ifndef VK_ACCESS_INDEX_READ_BIT
#define VK_ACCESS_INDEX_READ_BIT                        0x00000002u
#endif
#ifndef VK_ACCESS_VERTEX_ATTRIBUTE_READ_BIT
#define VK_ACCESS_VERTEX_ATTRIBUTE_READ_BIT             0x00000004u
#endif
#ifndef VK_ACCESS_UNIFORM_READ_BIT
#define VK_ACCESS_UNIFORM_READ_BIT                      0x00000008u
#endif
#ifndef VK_ACCESS_INPUT_ATTACHMENT_READ_BIT
#define VK_ACCESS_INPUT_ATTACHMENT_READ_BIT             0x00000010u
#endif
#ifndef VK_ACCESS_SHADER_READ_BIT
#define VK_ACCESS_SHADER_READ_BIT                       0x00000020u
#endif
#ifndef VK_ACCESS_SHADER_WRITE_BIT
#define VK_ACCESS_SHADER_WRITE_BIT                      0x00000040u
#endif
#ifndef VK_ACCESS_COLOR_ATTACHMENT_READ_BIT
#define VK_ACCESS_COLOR_ATTACHMENT_READ_BIT             0x00000080u
#endif
#ifndef VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT
#define VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT            0x00000100u
#endif
#ifndef VK_ACCESS_DEPTH_STENCIL_ATTACHMENT_READ_BIT
#define VK_ACCESS_DEPTH_STENCIL_ATTACHMENT_READ_BIT     0x00000200u
#endif
#ifndef VK_ACCESS_DEPTH_STENCIL_ATTACHMENT_WRITE_BIT
#define VK_ACCESS_DEPTH_STENCIL_ATTACHMENT_WRITE_BIT    0x00000400u
#endif
#ifndef VK_ACCESS_TRANSFER_READ_BIT
#define VK_ACCESS_TRANSFER_READ_BIT                     0x00000800u
#endif
#ifndef VK_ACCESS_TRANSFER_WRITE_BIT
#define VK_ACCESS_TRANSFER_WRITE_BIT                    0x00001000u
#endif
#ifndef VK_ACCESS_HOST_READ_BIT
#define VK_ACCESS_HOST_READ_BIT                         0x00002000u
#endif
#ifndef VK_ACCESS_HOST_WRITE_BIT
#define VK_ACCESS_HOST_WRITE_BIT                        0x00004000u
#endif
#ifndef VK_ACCESS_MEMORY_READ_BIT
#define VK_ACCESS_MEMORY_READ_BIT                       0x00008000u
#endif
#ifndef VK_ACCESS_MEMORY_WRITE_BIT
#define VK_ACCESS_MEMORY_WRITE_BIT                      0x00010000u
#endif

#ifndef VK_DEPENDENCY_BY_REGION_BIT
#define VK_DEPENDENCY_BY_REGION_BIT                     0x00000001u
#endif

#ifndef VK_DESCRIPTOR_POOL_CREATE_FREE_DESCRIPTOR_SET_BIT
#define VK_DESCRIPTOR_POOL_CREATE_FREE_DESCRIPTOR_SET_BIT   0x00000001u
#endif

#ifndef VK_STRUCTURE_TYPE_IMAGE_VIEW_USAGE_CREATE_INFO
#define VK_STRUCTURE_TYPE_IMAGE_VIEW_USAGE_CREATE_INFO  ((VkStructureType)1000117002)
#endif

#ifndef VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT
#define VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT ((VkStructureType)1000128004)
#endif
#ifndef VK_STRUCTURE_TYPE_VALIDATION_FEATURES_EXT
#define VK_STRUCTURE_TYPE_VALIDATION_FEATURES_EXT       ((VkStructureType)1000247000)
#endif
#ifndef VK_STRUCTURE_TYPE_VALIDATION_FLAGS_EXT
#define VK_STRUCTURE_TYPE_VALIDATION_FLAGS_EXT          ((VkStructureType)1000061000)
#endif
#ifndef VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_VULKAN_1_1_FEATURES
#define VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_VULKAN_1_1_FEATURES ((VkStructureType)49)
#endif
#ifndef VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_VULKAN_1_2_FEATURES
#define VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_VULKAN_1_2_FEATURES ((VkStructureType)51)
#endif

#ifndef VK_EXT_DEBUG_UTILS_EXTENSION_NAME
#define VK_EXT_DEBUG_UTILS_EXTENSION_NAME               "VK_EXT_debug_utils"
#endif
#ifndef VK_KHR_GET_PHYSICAL_DEVICE_PROPERTIES_2_EXTENSION_NAME
#define VK_KHR_GET_PHYSICAL_DEVICE_PROPERTIES_2_EXTENSION_NAME "VK_KHR_get_physical_device_properties2"
#endif

// AmigaOS4's vulkan_core.h only exposes VK_SAMPLE_COUNT_1_BIT in the enum
// (no multisampling support). Provide the canonical values so code that
// queries supported counts compiles; runtime code should still consult
// VkSampleCountFlags fields rather than assume any of these are usable.
// Cast to VkSampleCountFlagBits so they're usable in enum-typed contexts.
#ifndef VK_SAMPLE_COUNT_2_BIT
#define VK_SAMPLE_COUNT_2_BIT  ((VkSampleCountFlagBits)0x00000002u)
#endif
#ifndef VK_SAMPLE_COUNT_4_BIT
#define VK_SAMPLE_COUNT_4_BIT  ((VkSampleCountFlagBits)0x00000004u)
#endif
#ifndef VK_SAMPLE_COUNT_8_BIT
#define VK_SAMPLE_COUNT_8_BIT  ((VkSampleCountFlagBits)0x00000008u)
#endif
#ifndef VK_SAMPLE_COUNT_16_BIT
#define VK_SAMPLE_COUNT_16_BIT ((VkSampleCountFlagBits)0x00000010u)
#endif
#ifndef VK_SAMPLE_COUNT_32_BIT
#define VK_SAMPLE_COUNT_32_BIT ((VkSampleCountFlagBits)0x00000020u)
#endif
#ifndef VK_SAMPLE_COUNT_64_BIT
#define VK_SAMPLE_COUNT_64_BIT ((VkSampleCountFlagBits)0x00000040u)
#endif

// Renderpass-2 (Vulkan 1.2) structure types. The driver may return NULL for
// vkCreateRenderPass2 — callers should check before dispatching.
#ifndef VK_STRUCTURE_TYPE_ATTACHMENT_DESCRIPTION_2
#define VK_STRUCTURE_TYPE_ATTACHMENT_DESCRIPTION_2 ((VkStructureType)1000109000)
#endif
#ifndef VK_STRUCTURE_TYPE_ATTACHMENT_REFERENCE_2
#define VK_STRUCTURE_TYPE_ATTACHMENT_REFERENCE_2   ((VkStructureType)1000109001)
#endif
#ifndef VK_STRUCTURE_TYPE_SUBPASS_DESCRIPTION_2
#define VK_STRUCTURE_TYPE_SUBPASS_DESCRIPTION_2    ((VkStructureType)1000109002)
#endif
#ifndef VK_STRUCTURE_TYPE_SUBPASS_DEPENDENCY_2
#define VK_STRUCTURE_TYPE_SUBPASS_DEPENDENCY_2     ((VkStructureType)1000109003)
#endif
#ifndef VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_DEPTH_STENCIL_RESOLVE_PROPERTIES
#define VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_DEPTH_STENCIL_RESOLVE_PROPERTIES ((VkStructureType)1000199000)
#endif
#ifndef VK_STRUCTURE_TYPE_SUBPASS_DESCRIPTION_DEPTH_STENCIL_RESOLVE
#define VK_STRUCTURE_TYPE_SUBPASS_DESCRIPTION_DEPTH_STENCIL_RESOLVE ((VkStructureType)1000199001)
#endif
#ifndef VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_COHERENT_MEMORY_FEATURES_AMD
#define VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_COHERENT_MEMORY_FEATURES_AMD ((VkStructureType)1000229000)
#endif

#ifndef VK_AMD_DEVICE_COHERENT_MEMORY_EXTENSION_NAME
#define VK_AMD_DEVICE_COHERENT_MEMORY_EXTENSION_NAME "VK_AMD_device_coherent_memory"
#endif

#ifndef VK_REMAINING_MIP_LEVELS
#define VK_REMAINING_MIP_LEVELS    (~0U)
#endif
#ifndef VK_REMAINING_ARRAY_LAYERS
#define VK_REMAINING_ARRAY_LAYERS  (~0U)
#endif
#ifndef VK_IMAGE_LAYOUT_DEPTH_STENCIL_READ_ONLY_OPTIMAL
#define VK_IMAGE_LAYOUT_DEPTH_STENCIL_READ_ONLY_OPTIMAL ((VkImageLayout)4)
#endif

// Texture formats / sampler border colors / format-feature bits absent from
// the AmigaOS4 SDK headers but needed by upstream-style renderer code. The
// driver may not support all of these — runtime queries should still gate
// usage — but the values are canonical so portable code compiles.
#ifndef VK_FORMAT_R8_UNORM
#define VK_FORMAT_R8_UNORM      ((VkFormat)9)
#endif
#ifndef VK_FORMAT_R8G8_UNORM
#define VK_FORMAT_R8G8_UNORM    ((VkFormat)16)
#endif
#ifndef VK_FORMAT_R8G8B8_UNORM
#define VK_FORMAT_R8G8B8_UNORM  ((VkFormat)23)
#endif
#ifndef VK_FORMAT_R16G16_SFLOAT
#define VK_FORMAT_R16G16_SFLOAT ((VkFormat)83)
#endif
#ifndef VK_FORMAT_R16G16B16A16_SFLOAT
#define VK_FORMAT_R16G16B16A16_SFLOAT ((VkFormat)97)
#endif
#ifndef VK_FORMAT_R8G8B8A8_SINT
#define VK_FORMAT_R8G8B8A8_SINT ((VkFormat)42)
#endif

#ifndef VK_STRUCTURE_TYPE_COMMAND_BUFFER_INHERITANCE_INFO
#define VK_STRUCTURE_TYPE_COMMAND_BUFFER_INHERITANCE_INFO ((VkStructureType)41)
#endif
#ifndef VK_BORDER_COLOR_INT_OPAQUE_BLACK
#define VK_BORDER_COLOR_INT_OPAQUE_BLACK  ((VkBorderColor)3)
#endif
#ifndef VK_FORMAT_FEATURE_SAMPLED_IMAGE_FILTER_LINEAR_BIT
#define VK_FORMAT_FEATURE_SAMPLED_IMAGE_FILTER_LINEAR_BIT 0x00001000u
#endif

#ifndef VK_PIPELINE_CREATE_DISABLE_OPTIMIZATION_BIT
#define VK_PIPELINE_CREATE_DISABLE_OPTIMIZATION_BIT  0x00000001u
#endif
#ifndef VK_PIPELINE_CREATE_ALLOW_DERIVATIVES_BIT
#define VK_PIPELINE_CREATE_ALLOW_DERIVATIVES_BIT     0x00000002u
#endif
#ifndef VK_PIPELINE_CREATE_DERIVATIVE_BIT
#define VK_PIPELINE_CREATE_DERIVATIVE_BIT            0x00000004u
#endif

#ifndef VK_IMAGE_USAGE_STORAGE_BIT
#define VK_IMAGE_USAGE_STORAGE_BIT                   0x00000008u
#endif

// VkResolveModeFlagBits enum is already defined in the AmigaOS4 header but
// only with VK_RESOLVE_MODE_NONE — add the rest as #defines so they evaluate
// to integer constants compatible with the existing enum type.
#ifndef VK_RESOLVE_MODE_SAMPLE_ZERO_BIT
#define VK_RESOLVE_MODE_SAMPLE_ZERO_BIT  ((VkResolveModeFlagBits)0x00000001)
#endif
#ifndef VK_RESOLVE_MODE_AVERAGE_BIT
#define VK_RESOLVE_MODE_AVERAGE_BIT      ((VkResolveModeFlagBits)0x00000002)
#endif
#ifndef VK_RESOLVE_MODE_MIN_BIT
#define VK_RESOLVE_MODE_MIN_BIT          ((VkResolveModeFlagBits)0x00000004)
#endif
#ifndef VK_RESOLVE_MODE_MAX_BIT
#define VK_RESOLVE_MODE_MAX_BIT          ((VkResolveModeFlagBits)0x00000008)
#endif
typedef VkFlags VkResolveModeFlags;

typedef struct VkPhysicalDeviceDepthStencilResolveProperties {
    VkStructureType       sType;
    void*                 pNext;
    VkResolveModeFlags    supportedDepthResolveModes;
    VkResolveModeFlags    supportedStencilResolveModes;
    VkBool32              independentResolveNone;
    VkBool32              independentResolve;
} VkPhysicalDeviceDepthStencilResolveProperties;

typedef struct VkPhysicalDeviceCoherentMemoryFeaturesAMD {
    VkStructureType sType;
    void*           pNext;
    VkBool32        deviceCoherentMemory;
} VkPhysicalDeviceCoherentMemoryFeaturesAMD;

typedef struct VkSubpassDependency2 {
    VkStructureType         sType;
    const void*             pNext;
    uint32_t                srcSubpass;
    uint32_t                dstSubpass;
    VkPipelineStageFlags    srcStageMask;
    VkPipelineStageFlags    dstStageMask;
    VkAccessFlags           srcAccessMask;
    VkAccessFlags           dstAccessMask;
    VkDependencyFlags       dependencyFlags;
    int32_t                 viewOffset;
} VkSubpassDependency2;

typedef struct VkSubpassDescriptionDepthStencilResolve {
    VkStructureType                  sType;
    const void*                      pNext;
    VkResolveModeFlagBits            depthResolveMode;
    VkResolveModeFlagBits            stencilResolveMode;
    const VkAttachmentReference2*    pDepthStencilResolveAttachment;
} VkSubpassDescriptionDepthStencilResolve;

typedef VkResult (VKAPI_PTR *PFN_vkCreateRenderPass2)(VkDevice, const VkRenderPassCreateInfo2*, const VkAllocationCallbacks*, VkRenderPass*);

// vkCreateRenderPass2 / vkCmdBlitImage are not exposed by AmigaOS4
// vulkan.library. Provide stubs so direct call sites compile; at runtime the
// renderer should detect AmigaOS4 and skip these features (no-op blits,
// fallback to renderpass-1).
static inline VkResult vkCreateRenderPass2(VkDevice, const VkRenderPassCreateInfo2*, const VkAllocationCallbacks*, VkRenderPass*) {
    return VK_ERROR_EXTENSION_NOT_PRESENT;
}

static inline void vkCmdBlitImage(VkCommandBuffer, VkImage, VkImageLayout, VkImage, VkImageLayout, uint32_t, const VkImageBlit*, VkFilter) {
    // AmigaOS4 vulkan.library does not implement vkCmdBlitImage — caller
    // should mip-generate via a compute shader or copy path instead.
}

static inline void vkCmdExecuteCommands(VkCommandBuffer, uint32_t, const VkCommandBuffer*) {
    // AmigaOS4 vulkan.library does not implement secondary command buffer
    // execution — renderer should record everything into the primary buffer.
}

static inline void vkCmdClearColorImage(VkCommandBuffer, VkImage, VkImageLayout, const VkClearColorValue*, uint32_t, const VkImageSubresourceRange*) {
    // AmigaOS4 vulkan.library does not implement vkCmdClearColorImage —
    // callers should clear via render-pass loadOp = VK_ATTACHMENT_LOAD_OP_CLEAR.
}

static inline void vkCmdSetDepthBias(VkCommandBuffer, float, float, float) {
    // No-op stub: AmigaOS4 vulkan.library does not expose dynamic depth-bias state.
}

static inline void vkCmdClearDepthStencilImage(VkCommandBuffer, VkImage, VkImageLayout, const VkClearDepthStencilValue*, uint32_t, const VkImageSubresourceRange*) {
    // No-op stub. Clear via render-pass loadOp = VK_ATTACHMENT_LOAD_OP_CLEAR instead.
}

static inline VkResult vkCreateComputePipelines(VkDevice, VkPipelineCache, uint32_t, const VkComputePipelineCreateInfo*, const VkAllocationCallbacks*, VkPipeline*) {
    // AmigaOS4 vulkan.library does not implement compute pipelines.
    return VK_ERROR_FEATURE_NOT_PRESENT;
}

static inline void vkCmdDispatch(VkCommandBuffer, uint32_t, uint32_t, uint32_t) {
    // No-op stub: AmigaOS4 has no compute support.
}

// VkBufferUsageFlagBits / VkSwapchainCreateFlagBitsKHR are referenced as
// parameter types in some third-party code; the AmigaOS4 header only exposes
// the corresponding *Flags typedefs. Alias them.
typedef VkBufferUsageFlags VkBufferUsageFlagBits;
typedef VkFlags VkSwapchainCreateFlagBitsKHR;

// VkImageViewUsageCreateInfo (Vulkan 1.1 / KHR_maintenance2 chain struct).
typedef struct VkImageViewUsageCreateInfo {
    VkStructureType    sType;
    const void*        pNext;
    VkImageUsageFlags  usage;
} VkImageViewUsageCreateInfo;

// Legacy Vulkan 1.0 barrier structs. Layouts match the canonical Khronos
// definitions exactly; vkCmdPipelineBarrier on AmigaOS4 takes `const void*`
// for the barrier arrays so passing pointers to these structs is well-formed.
typedef struct VkMemoryBarrier {
    VkStructureType    sType;
    const void*        pNext;
    VkAccessFlags      srcAccessMask;
    VkAccessFlags      dstAccessMask;
} VkMemoryBarrier;

typedef struct VkBufferMemoryBarrier {
    VkStructureType    sType;
    const void*        pNext;
    VkAccessFlags      srcAccessMask;
    VkAccessFlags      dstAccessMask;
    uint32_t           srcQueueFamilyIndex;
    uint32_t           dstQueueFamilyIndex;
    VkBuffer           buffer;
    VkDeviceSize       offset;
    VkDeviceSize       size;
} VkBufferMemoryBarrier;

typedef struct VkImageMemoryBarrier {
    VkStructureType            sType;
    const void*                pNext;
    VkAccessFlags              srcAccessMask;
    VkAccessFlags              dstAccessMask;
    VkImageLayout              oldLayout;
    VkImageLayout              newLayout;
    uint32_t                   srcQueueFamilyIndex;
    uint32_t                   dstQueueFamilyIndex;
    VkImage                    image;
    VkImageSubresourceRange    subresourceRange;
} VkImageMemoryBarrier;

// VkCopyDescriptorSet — used by vkUpdateDescriptorSets.
typedef struct VkCopyDescriptorSet {
    VkStructureType    sType;
    const void*        pNext;
    VkDescriptorSet    srcSet;
    uint32_t           srcBinding;
    uint32_t           srcArrayElement;
    VkDescriptorSet    dstSet;
    uint32_t           dstBinding;
    uint32_t           dstArrayElement;
    uint32_t           descriptorCount;
} VkCopyDescriptorSet;

// VkPhysicalDeviceVulkan1{1,2,3}Features — aggregate feature structs used by
// vk-bootstrap's PhysicalDeviceSelector. On AmigaOS4 they are not present in
// the SDK; expose minimal layouts that match the canonical Khronos definitions
// (only the fields vk-bootstrap actually reads/writes).
typedef struct VkPhysicalDeviceVulkan11Features {
    VkStructureType sType;
    void*           pNext;
    VkBool32 storageBuffer16BitAccess;
    VkBool32 uniformAndStorageBuffer16BitAccess;
    VkBool32 storagePushConstant16;
    VkBool32 storageInputOutput16;
    VkBool32 multiview;
    VkBool32 multiviewGeometryShader;
    VkBool32 multiviewTessellationShader;
    VkBool32 variablePointersStorageBuffer;
    VkBool32 variablePointers;
    VkBool32 protectedMemory;
    VkBool32 samplerYcbcrConversion;
    VkBool32 shaderDrawParameters;
} VkPhysicalDeviceVulkan11Features;

typedef struct VkPhysicalDeviceVulkan12Features {
    VkStructureType sType;
    void*           pNext;
    VkBool32 samplerMirrorClampToEdge;
    VkBool32 drawIndirectCount;
    VkBool32 storageBuffer8BitAccess;
    VkBool32 uniformAndStorageBuffer8BitAccess;
    VkBool32 storagePushConstant8;
    VkBool32 shaderBufferInt64Atomics;
    VkBool32 shaderSharedInt64Atomics;
    VkBool32 shaderFloat16;
    VkBool32 shaderInt8;
    VkBool32 descriptorIndexing;
    VkBool32 shaderInputAttachmentArrayDynamicIndexing;
    VkBool32 shaderUniformTexelBufferArrayDynamicIndexing;
    VkBool32 shaderStorageTexelBufferArrayDynamicIndexing;
    VkBool32 shaderUniformBufferArrayNonUniformIndexing;
    VkBool32 shaderSampledImageArrayNonUniformIndexing;
    VkBool32 shaderStorageBufferArrayNonUniformIndexing;
    VkBool32 shaderStorageImageArrayNonUniformIndexing;
    VkBool32 shaderInputAttachmentArrayNonUniformIndexing;
    VkBool32 shaderUniformTexelBufferArrayNonUniformIndexing;
    VkBool32 shaderStorageTexelBufferArrayNonUniformIndexing;
    VkBool32 descriptorBindingUniformBufferUpdateAfterBind;
    VkBool32 descriptorBindingSampledImageUpdateAfterBind;
    VkBool32 descriptorBindingStorageImageUpdateAfterBind;
    VkBool32 descriptorBindingStorageBufferUpdateAfterBind;
    VkBool32 descriptorBindingUniformTexelBufferUpdateAfterBind;
    VkBool32 descriptorBindingStorageTexelBufferUpdateAfterBind;
    VkBool32 descriptorBindingUpdateUnusedWhilePending;
    VkBool32 descriptorBindingPartiallyBound;
    VkBool32 descriptorBindingVariableDescriptorCount;
    VkBool32 runtimeDescriptorArray;
    VkBool32 samplerFilterMinmax;
    VkBool32 scalarBlockLayout;
    VkBool32 imagelessFramebuffer;
    VkBool32 uniformBufferStandardLayout;
    VkBool32 shaderSubgroupExtendedTypes;
    VkBool32 separateDepthStencilLayouts;
    VkBool32 hostQueryReset;
    VkBool32 timelineSemaphore;
    VkBool32 bufferDeviceAddress;
    VkBool32 bufferDeviceAddressCaptureReplay;
    VkBool32 bufferDeviceAddressMultiDevice;
    VkBool32 vulkanMemoryModel;
    VkBool32 vulkanMemoryModelDeviceScope;
    VkBool32 vulkanMemoryModelAvailabilityVisibilityChains;
    VkBool32 shaderOutputViewportIndex;
    VkBool32 shaderOutputLayer;
    VkBool32 subgroupBroadcastDynamicId;
} VkPhysicalDeviceVulkan12Features;

typedef struct VkPhysicalDeviceVulkan13Features {
    VkStructureType sType;
    void*           pNext;
    VkBool32 robustImageAccess;
    VkBool32 inlineUniformBlock;
    VkBool32 descriptorBindingInlineUniformBlockUpdateAfterBind;
    VkBool32 pipelineCreationCacheControl;
    VkBool32 privateData;
    VkBool32 shaderDemoteToHelperInvocation;
    VkBool32 shaderTerminateInvocation;
    VkBool32 subgroupSizeControl;
    VkBool32 computeFullSubgroups;
    VkBool32 synchronization2;
    VkBool32 textureCompressionASTC_HDR;
    VkBool32 shaderZeroInitializeWorkgroupMemory;
    VkBool32 dynamicRendering;
    VkBool32 shaderIntegerDotProduct;
    VkBool32 maintenance4;
} VkPhysicalDeviceVulkan13Features;

// VK_EXT_debug_utils — minimal surface needed by vk-bootstrap.
VK_DEFINE_NON_DISPATCHABLE_HANDLE(VkDebugUtilsMessengerEXT)

typedef VkFlags VkDebugUtilsMessengerCreateFlagsEXT;
typedef VkFlags VkDebugUtilsMessengerCallbackDataFlagsEXT;
typedef VkFlags VkDebugUtilsMessageTypeFlagsEXT;
typedef VkFlags VkDebugUtilsMessageSeverityFlagsEXT;

typedef enum VkDebugUtilsMessageSeverityFlagBitsEXT {
    VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT = 0x00000001,
    VK_DEBUG_UTILS_MESSAGE_SEVERITY_INFO_BIT_EXT    = 0x00000010,
    VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT = 0x00000100,
    VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT   = 0x00001000,
    VK_DEBUG_UTILS_MESSAGE_SEVERITY_FLAG_BITS_MAX_ENUM_EXT = 0x7FFFFFFF
} VkDebugUtilsMessageSeverityFlagBitsEXT;

typedef enum VkDebugUtilsMessageTypeFlagBitsEXT {
    VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT     = 0x00000001,
    VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT  = 0x00000002,
    VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT = 0x00000004,
    VK_DEBUG_UTILS_MESSAGE_TYPE_DEVICE_ADDRESS_BINDING_BIT_EXT = 0x00000008,
    VK_DEBUG_UTILS_MESSAGE_TYPE_FLAG_BITS_MAX_ENUM_EXT = 0x7FFFFFFF
} VkDebugUtilsMessageTypeFlagBitsEXT;

typedef struct VkDebugUtilsLabelEXT {
    VkStructureType sType;
    const void*     pNext;
    const char*     pLabelName;
    float           color[4];
} VkDebugUtilsLabelEXT;

typedef struct VkDebugUtilsObjectNameInfoEXT {
    VkStructureType sType;
    const void*     pNext;
    VkObjectType    objectType;
    uint64_t        objectHandle;
    const char*     pObjectName;
} VkDebugUtilsObjectNameInfoEXT;

typedef struct VkDebugUtilsMessengerCallbackDataEXT {
    VkStructureType                              sType;
    const void*                                  pNext;
    VkDebugUtilsMessengerCallbackDataFlagsEXT    flags;
    const char*                                  pMessageIdName;
    int32_t                                      messageIdNumber;
    const char*                                  pMessage;
    uint32_t                                     queueLabelCount;
    const VkDebugUtilsLabelEXT*                  pQueueLabels;
    uint32_t                                     cmdBufLabelCount;
    const VkDebugUtilsLabelEXT*                  pCmdBufLabels;
    uint32_t                                     objectCount;
    const VkDebugUtilsObjectNameInfoEXT*         pObjects;
} VkDebugUtilsMessengerCallbackDataEXT;

typedef VkBool32 (VKAPI_PTR *PFN_vkDebugUtilsMessengerCallbackEXT)(
    VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity,
    VkDebugUtilsMessageTypeFlagsEXT messageTypes,
    const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData,
    void* pUserData);

typedef struct VkDebugUtilsMessengerCreateInfoEXT {
    VkStructureType                         sType;
    const void*                             pNext;
    VkDebugUtilsMessengerCreateFlagsEXT     flags;
    VkDebugUtilsMessageSeverityFlagsEXT     messageSeverity;
    VkDebugUtilsMessageTypeFlagsEXT         messageType;
    PFN_vkDebugUtilsMessengerCallbackEXT    pfnUserCallback;
    void*                                   pUserData;
} VkDebugUtilsMessengerCreateInfoEXT;

// VK_EXT_validation_flags / VK_EXT_validation_features — also needed by
// vk-bootstrap's InstanceBuilder.
typedef enum VkValidationCheckEXT {
    VK_VALIDATION_CHECK_ALL_EXT     = 0,
    VK_VALIDATION_CHECK_SHADERS_EXT = 1,
    VK_VALIDATION_CHECK_MAX_ENUM_EXT = 0x7FFFFFFF
} VkValidationCheckEXT;

typedef struct VkValidationFlagsEXT {
    VkStructureType              sType;
    const void*                  pNext;
    uint32_t                     disabledValidationCheckCount;
    const VkValidationCheckEXT*  pDisabledValidationChecks;
} VkValidationFlagsEXT;

typedef enum VkValidationFeatureEnableEXT {
    VK_VALIDATION_FEATURE_ENABLE_GPU_ASSISTED_EXT = 0,
    VK_VALIDATION_FEATURE_ENABLE_GPU_ASSISTED_RESERVE_BINDING_SLOT_EXT = 1,
    VK_VALIDATION_FEATURE_ENABLE_BEST_PRACTICES_EXT = 2,
    VK_VALIDATION_FEATURE_ENABLE_DEBUG_PRINTF_EXT = 3,
    VK_VALIDATION_FEATURE_ENABLE_SYNCHRONIZATION_VALIDATION_EXT = 4,
    VK_VALIDATION_FEATURE_ENABLE_MAX_ENUM_EXT = 0x7FFFFFFF
} VkValidationFeatureEnableEXT;

typedef enum VkValidationFeatureDisableEXT {
    VK_VALIDATION_FEATURE_DISABLE_ALL_EXT = 0,
    VK_VALIDATION_FEATURE_DISABLE_SHADERS_EXT = 1,
    VK_VALIDATION_FEATURE_DISABLE_THREAD_SAFETY_EXT = 2,
    VK_VALIDATION_FEATURE_DISABLE_API_PARAMETERS_EXT = 3,
    VK_VALIDATION_FEATURE_DISABLE_OBJECT_LIFETIMES_EXT = 4,
    VK_VALIDATION_FEATURE_DISABLE_CORE_CHECKS_EXT = 5,
    VK_VALIDATION_FEATURE_DISABLE_UNIQUE_HANDLES_EXT = 6,
    VK_VALIDATION_FEATURE_DISABLE_SHADER_VALIDATION_CACHE_EXT = 7,
    VK_VALIDATION_FEATURE_DISABLE_MAX_ENUM_EXT = 0x7FFFFFFF
} VkValidationFeatureDisableEXT;

typedef struct VkValidationFeaturesEXT {
    VkStructureType                       sType;
    const void*                           pNext;
    uint32_t                              enabledValidationFeatureCount;
    const VkValidationFeatureEnableEXT*   pEnabledValidationFeatures;
    uint32_t                              disabledValidationFeatureCount;
    const VkValidationFeatureDisableEXT*  pDisabledValidationFeatures;
} VkValidationFeaturesEXT;

// PFN_* typedefs for Vulkan 1.0 entry points absent from the AmigaOS4 SDK.
// Signatures match the canonical Khronos definitions exactly. The driver may
// not actually export many of these — vkGetDeviceProcAddr will return NULL —
// but the dispatch table just needs them to compile.
typedef VkResult (VKAPI_PTR *PFN_vkEnumerateDeviceLayerProperties)(VkPhysicalDevice, uint32_t*, VkLayerProperties*);
typedef void     (VKAPI_PTR *PFN_vkGetPhysicalDeviceSparseImageFormatProperties)(VkPhysicalDevice, VkFormat, VkImageType, VkSampleCountFlagBits, VkImageUsageFlags, VkImageTiling, uint32_t*, VkSparseImageFormatProperties*);
typedef void     (VKAPI_PTR *PFN_vkGetDeviceMemoryCommitment)(VkDevice, VkDeviceMemory, VkDeviceSize*);
typedef void     (VKAPI_PTR *PFN_vkGetImageSparseMemoryRequirements)(VkDevice, VkImage, uint32_t*, VkSparseImageMemoryRequirements*);
typedef VkResult (VKAPI_PTR *PFN_vkQueueBindSparse)(VkQueue, uint32_t, const VkBindSparseInfo*, VkFence);
typedef VkResult (VKAPI_PTR *PFN_vkCreateEvent)(VkDevice, const VkEventCreateInfo*, const VkAllocationCallbacks*, VkEvent*);
typedef void     (VKAPI_PTR *PFN_vkDestroyEvent)(VkDevice, VkEvent, const VkAllocationCallbacks*);
typedef VkResult (VKAPI_PTR *PFN_vkGetEventStatus)(VkDevice, VkEvent);
typedef VkResult (VKAPI_PTR *PFN_vkSetEvent)(VkDevice, VkEvent);
typedef VkResult (VKAPI_PTR *PFN_vkResetEvent)(VkDevice, VkEvent);
typedef VkResult (VKAPI_PTR *PFN_vkCreateQueryPool)(VkDevice, const VkQueryPoolCreateInfo*, const VkAllocationCallbacks*, VkQueryPool*);
typedef void     (VKAPI_PTR *PFN_vkDestroyQueryPool)(VkDevice, VkQueryPool, const VkAllocationCallbacks*);
typedef VkResult (VKAPI_PTR *PFN_vkGetQueryPoolResults)(VkDevice, VkQueryPool, uint32_t, uint32_t, size_t, void*, VkDeviceSize, VkQueryResultFlags);
typedef VkResult (VKAPI_PTR *PFN_vkCreateBufferView)(VkDevice, const VkBufferViewCreateInfo*, const VkAllocationCallbacks*, VkBufferView*);
typedef void     (VKAPI_PTR *PFN_vkDestroyBufferView)(VkDevice, VkBufferView, const VkAllocationCallbacks*);
typedef void     (VKAPI_PTR *PFN_vkGetImageSubresourceLayout)(VkDevice, VkImage, const VkImageSubresource*, VkSubresourceLayout*);
typedef VkResult (VKAPI_PTR *PFN_vkCreateComputePipelines)(VkDevice, VkPipelineCache, uint32_t, const VkComputePipelineCreateInfo*, const VkAllocationCallbacks*, VkPipeline*);
typedef void     (VKAPI_PTR *PFN_vkGetRenderAreaGranularity)(VkDevice, VkRenderPass, VkExtent2D*);

typedef void     (VKAPI_PTR *PFN_vkCmdSetLineWidth)(VkCommandBuffer, float);
typedef void     (VKAPI_PTR *PFN_vkCmdSetDepthBias)(VkCommandBuffer, float, float, float);
typedef void     (VKAPI_PTR *PFN_vkCmdSetBlendConstants)(VkCommandBuffer, const float[4]);
typedef void     (VKAPI_PTR *PFN_vkCmdSetDepthBounds)(VkCommandBuffer, float, float);
typedef void     (VKAPI_PTR *PFN_vkCmdSetStencilCompareMask)(VkCommandBuffer, VkStencilFaceFlags, uint32_t);
typedef void     (VKAPI_PTR *PFN_vkCmdSetStencilWriteMask)(VkCommandBuffer, VkStencilFaceFlags, uint32_t);
typedef void     (VKAPI_PTR *PFN_vkCmdSetStencilReference)(VkCommandBuffer, VkStencilFaceFlags, uint32_t);
typedef void     (VKAPI_PTR *PFN_vkCmdDrawIndirect)(VkCommandBuffer, VkBuffer, VkDeviceSize, uint32_t, uint32_t);
typedef void     (VKAPI_PTR *PFN_vkCmdDrawIndexedIndirect)(VkCommandBuffer, VkBuffer, VkDeviceSize, uint32_t, uint32_t);
typedef void     (VKAPI_PTR *PFN_vkCmdDispatch)(VkCommandBuffer, uint32_t, uint32_t, uint32_t);
typedef void     (VKAPI_PTR *PFN_vkCmdDispatchIndirect)(VkCommandBuffer, VkBuffer, VkDeviceSize);
typedef void     (VKAPI_PTR *PFN_vkCmdBlitImage)(VkCommandBuffer, VkImage, VkImageLayout, VkImage, VkImageLayout, uint32_t, const VkImageBlit*, VkFilter);
typedef void     (VKAPI_PTR *PFN_vkCmdClearColorImage)(VkCommandBuffer, VkImage, VkImageLayout, const VkClearColorValue*, uint32_t, const VkImageSubresourceRange*);
typedef void     (VKAPI_PTR *PFN_vkCmdClearDepthStencilImage)(VkCommandBuffer, VkImage, VkImageLayout, const VkClearDepthStencilValue*, uint32_t, const VkImageSubresourceRange*);
typedef void     (VKAPI_PTR *PFN_vkCmdClearAttachments)(VkCommandBuffer, uint32_t, const VkClearAttachment*, uint32_t, const VkClearRect*);
typedef void     (VKAPI_PTR *PFN_vkCmdResolveImage)(VkCommandBuffer, VkImage, VkImageLayout, VkImage, VkImageLayout, uint32_t, const VkImageResolve*);
typedef void     (VKAPI_PTR *PFN_vkCmdSetEvent)(VkCommandBuffer, VkEvent, VkPipelineStageFlags);
typedef void     (VKAPI_PTR *PFN_vkCmdResetEvent)(VkCommandBuffer, VkEvent, VkPipelineStageFlags);
typedef void     (VKAPI_PTR *PFN_vkCmdWaitEvents)(VkCommandBuffer, uint32_t, const VkEvent*, VkPipelineStageFlags, VkPipelineStageFlags, uint32_t, const void*, uint32_t, const void*, uint32_t, const void*);
typedef void     (VKAPI_PTR *PFN_vkCmdBeginQuery)(VkCommandBuffer, VkQueryPool, uint32_t, VkQueryControlFlags);
typedef void     (VKAPI_PTR *PFN_vkCmdEndQuery)(VkCommandBuffer, VkQueryPool, uint32_t);
typedef void     (VKAPI_PTR *PFN_vkCmdResetQueryPool)(VkCommandBuffer, VkQueryPool, uint32_t, uint32_t);
typedef void     (VKAPI_PTR *PFN_vkCmdWriteTimestamp)(VkCommandBuffer, VkPipelineStageFlagBits, VkQueryPool, uint32_t);
typedef void     (VKAPI_PTR *PFN_vkCmdCopyQueryPoolResults)(VkCommandBuffer, VkQueryPool, uint32_t, uint32_t, VkBuffer, VkDeviceSize, VkDeviceSize, VkQueryResultFlags);
typedef void     (VKAPI_PTR *PFN_vkCmdExecuteCommands)(VkCommandBuffer, uint32_t, const VkCommandBuffer*);

// VK_EXT_debug_utils + VK_KHR_get_physical_device_properties2 PFN typedefs.
typedef VkResult (VKAPI_PTR *PFN_vkCreateDebugUtilsMessengerEXT)(VkInstance, const VkDebugUtilsMessengerCreateInfoEXT*, const VkAllocationCallbacks*, VkDebugUtilsMessengerEXT*);
typedef void     (VKAPI_PTR *PFN_vkDestroyDebugUtilsMessengerEXT)(VkInstance, VkDebugUtilsMessengerEXT, const VkAllocationCallbacks*);
typedef void     (VKAPI_PTR *PFN_vkGetPhysicalDeviceFeatures2KHR)(VkPhysicalDevice, VkPhysicalDeviceFeatures2*);

#ifdef __cplusplus
}
#endif

#endif // WOWEE_AMIGAOS4_VULKAN_COMPAT_H
