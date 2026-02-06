cmake_minimum_required(VERSION 3.16)
project(PolygonInfection LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

file(GLOB SRC_FILES CONFIGURE_DEPENDS "${CMAKE_SOURCE_DIR}/src/*.cpp")
add_executable(polygon-infection ${SRC_FILES})

find_package(PkgConfig REQUIRED)
pkg_check_modules(ALLEGRO REQUIRED
  allegro-5
  allegro_font-5
  allegro_ttf-5
  allegro_primitives-5
  allegro_image-5
  allegro_audio-5
  allegro_acodec-5
)

target_include_directories(polygon-infection PRIVATE ${ALLEGRO_INCLUDE_DIRS})
target_compile_options(polygon-infection PRIVATE ${ALLEGRO_CFLAGS_OTHER})
target_link_directories(polygon-infection PRIVATE ${ALLEGRO_LIBRARY_DIRS})
target_link_libraries(polygon-infection PRIVATE ${ALLEGRO_LIBRARIES})

# Ensure pkg-config paths are honored for local installs
if(DEFINED ENV{PKG_CONFIG_PATH})
  message(STATUS "PKG_CONFIG_PATH=$ENV{PKG_CONFIG_PATH}")
endif()
