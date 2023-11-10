cmake_minimum_required(VERSION 3.27)
project(sparkly-fx)

add_library(sparkly-fx SHARED)
set_property(TARGET sparkly-fx PROPERTY
  MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>"
)
target_compile_features(sparkly-fx PUBLIC cxx_std_17)

add_subdirectory(src)