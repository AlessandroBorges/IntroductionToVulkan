// Copyright 2016 Intel Corporation All Rights Reserved
// 
// Intel makes no representations about the suitability of this software for any purpose.
// THIS SOFTWARE IS PROVIDED ""AS IS."" INTEL SPECIFICALLY DISCLAIMS ALL WARRANTIES,
// EXPRESS OR IMPLIED, AND ALL LIABILITY, INCLUDING CONSEQUENTIAL AND OTHER INDIRECT DAMAGES,
// FOR THE USE OF THIS SOFTWARE, INCLUDING LIABILITY FOR INFRINGEMENT OF ANY PROPRIETARY
// RIGHTS, AND INCLUDING THE WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
// Intel does not assume any responsibility for any errors which may appear in this software
// nor any responsibility to update it.

#if !defined(VULKAN_COMMON_HEADER)
#define VULKAN_COMMON_HEADER

#include <vector>
#include "vulkan.h"
#include "OperatingSystem.h"

namespace ApiWithoutSecrets {

  // ************************************************************ //
  // QueueParameters                                              //
  //                                                              //
  // Vulkan Queue's parameters container class                    //
  // ************************************************************ //
  struct QueueParameters {
    VkQueue                       Handle;
    uint32_t                      FamilyIndex;

    QueueParameters() :
      Handle( VK_NULL_HANDLE ),
      FamilyIndex( 0 ) {
    }
  };

  // ************************************************************ //
  // ImageParameters                                              //
  //                                                              //
  // Vulkan Image's parameters container class                    //
  // ************************************************************ //
  struct ImageParameters {
    VkImage                       Handle;
    VkImageView                   View;
    VkSampler                     Sampler;
    VkDeviceMemory                Memory;

    ImageParameters() :
      Handle( VK_NULL_HANDLE ),
      View( VK_NULL_HANDLE ),
      Sampler( VK_NULL_HANDLE ),
      Memory( VK_NULL_HANDLE ) {
    }
  };

  // ************************************************************ //
  // SwapChainParameters                                          //
  //                                                              //
  // Vulkan SwapChain's parameters container class                //
  // ************************************************************ //
  struct SwapChainParameters {
    VkSwapchainKHR                Handle;
    VkFormat                      Format;
    std::vector<ImageParameters>  Images;
    VkExtent2D                    Extent;

    SwapChainParameters() :
      Handle( VK_NULL_HANDLE ),
      Format( VK_FORMAT_UNDEFINED ),
      Images(),
      Extent() {
    }
  };

  // ************************************************************ //
  // VulkanCommonParameters                                       //
  //                                                              //
  // General Vulkan parameters' container class                   //
  // ************************************************************ //
  struct VulkanCommonParameters {
    VkInstance                    Instance;
    VkPhysicalDevice              PhysicalDevice;
    VkDevice                      Device;
    QueueParameters               GraphicsQueue;
    QueueParameters               PresentQueue;
    VkSurfaceKHR                  PresentationSurface;
    SwapChainParameters           SwapChain;

    VulkanCommonParameters() :
      Instance( VK_NULL_HANDLE ),
      PhysicalDevice( VK_NULL_HANDLE ),
      Device( VK_NULL_HANDLE ),
      GraphicsQueue(),
      PresentQueue(),
      PresentationSurface( VK_NULL_HANDLE ),
      SwapChain() {
    }
  };

  // ************************************************************ //
  // VulkanCommon                                                 //
  //                                                              //
  // Base class for Vulkan more advanced tutorial classes         //
  // ************************************************************ //
  class VulkanCommon : public OS::TutorialBase {
  public:
    VulkanCommon();
    virtual ~VulkanCommon();

    bool                          PrepareVulkan( OS::WindowParameters parameters );
    virtual bool                  OnWindowSizeChanged() final override;

  protected:
    VkPhysicalDevice              GetPhysicalDevice() const;
    VkDevice                      GetDevice() const;

    const QueueParameters         GetGraphicsQueue() const;
    const QueueParameters         GetPresentQueue() const;

    const SwapChainParameters     GetSwapChain() const;

  private:
    OS::LibraryHandle       VulkanLibrary;
    OS::WindowParameters    Window;
    VulkanCommonParameters  Vulkan;

    bool                          LoadVulkanLibrary();
    bool                          LoadExportedEntryPoints();
    bool                          LoadGlobalLevelEntryPoints();
    bool                          CreateInstance();
    bool                          LoadInstanceLevelEntryPoints();
    bool                          CreatePresentationSurface();
    bool                          CreateDevice();
    bool                          CheckPhysicalDeviceProperties( VkPhysicalDevice physical_device, uint32_t &graphics_queue_family_index, uint32_t &present_queue_family_index );
    bool                          LoadDeviceLevelEntryPoints();
    bool                          GetDeviceQueue();
    bool                          CreateSwapChain();
    bool                          CreateSwapChainImageViews();
    virtual bool                  ChildOnWindowSizeChanged() = 0;
    virtual void                  ChildClear() = 0;

    bool                          CheckExtensionAvailability( const char *extension_name, const std::vector<VkExtensionProperties> &available_extensions );
    uint32_t                      GetSwapChainNumImages( VkSurfaceCapabilitiesKHR &surface_capabilities );
    VkSurfaceFormatKHR            GetSwapChainFormat( std::vector<VkSurfaceFormatKHR> &surface_formats );
    VkExtent2D                    GetSwapChainExtent( VkSurfaceCapabilitiesKHR &surface_capabilities );
    VkImageUsageFlags             GetSwapChainUsageFlags( VkSurfaceCapabilitiesKHR &surface_capabilities );
    VkSurfaceTransformFlagBitsKHR GetSwapChainTransform( VkSurfaceCapabilitiesKHR &surface_capabilities );
    VkPresentModeKHR              GetSwapChainPresentMode( std::vector<VkPresentModeKHR> &present_modes );
  };

} // namespace ApiWithoutSecrets

#endif // VULKAN_COMMON_HEADER