# Copyright (c) 2026-Present Jogeshwar Digital Pvt. Ltd. | Brahmanda Engine. All rights reserved.

cmake_minimum_required(VERSION "3.31.0")

#add_subdirectory(thirdParty/{LIBRARY NAME})

project("BrahmandaEngine")
set(CMAKE_CXX_STANDARD 17)

set(PRODUCTION_BUILD OFF CACHE BOOL "Make this a production build" FORCE)
set(ENABLE_LOGGER ON CACHE BOOL "Enable logging" FORCE)

if (MSVC)
	set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Release>:Release>")
	set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")
endif()

if(PRODUCTION_BUILD)
	set(CMAKE_INTERPROCEDURAL_OPTIMIZATION TRUE)
else()
	set(CMAKE_INTERPROCEDURAL_OPTIMIZATION FALSE)
endif()

file(GLOB_RECURSE PROJ_SOURCES CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")
#add_executable("${CMAKE_PROJECT_NAME}" "${PROJ_SOURCES}")

add_executable("${CMAKE_PROJECT_NAME}")

if(PRODUCTION_BUILD)
	target_compile_definitions("${CMAKE_PROJECT_NAME}" PUBLIC RESOURCE_DIR="./resources/")
	target_compile_definitions("${CMAKE_PROJECT_NAME}" PUBLIC PRODUCTION_BUILD=1)
else()
	target_compile_definitions("${CMAKE_PROJECT_NAME}" PUBLIC RESOURCE_DIR="${CMAKE_CURRENT_SOURCE_DIR}/resources/")
	target_compile_definitions("${CMAKE_PROJECT_NAME}" PUBLIC PRODUCTION_BUILD=0)
endif()

if(ENABLE_LOGGER)
	target_compile_definitions("${CMAKE_PROJECT_NAME}" PUBLIC ENABLE_LOGGER=1)
else()
	target_compile_definitions("${CMAKE_PROJECT_NAME}" PUBLIC ENABLE_LOGGER=0)
endif()

if(MSVC)
	add_compile_options(/arch:AVX2)
	target_compile_definitions("${CMAKE_PROJECT_NAME}" PUBLIC _CRT_SECURE_NO_WARNINGS)
endif()

set(BUILD_SHARED_LIBS OFF CACHE BOOL "Build all libraries as Static by default" FORCE)

##########-----------------------------Add and Link Libraries here-----------------------------##########
##########-------------------------------------------------------------------------------------##########

#Adding Raylib dir
add_subdirectory(thirdParty/raylib-5.5)

#Adding Imgui dir
add_subdirectory(thirdParty/imgui-docking)

#Adding rlImgui dir
add_subdirectory(thirdParty/rlimgui)

#Adding spdlog dir
add_subdirectory(thirdParty/spdlog)
#target_include_directories("${CMAKE_PROJECT_NAME}" PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/thirdParty/spdlog/include/spdlog")

#Linking all added Libraries statically
target_link_libraries("${CMAKE_PROJECT_NAME}" PRIVATE raylib_static imgui rlimgui spdlog::spdlog)

##########-------------------------------------------------------------------------------------##########
##########-------------------------------------------------------------------------------------##########

target_sources("${CMAKE_PROJECT_NAME}" PRIVATE ${PROJ_SOURCES})
target_include_directories("${CMAKE_PROJECT_NAME}" PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/src/")
target_include_directories("${CMAKE_PROJECT_NAME}" PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/src/Engine")