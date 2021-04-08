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
		src/Game/Application.cpp
		src/Game/Game.cpp
		src/Game/GameClient.cpp
		src/Game/GameServer.cpp
		src/Game/GameState.cpp
		src/Game/GameWindow.cpp
		src/Utils/Log.cpp
		src/Utils/StringHelper.cpp
        src/Utils/TickRunner.cpp
		src/Graphics/GraphicsDevice.cpp
		src/Graphics/GraphicsDeviceOpenGL.cpp
		src/Graphics/GraphicsResource.cpp
		src/Graphics/Sprite.cpp
		src/Graphics/Texture2D.cpp
		src/Graphics/TextureManager.cpp
		src/Graphics/Shader.cpp
		src/Graphics/ShaderManager.cpp
		src/Graphics/Program.cpp
		src/Graphics/ProgramManager.cpp
		src/Graphics/GraphicsHelper.cpp
		src/Type/Color.cpp
		src/Type/Vector.cpp
		src/Type/Matrix.cpp
		)

add_library(${PROJECT_NAME} SHARED ${TARGET_SOURCE_FILES})

target_include_directories(${PROJECT_NAME} PUBLIC
        .
        src
        src/Game
        src/Utils
        src/Graphics)

add_subdirectory(libs/glm)

target_link_libraries(${PROJECT_NAME} PRIVATE
	android
	native_app_glue
	log
	EGL
	GLESv2
	glm
)
