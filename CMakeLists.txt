cmake_minimum_required(VERSION 2.8)

# remove MinSizeRel and RelWithDebInfo configurations
set(CMAKE_CONFIGURATION_TYPES Debug Release CACHE TYPE INTERNAL FORCE)
project(pacman)

add_executable(pacman
  src/actor.cpp
  src/actor.h
  src/game.cpp
  src/game.h
  src/gameplay_constants.cpp
  src/gameplay_constants.h
  src/ghost_modes.cpp
  src/ghost_modes.h
  src/ghost_strategies.cpp
  src/ghost.cpp
  src/ghost.h
  src/main.cpp
  src/maze.cpp
  src/maze.h
  src/pacman.cpp
  src/pacman.h
  src/pch.cpp
  src/pch.h
  src/sprite_factory.cpp
  src/sprite_factory.h)

option(USE_STATIC_STD_LIBS "Link system libraries statically." OFF)

# add SFML library dependencies
add_subdirectory("third_party/lib/SFML")
include_directories("third_party/lib/SFML/include")
target_link_libraries(${CMAKE_PROJECT_NAME} sfml-system sfml-window sfml-graphics)

# add additional compiler and linker flags
if (${CMAKE_CXX_COMPILER_ID} STREQUAL "GNU" OR ${CMAKE_CXX_COMPILER_ID} STREQUAL "Clang")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-unused-result -Wno-switch")
  set(CMAKE_EXE_LINKER_FLAGS_RELEASE "${CMAKE_EXE_LINKER_FLAGS_RELEASE} -s")
  if (${USE_STATIC_STD_LIBS})
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -static-libgcc -static-libstdc++")
  endif ()
elseif (${CMAKE_CXX_COMPILER_ID} STREQUAL "MSVC")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /MP /D_CRT_SECURE_NO_WARNINGS")
  set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /Ox /GL")
  set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /INCREMENTAL")
  set(CMAKE_EXE_LINKER_FLAGS_RELEASE "${CMAKE_EXE_LINKER_FLAGS_RELEASE} /LTCG /SUBSYSTEM:WINDOWS")

  if (${USE_STATIC_STD_LIBS})
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /MTd")
    set(CMAKE_CXX_FLAGS_RELEASE "{$CMAKE_CXX_FLAGS_RELEASE} /MT")
  endif ()

  # copy DLL files into Pacman binary directory using post build even
  add_custom_command(TARGET ${CMAKE_PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
      "${CMAKE_CURRENT_BINARY_DIR}/third_party/lib/SFML/lib/$<CONFIGURATION>"
      "$<TARGET_FILE_DIR:${CMAKE_PROJECT_NAME}>")
else ()
  message(FATAL_ERROR "Unsupported compiler ${CMAKE_CXX_COMPILER_ID}.")
endif ()

# copy game assets
if (NOT ${CMAKE_CURRENT_SOURCE_DIR} STREQUAL ${CMAKE_CURRENT_BINARY_DIR})
  file(COPY ${CMAKE_SOURCE_DIR}/assets DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
endif()
