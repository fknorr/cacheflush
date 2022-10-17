cmake_minimum_required(VERSION 3.18)
project(cacheflush C)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wextra")

if(CMAKE_SYSTEM_PROCESSOR STREQUAL ppc64le)
    set(ARCH_C power9.c)
elseif(CMAKE_SYSTEM_PROCESSOR STREQUAL x86_64)
    set(ARCH_C x86_64.c)
else()
    message(FATAL_ERROR "Not implemented for this system")
endif()

add_library(cacheflush cacheflush.h ${ARCH_C})
