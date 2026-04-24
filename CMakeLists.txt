cmake_minimum_required(VERSION 3.16)

project(chamCity3D LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS ON)

if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
  set(CMAKE_BUILD_TYPE Debug CACHE STRING "Choose the type of build (Debug or Release)" FORCE)
endif()

list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake/modules")

set(NAME "Cham-City-3D")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/bin")

configure_file(configuration/root_directory.h.in configuration/root_directory.h)

find_package(Threads REQUIRED)
find_package(GLM REQUIRED)

# Prefer CMake package configs when present; fallback to bundled find-modules.
find_package(glfw3 CONFIG QUIET)
if(TARGET glfw)
  set(CHAM_GLFW_TARGET glfw)
else()
  find_package(GLFW3 REQUIRED)
endif()

find_package(assimp CONFIG QUIET)
if(TARGET assimp::assimp)
  set(CHAM_ASSIMP_TARGET assimp::assimp)
else()
  find_package(ASSIMP REQUIRED)
endif()

if(UNIX AND NOT APPLE)
  find_package(OpenGL REQUIRED)
  find_package(X11 REQUIRED)
endif()

if(APPLE)
  find_library(COCOA_LIBRARY Cocoa REQUIRED)
  find_library(OPENGL_LIBRARY OpenGL REQUIRED)
  find_library(IOKIT_LIBRARY IOKit REQUIRED)
  find_library(COREVIDEO_LIBRARY CoreVideo REQUIRED)
endif()

option(CHAM_ENABLE_AUDIO "Enable audio with irrKlang when available" ON)
if(APPLE AND CHAM_ENABLE_AUDIO)
  message(WARNING "irrKlang is not bundled for macOS. Audio is disabled for Apple builds.")
  set(CHAM_ENABLE_AUDIO OFF)
endif()

if(CHAM_ENABLE_AUDIO)
  set(IRRKLANG_ROOT "${CMAKE_SOURCE_DIR}/includes/irrKlang")
  find_path(IRRKLANG_INCLUDE_DIR
    NAMES irrKlang.h
    PATHS
      "${IRRKLANG_ROOT}"
      "${IRRKLANG_ROOT}/include"
    NO_DEFAULT_PATH
  )

  if(WIN32)
    find_library(IRRKLANG_LIBRARY
      NAMES irrKlang
      PATHS
        "${CMAKE_SOURCE_DIR}/lib"
      NO_DEFAULT_PATH
    )
  elseif(UNIX AND NOT APPLE)
    find_library(IRRKLANG_LIBRARY
      NAMES IrrKlang irrKlang
      PATHS
        "${IRRKLANG_ROOT}/bin/linux-gcc-64"
        "${IRRKLANG_ROOT}/bin/linux-gcc-32"
        "${CMAKE_SOURCE_DIR}/lib"
      NO_DEFAULT_PATH
    )
  endif()

  if(NOT IRRKLANG_INCLUDE_DIR OR NOT IRRKLANG_LIBRARY)
    message(WARNING "irrKlang not found. Audio will be disabled for this build.")
    set(CHAM_ENABLE_AUDIO OFF)
  endif()
endif()

add_library(STB_IMAGE "src/stb_image.cpp")
target_include_directories(STB_IMAGE PRIVATE "${CMAKE_SOURCE_DIR}/includes")
add_library(GLAD "src/glad.c")
target_include_directories(GLAD PRIVATE "${CMAKE_SOURCE_DIR}/includes")

file(GLOB SOURCE
  "src/*.h"
  "src/*.cpp"
  "src/*.vs"
  "src/*.fs"
  "src/*.tcs"
  "src/*.tes"
  "src/*.gs"
  "src/*.cs"
  "src/App/*.cpp"
)

add_executable(${NAME} ${SOURCE})

target_include_directories(${NAME}
  PRIVATE
    "${CMAKE_SOURCE_DIR}/includes"
    "${CMAKE_BINARY_DIR}/configuration"
)

if(GLM_INCLUDE_DIR)
  target_include_directories(${NAME} PRIVATE "${GLM_INCLUDE_DIR}")
endif()

if(NOT CHAM_GLFW_TARGET)
  target_include_directories(${NAME} PRIVATE "${GLFW3_INCLUDE_DIR}")
endif()

if(NOT CHAM_ASSIMP_TARGET)
  target_include_directories(${NAME} PRIVATE "${ASSIMP_INCLUDE_DIR}")
endif()

target_link_libraries(${NAME} PRIVATE GLAD STB_IMAGE Threads::Threads)

if(CHAM_GLFW_TARGET)
  target_link_libraries(${NAME} PRIVATE ${CHAM_GLFW_TARGET})
else()
  target_link_libraries(${NAME} PRIVATE ${GLFW3_LIBRARY})
endif()

if(CHAM_ASSIMP_TARGET)
  target_link_libraries(${NAME} PRIVATE ${CHAM_ASSIMP_TARGET})
else()
  target_link_libraries(${NAME} PRIVATE ${ASSIMP_LIBRARY})
endif()

if(WIN32)
  target_link_libraries(${NAME} PRIVATE opengl32)
  target_compile_definitions(${NAME} PRIVATE _CRT_SECURE_NO_WARNINGS)
elseif(UNIX AND NOT APPLE)
  target_link_libraries(${NAME}
    PRIVATE
      OpenGL::GL
      X11
      Xrandr
      Xinerama
      Xi
      Xxf86vm
      Xcursor
      ${CMAKE_DL_LIBS}
  )
  set_target_properties(${NAME} PROPERTIES BUILD_RPATH "$ORIGIN" INSTALL_RPATH "$ORIGIN")
elseif(APPLE)
  target_link_libraries(${NAME}
    PRIVATE
      ${COCOA_LIBRARY}
      ${IOKIT_LIBRARY}
      ${OPENGL_LIBRARY}
      ${COREVIDEO_LIBRARY}
  )
endif()

if(CHAM_ENABLE_AUDIO)
  target_compile_definitions(${NAME} PRIVATE CHAM_ENABLE_AUDIO=1)
  target_include_directories(${NAME} PRIVATE "${IRRKLANG_INCLUDE_DIR}")
  target_link_libraries(${NAME} PRIVATE "${IRRKLANG_LIBRARY}")
else()
  target_compile_definitions(${NAME} PRIVATE CHAM_ENABLE_AUDIO=0)
endif()

if(MSVC)
  target_compile_options(${NAME} PRIVATE /std:c++17 /MP)
  target_link_options(${NAME} PUBLIC /ignore:4099)
  set_target_properties(${NAME} PROPERTIES VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}/bin")
endif()

set(RUNTIME_SHARED_LIBS)
if(WIN32)
  file(GLOB RUNTIME_SHARED_LIBS "${CMAKE_SOURCE_DIR}/dlls/*.dll")
elseif(UNIX AND NOT APPLE AND CHAM_ENABLE_AUDIO)
  get_filename_component(IRRKLANG_LIB_DIR "${IRRKLANG_LIBRARY}" DIRECTORY)
  file(GLOB RUNTIME_SHARED_LIBS "${IRRKLANG_LIB_DIR}/libIrrKlang.so*")
endif()

if(RUNTIME_SHARED_LIBS)
  add_custom_command(
    TARGET ${NAME}
    POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different ${RUNTIME_SHARED_LIBS} $<TARGET_FILE_DIR:${NAME}>
  )
endif()

if(MSVC)
  configure_file(
    "${CMAKE_SOURCE_DIR}/configuration/visualstudio.vcxproj.user.in"
    "${CMAKE_CURRENT_BINARY_DIR}/${NAME}.vcxproj.user"
    @ONLY
  )
endif()

