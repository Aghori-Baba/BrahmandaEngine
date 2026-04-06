cmake_minimum_required(VERSION "3.31.0")

set(RLIMGUI_DIR ${CMAKE_CURRENT_SOURCE_DIR})

add_library(rlimgui STATIC
	${RLIMGUI_DIR}/rlImGui.cpp
)

target_include_directories(rlimgui PUBLIC 
	${RLIMGUI_DIR}
	${CMAKE_SOURCE_DIR}/thirdParty/imgui-docking/imgui
)

target_link_libraries(rlimgui PUBLIC raylib_static imgui)