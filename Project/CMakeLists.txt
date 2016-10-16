# Copyright 2016 Intel Corporation All Rights Reserved
# 
# Intel makes no representations about the suitability of this software for any purpose.
# THIS SOFTWARE IS PROVIDED ""AS IS."" INTEL SPECIFICALLY DISCLAIMS ALL WARRANTIES,
# EXPRESS OR IMPLIED, AND ALL LIABILITY, INCLUDING CONSEQUENTIAL AND OTHER INDIRECT DAMAGES,
# FOR THE USE OF THIS SOFTWARE, INCLUDING LIABILITY FOR INFRINGEMENT OF ANY PROPRIETARY
# RIGHTS, AND INCLUDING THE WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
# Intel does not assume any responsibility for any errors which may appear in this software
# nor any responsibility to update it.

cmake_minimum_required (VERSION 3.0)
project( "IntroductionToVulkan" )

if( CMAKE_BUILD_TYPE STREQUAL "" )
	set( CMAKE_BUILD_TYPE "debug" )
endif()

if( NOT USE_PLATFORM MATCHES "VK_USE_PLATFORM_.*" )
	if( WIN32 )
		set( USE_PLATFORM "VK_USE_PLATFORM_WIN32_KHR" )
	elseif( UNIX )
		set( USE_PLATFORM "VK_USE_PLATFORM_XCB_KHR" )
	endif()
endif()

if( USE_PLATFORM STREQUAL "VK_USE_PLATFORM_WIN32_KHR" )
	set( CMAKE_C_FLAGS_RELWITHDEBINFO    "${CMAKE_C_FLAGS_RELWITHDEBINFO} /MT" )
	set( CMAKE_C_FLAGS_RELEASE           "${CMAKE_C_FLAGS_RELEASE} /MT" )
	set( CMAKE_C_FLAGS_DEBUG             "${CMAKE_C_FLAGS_DEBUG} /MTd" )
	set( CMAKE_CXX_FLAGS_RELWITHDEBINFO  "${CMAKE_CXX_FLAGS_RELWITHDEBINFO} /MT" )
	set( CMAKE_CXX_FLAGS_RELEASE         "${CMAKE_CXX_FLAGS_RELEASE} /MT" )
	set( CMAKE_CXX_FLAGS_DEBUG           "${CMAKE_CXX_FLAGS_DEBUG} /MTd" )
	set( PLATFORM_LIBRARY                "" )
elseif( USE_PLATFORM STREQUAL "VK_USE_PLATFORM_XCB_KHR" )
	add_definitions( -std=c++11 )
	set( PLATFORM_LIBRARY dl xcb )
elseif( USE_PLATFORM STREQUAL "VK_USE_PLATFORM_XLIB_KHR" )
	add_definitions( -std=c++11 )
	set( PLATFORM_LIBRARY dl X11 )
endif()

if( CMAKE_BUILD_TYPE STREQUAL "debug" )
	add_definitions(-D_DEBUG)
endif()

macro( add_executable _number _name )
	set( TARGET_NAME "${_number}-${_name}" )
	_add_executable( ${TARGET_NAME} ${ARGN} )
	target_compile_definitions( ${TARGET_NAME} PRIVATE USE_SWAPCHAIN_EXTENSIONS )
	target_link_libraries( ${TARGET_NAME} ${PLATFORM_LIBRARY} )
	
	if( EXISTS "${CMAKE_SOURCE_DIR}/Tutorial${_number}/Data${_number}/" )
		file( COPY "${CMAKE_SOURCE_DIR}/Tutorial${_number}/Data${_number}/" DESTINATION "${CMAKE_SOURCE_DIR}/build/Data${_number}" )
	endif()
endmacro()

add_definitions( -DVK_NO_PROTOTYPES )
add_definitions( -D${USE_PLATFORM} )
include_directories( Include )
include_directories( Common )

set( BASIC_SHARED_HEADER_FILES
		"Common/OperatingSystem.h"
		"Common/ListOfFunctions.inl"
		"Common/VulkanFunctions.h" )

set( BASIC_SHARED_SOURCE_FILES
		"Common/OperatingSystem.cpp"
		"Common/VulkanFunctions.cpp" )

set( EXTERNAL_HEADER_FILES
		"Include/vk_platform.h"
		"Include/vulkan.h"
		"Include/stb_image.h" )

set( ALL_BASIC_SHARED_FILES
		${BASIC_SHARED_HEADER_FILES}
		${BASIC_SHARED_SOURCE_FILES}
		${EXTERNAL_HEADER_FILES} )

set( ADVANCED_SHARED_HEADER_FILES
		"Common/Tools.h"
		"Common/VulkanCommon.h" )

set( ADVANCED_SHARED_SOURCE_FILES
		"Common/Tools.cpp"
		"Common/VulkanCommon.cpp" )

set( ALL_BASIC_AND_ADVANCED_SHARED_FILES
		${ALL_BASIC_SHARED_FILES}
		${ADVANCED_SHARED_HEADER_FILES}
		${ADVANCED_SHARED_SOURCE_FILES} )

set( TUTORIAL_HEADER_FILES REGULAR_EXPRESSION
		"Tutorial.*h" )

set( TUTORIAL_SOURCE_FILES REGULAR_EXPRESSION
		"Tutorial.*cpp" )

source_group( "Header Files\\Common" FILES ${BASIC_SHARED_HEADER_FILES} )
source_group( "Source Files\\Common" FILES ${BASIC_SHARED_SOURCE_FILES} )
source_group( "Header Files\\Include" FILES ${EXTERNAL_HEADER_FILES} )
source_group( "Header Files\\Common" FILES ${ADVANCED_SHARED_HEADER_FILES} )
source_group( "Source Files\\Common" FILES ${ADVANCED_SHARED_SOURCE_FILES} )
source_group( "Header Files" FILES ${TUTORIAL_HEADER_FILES} )
source_group( "Source Files" FILES ${TUTORIAL_SOURCE_FILES} )

_add_executable( "01-The_Beginning"
	${ALL_BASIC_SHARED_FILES}
	Tutorial01/Tutorial01.h
	Tutorial01/main.cpp
	Tutorial01/Tutorial01.cpp )
	target_link_libraries( "01-The_Beginning" ${PLATFORM_LIBRARY} )

add_executable( "02" "Swapchain"
	${ALL_BASIC_SHARED_FILES}
	Tutorial02/Tutorial02.h
	Tutorial02/main.cpp
	Tutorial02/Tutorial02.cpp )

add_executable( "03" "First_Triangle"
	${ALL_BASIC_AND_ADVANCED_SHARED_FILES}
	Tutorial03/Tutorial03.h
	Tutorial03/main.cpp
	Tutorial03/Tutorial03.cpp )

add_executable( "04" "Vertex_Attributes"
	${ALL_BASIC_AND_ADVANCED_SHARED_FILES}
	Tutorial04/Tutorial04.h
	Tutorial04/main.cpp
	Tutorial04/Tutorial04.cpp )
	
add_executable( "05" "Staging_Resources"
	${ALL_BASIC_AND_ADVANCED_SHARED_FILES}
	Tutorial05/Tutorial05.h
	Tutorial05/main.cpp
	Tutorial05/Tutorial05.cpp )

add_executable( "06" "Descriptor_Sets"
	${ALL_BASIC_AND_ADVANCED_SHARED_FILES}
	Tutorial06/Tutorial06.h
	Tutorial06/main.cpp
	Tutorial06/Tutorial06.cpp )

add_executable( "07" "Uniform_Buffers"
	${ALL_BASIC_AND_ADVANCED_SHARED_FILES}
	Tutorial07/Tutorial07.h
	Tutorial07/main.cpp
	Tutorial07/Tutorial07.cpp )