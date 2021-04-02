cmake_minimum_required(VERSION 3.6.0)

project(TCEngine LANGUAGES C CXX)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(ANDROID)
	set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -funwind-tables")
	set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -funwind-tables")
endif()

set(TARGET_NAME TCEngine)

add_library(native_app_glue STATIC
		${ANDROID_NDK}/sources/android/native_app_glue/android_native_app_glue.c)
target_include_directories(native_app_glue PUBLIC
		${ANDROID_NDK}/sources/android/native_app_glue)

set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} -u ANativeActivity_onCreate")

set(TARGET_SOURCE_FILES
		src/Main.cpp
		src/Application.cpp
		src/Game.cpp
		src/Log.cpp
		src/Main.cpp
		src/StringHelper.cpp
		)

add_library(${TARGET_NAME} STATIC ${TARGET_SOURCE_FILES})
target_include_directories(${TARGET_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src)

target_include_directories(${TARGET_NAME} PUBLIC .)

target_link_libraries(${TARGET_NAME}
		android
		native_app_glue
		log
		EGL
		GLESv2)