// Copyright 2016 Intel Corporation All Rights Reserved
// 
// Intel makes no representations about the suitability of this software for any purpose.
// THIS SOFTWARE IS PROVIDED ""AS IS."" INTEL SPECIFICALLY DISCLAIMS ALL WARRANTIES,
// EXPRESS OR IMPLIED, AND ALL LIABILITY, INCLUDING CONSEQUENTIAL AND OTHER INDIRECT DAMAGES,
// FOR THE USE OF THIS SOFTWARE, INCLUDING LIABILITY FOR INFRINGEMENT OF ANY PROPRIETARY
// RIGHTS, AND INCLUDING THE WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
// Intel does not assume any responsibility for any errors which may appear in this software
// nor any responsibility to update it.

#if !defined(TOOLS_HEADER)
#define TOOLS_HEADER

#include <string>
#include <vector>
#include <array>
#include "vulkan.h"

namespace ApiWithoutSecrets {

  namespace Tools {

    // ************************************************************ //
    // AutoDeleter                                                  //
    //                                                              //
    // Auto-deleter helper template class responsible for calling   //
    // provided function which deletes given object of type T       //
    // ************************************************************ //
    template<class T, class F>
    class AutoDeleter {
    public:
      AutoDeleter() :
        Object( VK_NULL_HANDLE ),
        Deleter( nullptr ),
        Device( VK_NULL_HANDLE ) {
      }

      AutoDeleter( T object, F deleter, VkDevice device ) :
        Object( object ),
        Deleter( deleter ),
        Device( device ) {
      }

      AutoDeleter( AutoDeleter&& other ) {
        *this = std::move( other );
      }

      ~AutoDeleter() {
        if( (Object != VK_NULL_HANDLE) && (Deleter != nullptr) && (Device != VK_NULL_HANDLE) ) {
          Deleter( Device, Object, nullptr );
        }
      }

      AutoDeleter& operator=(AutoDeleter&& other) {
        if( this != &other ) {
          Object = other.Object;
          Deleter = other.Deleter;
          Device = other.Device;
          other.Object = VK_NULL_HANDLE;
        }
        return *this;
      }

      T Get() {
        return Object;
      }

      bool operator !() const {
        return Object == VK_NULL_HANDLE;
      }

    private:
      AutoDeleter( const AutoDeleter& );
      AutoDeleter& operator=( const AutoDeleter& );
      T         Object;
      F         Deleter;
      VkDevice  Device;
    };

    // ************************************************************ //
    // GetBinaryFileContents                                        //
    //                                                              //
    // Function reading binary contents of a file                   //
    // ************************************************************ //
    std::vector<char> GetBinaryFileContents( std::string const &filename );

    // ************************************************************ //
    // GetImageData                                                 //
    //                                                              //
    // Function loading image (texture) data from a specified file  //
    // ************************************************************ //
    std::vector<char> GetImageData( std::string const &filename, int requested_components, int *width, int *height, int *components, int *data_size );

    // ************************************************************ //
    // GetPerspectiveProjectionMatrix                               //
    //                                                              //
    // Function calculating perspective projection matrix           //
    // ************************************************************ //
    std::array<float, 16> GetPerspectiveProjectionMatrix( float const aspect_ratio, float const field_of_view, float const near_clip, float const far_clip );

    // ************************************************************ //
    // GetOrthographicsProjectionMatrix                             //
    //                                                              //
    // Function calculating orthographic projection matrix          //
    // ************************************************************ //
	std::array<float, 16> GetOrthographicProjectionMatrix( float const left_plane, float const right_plane, float const top_plane, float const bottom_plane, float const near_plane, float const far_plane );

  } // namespace Tools

} // namespace ApiWithoutSecrets


#endif // TOOLS_HEADER