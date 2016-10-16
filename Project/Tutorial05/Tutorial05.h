// Copyright 2016 Intel Corporation All Rights Reserved
// 
// Intel makes no representations about the suitability of this software for any purpose.
// THIS SOFTWARE IS PROVIDED ""AS IS."" INTEL SPECIFICALLY DISCLAIMS ALL WARRANTIES,
// EXPRESS OR IMPLIED, AND ALL LIABILITY, INCLUDING CONSEQUENTIAL AND OTHER INDIRECT DAMAGES,
// FOR THE USE OF THIS SOFTWARE, INCLUDING LIABILITY FOR INFRINGEMENT OF ANY PROPRIETARY
// RIGHTS, AND INCLUDING THE WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
// Intel does not assume any responsibility for any errors which may appear in this software
// nor any responsibility to update it.

#if !defined(TUTORIAL_05_HEADER)
#define TUTORIAL_05_HEADER

#include "VulkanCommon.h"
#include "Tools.h"

namespace ApiWithoutSecrets {

  // ************************************************************ //
  // BufferParameters                                             //
  //                                                              //
  // Vulkan Buffer's parameters container class                   //
  // ************************************************************ //
  struct BufferParameters {
    VkBuffer                        Handle;
    VkDeviceMemory                  Memory;
    uint32_t                        Size;

    BufferParameters() :
      Handle( VK_NULL_HANDLE ),
      Memory( VK_NULL_HANDLE ),
      Size( 0 ) {
    }
  };

  // ************************************************************ //
  // VertexData                                                   //
  //                                                              //
  // Struct describing data type and format of vertex attributes  //
  // ************************************************************ //
  struct VertexData {
    float   x, y, z, w;
    float   r, g, b, a;
  };

  // ************************************************************ //
  // RenderingResourcesData                                       //
  //                                                              //
  // Struct containing data used during rendering process         //
  // ************************************************************ //
  struct RenderingResourcesData {
    VkFramebuffer                         Framebuffer;
    VkCommandBuffer                       CommandBuffer;
    VkSemaphore                           ImageAvailableSemaphore;
    VkSemaphore                           FinishedRenderingSemaphore;
    VkFence                               Fence;

    RenderingResourcesData() :
      Framebuffer( VK_NULL_HANDLE ),
      CommandBuffer( VK_NULL_HANDLE ),
      ImageAvailableSemaphore( VK_NULL_HANDLE ),
      FinishedRenderingSemaphore( VK_NULL_HANDLE ),
      Fence( VK_NULL_HANDLE ) {
    }
  };

  // ************************************************************ //
  // VulkanTutorial04Parameters                                   //
  //                                                              //
  // Vulkan specific parameters                                   //
  // ************************************************************ //
  struct VulkanTutorial05Parameters {
    VkRenderPass                          RenderPass;
    VkPipeline                            GraphicsPipeline;
    BufferParameters                      VertexBuffer;
    BufferParameters                      StagingBuffer;
    VkCommandPool                         CommandPool;
    std::vector<RenderingResourcesData>   RenderingResources;

    static const size_t                   ResourcesCount = 3;

    VulkanTutorial05Parameters() :
      RenderPass( VK_NULL_HANDLE ),
      GraphicsPipeline( VK_NULL_HANDLE ),
      VertexBuffer(),
      StagingBuffer(),
      CommandPool( VK_NULL_HANDLE ),
      RenderingResources( ResourcesCount ) {
    }
  };

  // ************************************************************ //
  // Tutorial04                                                   //
  //                                                              //
  // Class for presenting Vulkan usage topics                     //
  // ************************************************************ //
  class Tutorial05 : public VulkanCommon {
  public:
    Tutorial05();
    ~Tutorial05();

    bool    CreateRenderingResources();
    bool    CreateRenderPass();
    bool    CreatePipeline();
    bool    CreateVertexBuffer();
    bool    CreateStagingBuffer();
    bool    CopyVertexData();

    bool    Draw() override;

  private:
    VulkanTutorial05Parameters  Vulkan;

    bool                                                              CreateCommandPool( uint32_t queue_family_index, VkCommandPool *pool );
    bool                                                              AllocateCommandBuffers( VkCommandPool pool, uint32_t count, VkCommandBuffer *command_buffers );
    bool                                                              CreateSemaphore( VkSemaphore *semaphore );
    bool                                                              CreateFence( VkFenceCreateFlags flags, VkFence *fence );
    Tools::AutoDeleter<VkShaderModule, PFN_vkDestroyShaderModule>     CreateShaderModule( const char* filename );
    Tools::AutoDeleter<VkPipelineLayout, PFN_vkDestroyPipelineLayout> CreatePipelineLayout();
    bool                                                              CreateBuffer( VkBufferUsageFlags usage, VkMemoryPropertyFlagBits memoryProperty, BufferParameters &buffer );
    bool                                                              AllocateBufferMemory( VkBuffer buffer, VkMemoryPropertyFlagBits property, VkDeviceMemory *memory );
    const std::vector<float>&                                         GetVertexData() const;
    bool                                                              PrepareFrame( VkCommandBuffer command_buffer, const ImageParameters &image_parameters, VkFramebuffer &framebuffer );
    bool                                                              CreateFramebuffer( VkFramebuffer &framebuffer, VkImageView image_view );
    void                                                              DestroyBuffer( BufferParameters& buffer );

    void                                                              ChildClear() override;
    bool                                                              ChildOnWindowSizeChanged() override;
  };

} // namespace ApiWithoutSecrets

#endif // TUTORIAL_05_HEADER