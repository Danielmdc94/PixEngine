cmake_minimum_required(VERSION 3.22)
include(FetchContent)

project(PixEngine VERSION 0.0.1)

# --- Fetch SFML ---
FetchContent_Declare(
 SFML
 GIT_REPOSITORY https://github.com/SFML/SFML.git
 GIT_TAG 2.6.0
)
FetchContent_MakeAvailable(SFML)

# --- C++ standard ---
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED true)

# --- Output directory ---
set(CMAKE_SUPPRESS_REGENERATION true)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY bin)

set(TARGET_NAME PixEngine)

# --- Collect source/header files ---
file(GLOB_RECURSE SOURCES 
    game/source/*.cpp 
    engine/source/*.cpp
)
file(GLOB_RECURSE HEADERS 
    game/include/*.h 
    engine/include/*.h
)

source_group("source" FILES ${SOURCES})
source_group("include" FILES ${HEADERS})

# --- Windows icon ---
if(WIN32)
    set(WINDOWS_ICON ${CMAKE_CURRENT_SOURCE_DIR}/engine/resources/App.rc)
endif()

# --- Add executable ---
add_executable(${TARGET_NAME} MACOSX_BUNDLE ${SOURCES} ${HEADERS} ${WINDOWS_ICON})
target_include_directories(${TARGET_NAME} PRIVATE game/include engine/include)
target_link_libraries(${TARGET_NAME} PRIVATE sfml-audio sfml-graphics sfml-window sfml-system Shlwapi)

set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT ${TARGET_NAME})

# --- Assets root for debugger ---
set_target_properties(${TARGET_NAME} PROPERTIES VS_DEBUGGER_WORKING_DIRECTORY $<TARGET_FILE_DIR:${TARGET_NAME}>)

# --- Helper macro for copying SFML DLLs depending on configuration ---
macro(copy_sfml_dll dll_name)
    add_custom_command(
        TARGET ${TARGET_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
            "${PROJECT_SOURCE_DIR}/build/_deps/sfml-build/lib/$<CONFIG>/${dll_name}$<$<CONFIG:Debug>:-d>-2.dll"
            $<TARGET_FILE_DIR:${TARGET_NAME}>)
endmacro()

# --- Copy SFML DLLs ---
copy_sfml_dll(sfml-graphics)
copy_sfml_dll(sfml-window)
copy_sfml_dll(sfml-audio)
copy_sfml_dll(sfml-system)

# --- Copy OpenAL DLL ---
add_custom_command(
    TARGET ${TARGET_NAME} PRE_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy
        "${SFML_SOURCE_DIR}/extlibs/bin/$<IF:$<EQUAL:${CMAKE_SIZEOF_VOID_P},8>,x64,x86>/openal32.dll"
        $<TARGET_FILE_DIR:${TARGET_NAME}>
    VERBATIM)

# --- Copy assets directories ---
function(copy_assets source_dir target_subdir)
    add_custom_command(
        TARGET ${TARGET_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
            ${source_dir}
            $<TARGET_FILE_DIR:${TARGET_NAME}>/${target_subdir}
        COMMENT "Copy ${target_subdir} assets"
        VERBATIM)
endfunction()

copy_assets(${CMAKE_CURRENT_SOURCE_DIR}/engine/assets engine/assets)
copy_assets(${CMAKE_CURRENT_SOURCE_DIR}/engine/config engine/config)
copy_assets(${CMAKE_CURRENT_SOURCE_DIR}/engine/resources engine/resources)

copy_assets(${CMAKE_CURRENT_SOURCE_DIR}/game/assets game/assets)

# --- Mac-specific resource handling ---
if(APPLE)
    file(GLOB RESOURCE_FILES "assets")
    set_source_files_properties("${RESOURCE_FILES}" PROPERTIES MACOSX_PACKAGE_LOCATION "Resources")
    target_sources(${TARGET_NAME} PRIVATE ${RESOURCE_FILES})
    set_target_properties(${TARGET_NAME} PROPERTIES RESOURCE "${RESOURCE_FILES}")
    add_compile_definitions(TARGET_OS_MAC)
endif()
