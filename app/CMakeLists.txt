# For more information about using CMake with Android Studio, read the
# documentation: https://d.android.com/studio/projects/add-native-code.html

# Sets the minimum version of CMake required to build the native library.

cmake_minimum_required(VERSION 3.4.1)

# Creates and names a library, sets it as either STATIC
# or SHARED, and provides the relative paths to its source code.
# You can define multiple libraries, and CMake builds them for you.
# Gradle automatically packages shared libraries with your APK.

add_library( # Sets the name of the library.
             native-lib

             # Sets the library as a shared library.
             SHARED

             # Provides a relative path to your source file(s).
             src/main/cpp/native-lib.cpp )

include_directories(
    "C:/Projects/SkiaSharp/externals/skia/include/c"
    "C:/Projects/SkiaSharp/externals/skia/include/core"
    "C:/Projects/SkiaSharp/externals/skia/include/gpu"
    "C:/Projects/SkiaSharp/externals/skia/include/config"
    )

add_library( SkiaSharp SHARED IMPORTED )
set_target_properties( SkiaSharp PROPERTIES IMPORTED_LOCATION "C:/Projects/SkiaSharp/externals/skia/out/android/arm64-v8a/libSkiaSharp.so" )

add_library( skia STATIC IMPORTED )
set_target_properties( skia PROPERTIES IMPORTED_LOCATION "C:/Projects/SkiaSharp/externals/skia/out/android/arm64-v8a/libskia.a" )

# Searches for a specified prebuilt library and stores the path as a
# variable. Because CMake includes system libraries in the search path by
# default, you only need to specify the name of the public NDK library
# you want to add. CMake verifies that the library exists before
# completing its build.

find_library( # Sets the name of the path variable.
              log-lib

              # Specifies the name of the NDK library that
              # you want CMake to locate.
              log )

# Specifies libraries CMake should link to your target library. You
# can link multiple libraries, such as libraries you define in this
# build script, prebuilt third-party libraries, or system libraries.

target_link_libraries( native-lib SkiaSharp)
target_link_libraries( native-lib skia)
target_link_libraries( native-lib ${log-lib})
target_link_libraries( native-lib EGL)
target_link_libraries( native-lib GLESv2)
