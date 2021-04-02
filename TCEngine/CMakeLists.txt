cmake_minimum_required(VERSION 3.6.0)
project(TCEngine LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")

if(ANDROID)
	set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -funwind-tables")
	set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -funwind-tables")
endif()

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

add_library(${PROJECT_NAME} SHARED ${TARGET_SOURCE_FILES})

target_include_directories(${PROJECT_NAME} PUBLIC . src)

target_link_libraries(${PROJECT_NAME} PRIVATE
	android
	native_app_glue
	log
	EGL
	GLESv2
)
