# Sets the minimum version of CMake required to build the native
# library. You should either keep the default value or only pass a
# value of 3.4.0 or lower.

cmake_minimum_required(VERSION 3.4.1)

# Creates and names a library, sets it as either STATIC
# or SHARED, and provides the relative paths to its source code.
# You can define multiple libraries, and CMake builds it for you.
# Gradle automatically packages shared libraries with your APK.

SET(LIBHELLO_SRC
src/main/cpp/show-lib.cpp
)

add_library(
             show-li
             SHARED
             ${LIBHELLO_SRC})

set(lib_src_DIR ${CMAKE_SOURCE_DIR}/src/main/jniLibs/${ANDROID_ABI})
add_library(hello_static SHARED IMPORTED)
set_target_properties(hello_static PROPERTIES IMPORTED_LOCATION
${lib_src_DIR}/libairkiss.a)

find_library( # Sets the name of the path variable.
              log-lib
              log )
set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} -Wall -v -Wl,--no-warn-shared-textrel")
target_link_libraries(
                       show-li
                       hello_static
                       ${log-lib} )
