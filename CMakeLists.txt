cmake_minimum_required(VERSION 3.0)

project(gtasa)

ADD_DEFINITIONS(-DWIN32=1)

find_program(CCACHE_FOUND ccache)
if(CCACHE_FOUND)
	set_property(GLOBAL PROPERTY RULE_LAUNCH_COMPILE ccache)
	set_property(GLOBAL PROPERTY RULE_LAUNCH_LINK ccache)
endif(CCACHE_FOUND)

aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR} ${PROJECT_NAME}_LIST)
aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR}/CGame ${PROJECT_NAME}_LIST)
	aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR}/CGame/Transport ${PROJECT_NAME}_LIST)
	aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR}/CGame/Pools ${PROJECT_NAME}_LIST)

if (CMAKE_CXX_COMPILER_ID STREQUAL "Clang" OR CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
	add_definitions("-ffunction-sections -fdata-sections -w")
endif()

add_library(${PROJECT_NAME} STATIC ${${PROJECT_NAME}_LIST})

set_target_properties(${PROJECT_NAME} PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED YES
    CXX_EXTENSIONS NO
)

target_link_libraries(${PROJECT_NAME})
