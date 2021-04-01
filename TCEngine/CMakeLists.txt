cmake_minimum_required(VERSION 3.6.0)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall")

set(TARGET_NAME TCEngine)

file(GLOB TARGET_HEADER_FILES src/*.h>)
aux_source_directory(src TARGET_SOURCE_FILES)

add_library(native_app_glue STATIC
    ${ANDROID_NDK}/sources/android/native_app_glue/android_native_app_glue.c)
target_include_directories(native_app_glue PUBLIC
    ${ANDROID_NDK}/sources/android/native_app_glue)

set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} -u ANativeActivity_onCreate")

add_library(${TARGET_NAME} SHARED
	${TARGET_SOURCE_FILES} ${TARGET_HEADER_FILES})

target_include_directories(${TARGET_NAME} PUBLIC .)

target_link_libraries(${TARGET_NAME}
	android
	native_app_glue
	log
	EGL
	GLESv2)