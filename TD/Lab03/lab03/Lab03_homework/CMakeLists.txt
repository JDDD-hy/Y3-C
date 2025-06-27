 cmake_minimum_required(VERSION 3.0)
 project(Lab03_homework)
 add_executable(main main.c)
 if(MSVC)
 target_compile_options(main PRIVATE /W4)
 else()
 target_compile_options(main PRIVATE -Wall)
 endif()
 