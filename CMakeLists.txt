cmake_minimum_required(VERSION 3.22)
include(FetchContent)

project(PixEngine VERSION 0.0.1)

# --- Is PixEngine the top-level project, or embedded via add_subdirectory() ---
# When a host project does `add_subdirectory(PixEngine)`, only the reusable
# PixEngineLib library target (+ its assets/config) is produced. When PixEngine
# is opened/built on its own, the bundled example project is also built as a
# runnable executable named "PixEngine".
if(CMAKE_SOURCE_DIR STREQUAL CMAKE_CURRENT_SOURCE_DIR)
    set(PIXENGINE_IS_TOP_LEVEL TRUE)
else()
    set(PIXENGINE_IS_TOP_LEVEL FALSE)
endif()

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
if(PIXENGINE_IS_TOP_LEVEL)
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY bin)
endif()

# =============================================================================
# PixEngineLib - the reusable engine, meant to be consumed by host projects
# =============================================================================

file(GLOB_RECURSE PIXENGINE_SOURCES source/*.cpp)
file(GLOB_RECURSE PIXENGINE_HEADERS include/*.h)

add_library(PixEngineLib STATIC ${PIXENGINE_SOURCES} ${PIXENGINE_HEADERS})

target_include_directories(PixEngineLib PUBLIC include)
target_compile_features(PixEngineLib PUBLIC cxx_std_20)
target_link_libraries(PixEngineLib PUBLIC sfml-audio sfml-graphics sfml-window sfml-system)
if(WIN32)
    target_link_libraries(PixEngineLib PUBLIC Shlwapi)
endif()

# The engine's own assets/config always live alongside this CMakeLists.txt.
# Host projects read these via PIXENGINE_ASSETS_DIR/PIXENGINE_CONFIG_DIR
# (set below) to copy them next to their executable - see pixengine_setup_app().
set(PIXENGINE_ASSETS_DIR ${CMAKE_CURRENT_SOURCE_DIR}/assets)
set(PIXENGINE_CONFIG_DIR ${CMAKE_CURRENT_SOURCE_DIR}/config)

# Where PixEngine's own assets/config get copied to, relative to the final
# executable's output directory. Standalone builds copy them straight to
# "assets/"+"config/"; when embedded in a host project they are namespaced
# under "PixEngine/" so they don't collide with the host's own resources.
if(PIXENGINE_IS_TOP_LEVEL)
    set(PIXENGINE_ENGINE_ASSETS_OUTPUT_SUBDIR "assets")
    set(PIXENGINE_ENGINE_CONFIG_OUTPUT_SUBDIR "config")
else()
    set(PIXENGINE_ENGINE_ASSETS_OUTPUT_SUBDIR "PixEngine/assets")
    set(PIXENGINE_ENGINE_CONFIG_OUTPUT_SUBDIR "PixEngine/config")
endif()

target_compile_definitions(PixEngineLib PUBLIC
    PIXENGINE_ENGINE_ASSETS_DIR="${PIXENGINE_ENGINE_ASSETS_OUTPUT_SUBDIR}/"
    PIXENGINE_ENGINE_CONFIG_DIR="${PIXENGINE_ENGINE_CONFIG_OUTPUT_SUBDIR}/"
)

# --- Helper: wire up a host executable so it runs out of the box ---
# Call this once, after add_subdirectory(PixEngine) and after your own
# add_executable(...), to copy SFML/OpenAL DLLs and PixEngine's own
# assets/config next to your binary, and to set the debugger working dir.
# See README.md for the full "embedding PixEngine" walkthrough.
function(pixengine_setup_app TARGET_NAME)
    set_target_properties(${TARGET_NAME} PROPERTIES VS_DEBUGGER_WORKING_DIRECTORY $<TARGET_FILE_DIR:${TARGET_NAME}>)

    macro(pixengine_copy_sfml_dll dll_name)
        add_custom_command(
            TARGET ${TARGET_NAME} POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_if_different
                "${CMAKE_BINARY_DIR}/_deps/sfml-build/lib/$<CONFIG>/${dll_name}$<$<CONFIG:Debug>:-d>-2.dll"
                $<TARGET_FILE_DIR:${TARGET_NAME}>)
    endmacro()

    pixengine_copy_sfml_dll(sfml-graphics)
    pixengine_copy_sfml_dll(sfml-window)
    pixengine_copy_sfml_dll(sfml-audio)
    pixengine_copy_sfml_dll(sfml-system)

    add_custom_command(
        TARGET ${TARGET_NAME} PRE_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
            "${sfml_SOURCE_DIR}/extlibs/bin/$<IF:$<EQUAL:${CMAKE_SIZEOF_VOID_P},8>,x64,x86>/openal32.dll"
            $<TARGET_FILE_DIR:${TARGET_NAME}>
        VERBATIM)

    add_custom_command(
        TARGET ${TARGET_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
            ${PIXENGINE_ASSETS_DIR} $<TARGET_FILE_DIR:${TARGET_NAME}>/${PIXENGINE_ENGINE_ASSETS_OUTPUT_SUBDIR}
        COMMENT "Copy PixEngine engine assets"
        VERBATIM)
    add_custom_command(
        TARGET ${TARGET_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
            ${PIXENGINE_CONFIG_DIR} $<TARGET_FILE_DIR:${TARGET_NAME}>/${PIXENGINE_ENGINE_CONFIG_OUTPUT_SUBDIR}
        COMMENT "Copy PixEngine engine config"
        VERBATIM)

    if(APPLE)
        target_compile_definitions(${TARGET_NAME} PRIVATE TARGET_OS_MAC)
    endif()
endfunction()

# Function to create a source_group tree matching folder structure (IDE only)
function(pixengine_create_source_group PREFIX FILES)
    foreach(FILE_PATH ${FILES})
        file(RELATIVE_PATH REL_PATH ${CMAKE_CURRENT_SOURCE_DIR} ${FILE_PATH})
        get_filename_component(GROUP_PATH ${REL_PATH} PATH)
        string(REPLACE "/" "\\" GROUP_PATH ${GROUP_PATH})
        source_group("${PREFIX}\\${GROUP_PATH}" FILES ${FILE_PATH})
    endforeach()
endfunction()

pixengine_create_source_group("source" "${PIXENGINE_SOURCES}")
pixengine_create_source_group("include" "${PIXENGINE_HEADERS}")

# =============================================================================
# Bundled example - only built when PixEngine itself is the top-level project
# =============================================================================
if(PIXENGINE_IS_TOP_LEVEL)
    set(TARGET_NAME PixEngine)

    file(GLOB_RECURSE EXAMPLE_SOURCES example/source/*.cpp)
    file(GLOB_RECURSE EXAMPLE_HEADERS example/include/*.h)

    pixengine_create_source_group("example-source" "${EXAMPLE_SOURCES}")
    pixengine_create_source_group("example-include" "${EXAMPLE_HEADERS}")

    file(GLOB_RECURSE EXAMPLE_ASSETS example/assets/*)
    file(GLOB_RECURSE EXAMPLE_CONFIGS example/config/*)
    source_group("example-assets" FILES ${EXAMPLE_ASSETS})
    source_group("example-config" FILES ${EXAMPLE_CONFIGS})

    # --- Windows icon ---
    if(WIN32)
        set(WINDOWS_ICON ${CMAKE_CURRENT_SOURCE_DIR}/assets/icon/app.rc)
    endif()

    # --- Add executable ---
    add_executable(${TARGET_NAME} MACOSX_BUNDLE ${EXAMPLE_SOURCES} ${EXAMPLE_HEADERS} ${EXAMPLE_ASSETS} ${EXAMPLE_CONFIGS} ${WINDOWS_ICON})

    target_include_directories(${TARGET_NAME} PRIVATE example/include)
    target_link_libraries(${TARGET_NAME} PRIVATE PixEngineLib)

    # The example's own resources play the role of a "host project"'s assets/config.
    target_compile_definitions(${TARGET_NAME} PRIVATE
        PIXENGINE_GAME_ASSETS_DIR="example/assets/"
        PIXENGINE_GAME_CONFIG_DIR="example/config/"
    )

    # --- VS startup project ---
    set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT ${TARGET_NAME})

    pixengine_setup_app(${TARGET_NAME})

    # --- Copy example assets/config next to the executable ---
    add_custom_command(
        TARGET ${TARGET_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
            ${CMAKE_CURRENT_SOURCE_DIR}/example/assets $<TARGET_FILE_DIR:${TARGET_NAME}>/example/assets
        COMMENT "Copy example assets"
        VERBATIM)
    add_custom_command(
        TARGET ${TARGET_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
            ${CMAKE_CURRENT_SOURCE_DIR}/example/config $<TARGET_FILE_DIR:${TARGET_NAME}>/example/config
        COMMENT "Copy example config"
        VERBATIM)

    # --- Mac-specific resource handling ---
    if(APPLE)
        file(GLOB RESOURCE_FILES "assets")
        set_source_files_properties("${RESOURCE_FILES}" PROPERTIES MACOSX_PACKAGE_LOCATION "Resources")
        target_sources(${TARGET_NAME} PRIVATE ${RESOURCE_FILES})
        set_target_properties(${TARGET_NAME} PROPERTIES RESOURCE "${RESOURCE_FILES}")
    endif()
endif()
