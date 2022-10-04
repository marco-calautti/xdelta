cmake_minimum_required(VERSION 3.0.0)
project(xdelta3 VERSION 3.0.11)

include(CheckTypeSize)
check_type_size(size_t XD3_SIZEOF_SIZE_T)

set(XD3_SOURCES xdelta3/xdelta3.c)

set(XD3_TARGET_LIBS "")

option( XD3_BUILD_AS_EXE 
        "Set to ON to build xdelta3 as an executable rather than a library."
        OFF)

option( XD3_ENABLE_SECONDARY_COMPRESSION 
        "Compiles builtin in support for secondary compression (DJW and FGK). \
        To also include lzma as secondary compression, you should enable it with the corresponding option"
        OFF)

option( XD3_ENABLE_LZMA
        "Includes lzma as secondary compression. \
        For this to work, libzma must be available to find_package when building
        This option has no effect if secondary compression is not enabled."
        OFF)

option( XD3_ENABLE_ENCODER
        "Enable also the encoding code, and not only the decoder."
        OFF)

option( XD3_ENABLE_VCDIFF_TOOLS
        "Enable additional vcdiff code (e.g., get xdelta patch's header information"
        OFF)

add_compile_definitions(SIZEOF_SIZE_T=${XD3_SIZEOF_SIZE_T})
add_compile_definitions(XD3_USE_LARGEFILE64=1)
add_compile_definitions(XD3_MAIN=1) #enables main function
add_compile_definitions(EXTERNAL_COMPRESSION=0)
if(WIN32)
    add_compile_definitions(XD3_WIN32=1) #this forces using the win32 io library
    add_compile_definitions(WIN32=1)
else()
    add_compile_definitions(XD3_WIN32=0)
    add_compile_definitions(WIN32=0)
    # here we are defaulting to using the stdio io library. If posix is need,
    # we must change  the following compile definition to use XD3_POSIX
    add_compile_definitions(XD3_STDIO=1)
endif()

if(XD3_BUILD_AS_EXE)
    add_compile_definitions(NOT_MAIN=0)
else()
    add_compile_definitions(NOT_MAIN=1) # changes the main function name to xd3_main_cmdline
    set(XD3_SOURCES xdelta3_wrapper.cpp ${XD3_SOURCES})
endif()

if(XD3_ENABLE_ENCODER)
    add_compile_definitions(XD3_ENCODER=1)
else()
    add_compile_definitions(XD3_ENCODER=0)
endif()

if(XD3_ENABLE_VCDIFF_TOOLS)
    add_compile_definitions(VCDIFF_TOOLS=1)
else()
    add_compile_definitions(VCDIFF_TOOLS=0)
endif()

if(XD3_ENABLE_SECONDARY_COMPRESSION)
    add_compile_definitions(SECONDARY_DJW=1) #(passing djwn chooses compression n with djw. Other second compressions do not seem to support level)
    add_compile_definitions(SECONDARY_FGK=1)
    if(XD3_ENABLE_LZMA)
        #find_package(LibLZMA 5.2.1 REQUIRED CONFIG)
        set(XD3_TARGET_LIBS liblzma ${XD3_TARGET_LIBS})
        add_compile_definitions(SECONDARY_LZMA=1)
    endif()
else()
    add_compile_definitions(SECONDARY_DJW=0)
    add_compile_definitions(SECONDARY_FGK=0)
    add_compile_definitions(SECONDARY_LZMA=0)
endif()

if(XD3_BUILD_AS_EXE)
    add_executable(${PROJECT_NAME} "${XD3_SOURCES}")
else()
    add_library(${PROJECT_NAME} "${XD3_SOURCES}")
    target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
    target_link_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
endif()


target_link_libraries(${PROJECT_NAME} ${XD3_TARGET_LIBS})
