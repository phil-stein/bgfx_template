cmake_minimum_required(VERSION 3.20.1)

set(NAME "bgfx_test")

project(${NAME}
      VERSION 0.1
      DESCRIPTION "bgfx test")
      # LANGUAGES CXX)

set(ROOT_DIR_STEP "../..")
set(ROOT_DIR      "${CMAKE_SOURCE_DIR}/${ROOT_DIR_STEP}")
set(SRC_DIR       ${ROOT_DIR}/src)
set(EXT_DIR       ${ROOT_DIR}/_external)
set(LIB_DIR       ${ROOT_DIR}/_libs)
set(BUILD_DIR     ${ROOT_DIR}/_build)
set(BIN_DIR       ${ROOT_DIR}/_bin)

# puts .exe in _bin, but also dll's
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${BIN_DIR})
# # set the output dir for libraries 
# set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${ROOT_DIR}/_libs/win64)   # static lib's
# set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${ROOT_DIR}/_libs/win64)   # dll's, should prob. be _bin
# # set_target_properties(${LIB_NAME} PROPERTIES LIBRARY_OUTPUT_DIRECTORY ${ROOT_DIR}/_libs/win64)
# # set_target_properties(${LIB_NAME} PROPERTIES ARCHIVE_OUTPUT_DIRECTORY ${ROOT_DIR}/_libs/win64)

add_executable(${NAME}
              ${ROOT_DIR}/src/core/main.c
              ${ROOT_DIR}/src/core/logo.h
              )
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -g -Wall -std=gnu99")

if(${CMAKE_GENERATOR} STREQUAL "MinGW Makefiles")
  # set(CUSTOM_C_VERSION -std=c17)
  set(CUSTOM_C_VERSION )  # setting c version in gcc causes errors
else()
  set(CUSTOM_C_VERSION /std:c17)
endif()

set(CUSTOM_LINK_OPTIONS
  -g  # debug info
  -pg # generate instumentation info for gprof
  # -no-pie
  )
set(CUSTOM_COMPILE_OPTIONS
  ${CUSTOM_C_VERSION}
  -g
  -Wall
  -D_CRT_SECURE_NO_WARNINGS
  -DGLOBAL_DEBUG 
  -pg # generate instumentation info for gprof
  # -no-pie
  )

target_include_directories(${NAME} PRIVATE ${SRC_DIR})
target_include_directories(${NAME} PRIVATE ${EXT_DIR})
target_include_directories(${NAME} PRIVATE ${EXT_DIR}/bgfx.cmake/bgfx/include)
target_include_directories(${NAME} PRIVATE ${EXT_DIR}/bgfx.cmake/bimg/include)
target_include_directories(${NAME} PRIVATE ${EXT_DIR}/bgfx.cmake/bx/include)
# target_compile_features(   ${NAME} PRIVATE cxx_std_11)
target_compile_options(    ${NAME} PRIVATE ${CUSTOM_COMPILE_OPTIONS}) 
target_link_options(       ${NAME} PRIVATE ${CUSTOM_LINK_OPTIONS})

if(${CMAKE_GENERATOR} STREQUAL "MinGW Makefiles")
  target_link_libraries(${NAME} ${LIB_DIR}/win64/libglfw3.a)
  # target_link_libraries(${EDITOR_NAME} ${EDITOR_ROOT_DIR}/_libs/win64/freetype.a)
  # message("!!! -> used .a")
else() # if(${CMAKE_GENERATOR} STREQUAL "Visual Studio 2016 19")
  target_link_libraries(${NAME} ${LIB_DIR}/win64/glfw3.lib)
  # target_link_libraries(${EDITOR_NAME} ${EDITOR_ROOT_DIR}/_libs/win64/freetype.lib)
  # message("!!! -> used .lib")
endif()

# if(${CMAKE_GENERATOR} STREQUAL "MinGW Makefiles")
#   # target_link_libraries(${NAME} ${ROOT_DIR}/libs/win64/bgfx_gcc/libbgfx.a)
#   # target_link_libraries(${NAME} ${ROOT_DIR}/libs/win64/bgfx_gcc/libexample-common.a)
#   # target_link_libraries(${NAME} ${ROOT_DIR}/libs/win64/bgfx_gcc/libfcpp.a)
#   # target_link_libraries(${NAME} ${ROOT_DIR}/libs/win64/bgfx_gcc/libgeometryv.dll.a)
#   # target_link_libraries(${NAME} ${ROOT_DIR}/libs/win64/bgfx_gcc/libglslang.a)
#   # target_link_libraries(${NAME} ${ROOT_DIR}/libs/win64/bgfx_gcc/libglsl-optimizer.a)
#   # target_link_libraries(${NAME} ${ROOT_DIR}/libs/win64/bgfx_gcc/libspirv-cross.a)
#   # target_link_libraries(${NAME} ${ROOT_DIR}/libs/win64/bgfx_gcc/libspirv-opt.a)
#   # target_link_libraries(${NAME} ${ROOT_DIR}/libs/win64/bgfx_gcc/libtexturev.dll.a)
# 
#   target_link_libraries(${NAME} ${ROOT_DIR}/external/bgfx.cmake/mingw64/cmake/bgfx/libbgfx.a)
#   target_link_libraries(${NAME} ${ROOT_DIR}/external/bgfx.cmake/mingw64/cmake/bgfx/libexample-common.a)
#   target_link_libraries(${NAME} ${ROOT_DIR}/external/bgfx.cmake/mingw64/cmake/bgfx/libfcpp.a)
#   # target_link_libraries(${NAME} ${ROOT_DIR}/external/bgfx.cmake/mingw64/cmake/bgfx/libgeometryv.dll.a)
#   target_link_libraries(${NAME} ${ROOT_DIR}/external/bgfx.cmake/mingw64/cmake/bgfx/libglslang.a)
#   target_link_libraries(${NAME} ${ROOT_DIR}/external/bgfx.cmake/mingw64/cmake/bgfx/libglsl-optimizer.a)
#   target_link_libraries(${NAME} ${ROOT_DIR}/external/bgfx.cmake/mingw64/cmake/bgfx/libspirv-cross.a)
#   target_link_libraries(${NAME} ${ROOT_DIR}/external/bgfx.cmake/mingw64/cmake/bgfx/libspirv-opt.a)
#   # target_link_libraries(${NAME} ${ROOT_DIR}/external/bgfx.cmake/mingw64/cmake/bgfx/libtexturev.dll.a)
#   
#   target_link_libraries(${NAME} ${ROOT_DIR}/external/bgfx.cmake/mingw64/cmake/bimg/libbimg.a)
#   target_link_libraries(${NAME} ${ROOT_DIR}/external/bgfx.cmake/mingw64/cmake/bimg/libbimg_decode.a)
#   target_link_libraries(${NAME} ${ROOT_DIR}/external/bgfx.cmake/mingw64/cmake/bimg/libbimg_encode.a)
#   # target_link_libraries(${NAME} ${ROOT_DIR}/external/bgfx.cmake/mingw64/cmake/bimg/libtexturec.dll.a)
# 
#   target_link_libraries(${NAME} ${ROOT_DIR}/external/bgfx.cmake/mingw64/cmake/bx/libbx.a)
# else() # if(${CMAKE_GENERATOR} STREQUAL "Visual Studio 2016 19")
# endif()

if(${CMAKE_GENERATOR} STREQUAL "MinGW Makefiles")
  add_subdirectory(${EXT_DIR}/bgfx.cmake ${BUILD_DIR}/bgfx/mingw64)
else() # if(${CMAKE_GENERATOR} STREQUAL "Visual Studio 2016 19")
  add_subdirectory(${EXT_DIR}/bgfx.cmake ${BUILD_DIR}/bgfx/vs)
endif()
target_link_libraries(${NAME} bgfx)
target_link_libraries(${NAME} bimg)
target_link_libraries(${NAME} bx)
# target_link_libraries(${NAME} example-common)

