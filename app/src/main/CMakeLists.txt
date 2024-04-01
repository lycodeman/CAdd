# For more information about using CMake with Android Studio, read the
# documentation: https://d.android.com/studio/projects/add-native-code.html.
# For more examples on how to use CMake, see https://github.com/android/ndk-samples.

# Sets the minimum CMake version required for this project.
cmake_minimum_required(VERSION 3.22.1)

# Declares the project name. The project name can be accessed via ${ PROJECT_NAME},
# Since this is the top level CMakeLists.txt, the project name is also accessible
# with ${CMAKE_PROJECT_NAME} (both CMake variables are in-sync within the top level
# build script scope).
project("cadd")

# Creates and names a library, sets it as either STATIC
# or SHARED, and provides the relative paths to its source code.
# You can define multiple libraries, and CMake builds them for you.
# Gradle automatically packages shared libraries with your APK.
#
# In this top level CMakeLists.txt, ${CMAKE_PROJECT_NAME} is used to define
# the target library name; in the sub-module's CMakeLists.txt, ${PROJECT_NAME}
# is preferred for the same purpose.
#
# In order to load a library into your app from Java/Kotlin, you must call
# System.loadLibrary() and pass the name of the library defined here;
# for GameActivity/NativeActivity derived applications, the same library name must be
# used in the AndroidManifest.xml file.

add_library(${CMAKE_PROJECT_NAME} SHARED
        # List C/C++ source files with relative paths to this CMakeLists.txt.
        cpp/native-lib.cpp)

#message(STATUS "CMAKE_SOURCE_DIR: ${CMAKE_SOURCE_DIR}")
#add_library(toolchains1 SHARED IMPORTED)
#set_target_properties(
#        toolchains1
#        PROPERTIES IMPORTED_LOCATION
#        ${CMAKE_SOURCE_DIR}/jniLibs/${CMAKE_ANDROID_ARCH_ABI}/libtoolchains1.so
##        /Users/ly/AndroidStudioProjects/CAdd/app/src/main/jniLibs/arm64-v8a/libtoolchains1.so
#)
#add_library(toolchains2 SHARED IMPORTED)
#set_target_properties(
#        toolchains2
#        PROPERTIES IMPORTED_LOCATION
#        ${CMAKE_SOURCE_DIR}/jniLibs/${CMAKE_ANDROID_ARCH_ABI}/libtoolchains2.so
##        /Users/ly/AndroidStudioProjects/CAdd/app/src/main/jniLibs/arm64-v8a/libtoolchains2.so
#)

#target_link_libraries(myApp ${TOOLCHAINS_LIB})
# 添加头文件搜索路径
#include_directories(${CMAKE_SOURCE_DIR}/src/main/cpp/include)

# 添加库搜索路径
#link_directories(${CMAKE_SOURCE_DIR}/src/main/jniLibs/${ANDROID_ABI})

#add_library(android_test SHARED IMPORTED)
#set_target_properties(
#        android_test
#        PROPERTIES IMPORTED_LOCATION
#        ${CMAKE_SOURCE_DIR}/../jniLibs/${CMAKE_ANDROID_ARCH_ABI}/libandroid_test1.so
#)

#add_library(qt_5core SHARED IMPORTED)
#set_target_properties(
#        qt_5core
#        PROPERTIES IMPORTED_LOCATION
#        ${CMAKE_SOURCE_DIR}/../jniLibs/${CMAKE_ANDROID_ARCH_ABI}/libQt5Core.so
#)
#
#target_include_directories(${CMAKE_PROJECT_NAME} PUBLIC toolchains1.h)
#include_directories(/Users/ly/AndroidStudioProjects/CAdd/toolchains1/src/main/cpp)
#target_include_directories(toolchains2 PUBLIC /Users/ly/AndroidStudioProjects/CAdd/toolchains1/src/main/cpp/toolchains2.h)
#add_library(test-dlopen SHARED
#        # List C/C++ source files with relative paths to this CMakeLists.txt.
#        dlopen/test-dlopen.cpp)
#message("======"+${CMAKE_PROJECT_NAME})
#add_library(off_line SHARED
#        # List C/C++ source files with relative paths to this CMakeLists.txt.
#        ${CMAKE_SOURCE_DIR}/libModuleOfflineD.so)
# 设置变量
# CMAKE_CXX_FLAGS 表示会将 C++ 的参数传给编译器
# CMAKE_C_FLAGS 表示会将 C 参数传给编译器

# 参数设置 : 传递 CMAKE_CXX_FLAGS C+= 参数给编译器时 , 在 该参数后面指定库的路径
#   CMAKE_SOURCE_DIR 指的是当前的文件地址
#   -L 参数指定动态库的查找路径
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -L${CMAKE_SOURCE_DIR}/${ANDROID_ABI}")
message("CMAKE_SOURCE_DIR : ${CMAKE_SOURCE_DIR}, ANDROID_ABI : ${ANDROID_ABI}")
#message("${CMAKE_SOURCE_DIR}/${ANDROID_ABI}/libtest.so")
#message(" libtest = "+libtest)
#find_library(libModuleOfflineD libModuleOfflineD.so ${CMAKE_SOURCE_DIR}/${ANDROID_ABI})
# Specifies libraries CMake should link to your target library. You
# can link libraries from various origins, such as libraries defined in this
# build script, prebuilt third-party libraries, or Android system libraries.
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -L${CMAKE_SOURCE_DIR}/../jniLibs/${CMAKE_ANDROID_ARCH_ABI}")
#add_subdirectory()
target_link_libraries(
        ${CMAKE_PROJECT_NAME}
        # List libraries link to the target library
#        libModuleOfflineD

        android
        log
        ${CMAKE_SOURCE_DIR}/jniLibs/${CMAKE_ANDROID_ARCH_ABI}/libtoolchains1.so
#        toolchains1
        ${CMAKE_SOURCE_DIR}/jniLibs/${CMAKE_ANDROID_ARCH_ABI}/libtoolchains2.so
#        ${CMAKE_SOURCE_DIR}/jniLibs/${CMAKE_ANDROID_ARCH_ABI}/libandroid_test.so
#        ${CMAKE_SOURCE_DIR}/jniLibs/${CMAKE_ANDROID_ARCH_ABI}/libQt5Core.so
#        ${CMAKE_SOURCE_DIR}/jniLibs/${CMAKE_ANDROID_ARCH_ABI}/libc++_shared.so
#        toolchains2
#        ${TOOLCHAINS_LIB}
)
#target_link_libraries(
#        # List libraries link to the target library
##        libModuleOfflineD
#
#        android
#        log
#)
