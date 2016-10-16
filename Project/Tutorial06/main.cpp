// Copyright 2016 Intel Corporation All Rights Reserved
// 
// Intel makes no representations about the suitability of this software for any purpose.
// THIS SOFTWARE IS PROVIDED ""AS IS."" INTEL SPECIFICALLY DISCLAIMS ALL WARRANTIES,
// EXPRESS OR IMPLIED, AND ALL LIABILITY, INCLUDING CONSEQUENTIAL AND OTHER INDIRECT DAMAGES,
// FOR THE USE OF THIS SOFTWARE, INCLUDING LIABILITY FOR INFRINGEMENT OF ANY PROPRIETARY
// RIGHTS, AND INCLUDING THE WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
// Intel does not assume any responsibility for any errors which may appear in this software
// nor any responsibility to update it.

#include "Tutorial06.h"

int main( int argc, char **argv ) {
  ApiWithoutSecrets::OS::Window window;
  ApiWithoutSecrets::Tutorial06 tutorial06;

  // Window creation
  if( !window.Create( "06 - Descriptor Sets" ) ) {
    return -1;
  }

  // Vulkan preparations and initialization
  if( !tutorial06.PrepareVulkan( window.GetParameters() ) ) {
    return -1;
  }

  // Tutorial 06
  if( !tutorial06.CreateRenderingResources() ) {
    return -1;
  }
  if( !tutorial06.CreateStagingBuffer() ) {
    return -1;
  }
  if( !tutorial06.CreateTexture() ) {
    return -1;
  }
  if( !tutorial06.CreateDescriptorSetLayout() ) {
    return -1;
  }
  if( !tutorial06.CreateDescriptorPool() ) {
    return -1;
  }
  if( !tutorial06.AllocateDescriptorSet() ) {
    return -1;
  }
  if( !tutorial06.UpdateDescriptorSet() ) {
    return -1;
  }
  if( !tutorial06.CreateRenderPass() ) {
    return -1;
  }
  if( !tutorial06.CreatePipelineLayout() ) {
    return -1;
  }
  if( !tutorial06.CreatePipeline() ) {
    return -1;
  }
  if( !tutorial06.CreateVertexBuffer() ) {
    return -1;
  }

  // Rendering loop
  if( !window.RenderingLoop( tutorial06 ) ) {
    return -1;
  }

  return 0;
}
