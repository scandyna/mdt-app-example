
set(CMAKE_C_COMPILER clang CACHE STRING "C compiler")
set(CMAKE_CXX_COMPILER clang++ CACHE STRING "C++ compiler")
set(CMAKE_BUILD_TYPE Release CACHE STRING "Build type") 
set(MDT_CXX_FLAGS_TO_APPEND "-O3 -Wall -Wextra -Werror" CACHE STRING "")
