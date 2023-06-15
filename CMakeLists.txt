cmake_minimum_required(VERSION 3.27)
project(sparkly-fx)

add_library(sparkly-fx SHARED)
set_property(TARGET sparkly-fx PROPERTY
  MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>"
)

add_subdirectory(src)