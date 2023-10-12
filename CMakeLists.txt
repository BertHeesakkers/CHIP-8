cmake_minimum_required(VERSION 3.21)
project(CHIP-8 VERSION 0.1.0)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake/")
#set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
#set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

include(CopyAssets)

### Dependencies
#set(RAYLIB_VERSION 4.5.0)
#find_package(raylib ${RAYLIB_VERSION} QUIET) # QUIET or REQUIRED
#if (NOT raylib_FOUND) # If there's none, fetch and build raylib
#    include(FetchContent)
#    FetchContent_Declare(
##        raylib
##        DOWNLOAD_EXTRACT_TIMESTAMP OFF
##        URL https://github.com/raysan5/raylib/archive/refs/tags/${RAYLIB_VERSION}.tar.gz
#        raylib
#        GIT_REPOSITORY https://github.com/raysan5/raylib
#        GIT_TAG		   4.5.0
#    )
#    FetchContent_GetProperties(raylib)
#
#    if (NOT raylib_POPULATED) # Have we downloaded raylib yet?
#        set(FETCHCONTENT_QUIET NO)
#        FetchContent_Populate(raylib)
#        set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE) # don't build the supplied examples
#        add_subdirectory(${raylib_SOURCE_DIR} ${raylib_BINARY_DIR})
#    endif()
#endif()

# header files
file(GLOB_RECURSE ${PROJECT_NAME}_CORE_HEADERS "${CMAKE_CURRENT_SOURCE_DIR}/code/*.h")
source_group("Header Files\\" FILES ${${PROJECT_NAME}_CORE_HEADERS})

# aggregate headers
set(${PROJECT_NAME}_AGGREGATE_HEADERS
        ${${PROJECT_NAME}_CORE_HEADERS})

# source files
file(GLOB_RECURSE ${PROJECT_NAME}_CORE_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/code/*.c")
source_group("Source Files\\" FILES ${${PROJECT_NAME}_CORE_SOURCES})

# aggregate sources
set(${PROJECT_NAME}_AGGREGATE_SOURCES
        ${${PROJECT_NAME}_CORE_SOURCES})

add_executable(${PROJECT_NAME} ${${PROJECT_NAME}_AGGREGATE_HEADERS} ${${PROJECT_NAME}_AGGREGATE_SOURCES})
set_property(TARGET ${PROJECT_NAME} PROPERTY C_STANDARD 11)
#target_link_libraries(${PROJECT_NAME} raylib)

# Checks if OSX and links appropriate frameworks (Only required on MacOS)
if (APPLE)
#    target_link_libraries(${PROJECT_NAME} "-framework IOKit")
#    target_link_libraries(${PROJECT_NAME} "-framework Cocoa")
#    target_link_libraries(${PROJECT_NAME} "-framework OpenGL")

    include(CPack)

    set_target_properties(${target} PROPERTIES
        BUNDLE True
        MACOSX_BUNDLE_GUI_IDENTIFIER com.acme.raylib_cmake
        MACOSX_BUNDLE_BUNDLE_NAME "CHIP-8 Emulator"
        MACOSX_BUNDLE_BUNDLE_VERSION "0.1.0"
        MACOSX_BUNDLE_SHORT_VERSION_STRING "0.1.0"
        MACOSX_BUNDLE_ICON_NAME "AppIcon"
        MACOSX_BUNDLE_COPYRIGHT "© 2023 Bert Heesakkers"
        MACOSX_BUNDLE_INFO_PLIST "${CMAKE_SOURCE_DIR}/cmake/MacOSXBundleInfo.plist.in"
    )
endif()

# copy assets
set(ROM_DIR ${CMAKE_CURRENT_SOURCE_DIR}/roms)
set(SCRIPT_DIR ${CMAKE_CURRENT_SOURCE_DIR}/scripts)

if(CMAKE_HOST_WIN32)
    add_custom_command(TARGET ${PROJECT_NAME}
            POST_BUILD COMMAND python ${SCRIPT_DIR}/CopyAssets.py
            ${ROM_DIR}
            ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/Debug/roms/)

    add_custom_command(TARGET ${PROJECT_NAME}
            POST_BUILD COMMAND python ${SCRIPT_DIR}/CopyAssets.py
            ${ROM_DIR}
            ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/Release/roms/)
else()
    add_custom_command(TARGET ${PROJECT_NAME}
            POST_BUILD COMMAND python ${SCRIPT_DIR}/CopyAssets.py
            ${ROM_DIR}
            ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/roms/)
endif()
