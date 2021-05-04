cmake_minimum_required(VERSION 3.6.0)
project(TCEngine LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")

if(ANDROID)
	set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -funwind-tables")
	set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -funwind-tables")
endif()

if(ANDROID)
	add_library(native_app_glue STATIC
			${ANDROID_NDK}/sources/android/native_app_glue/android_native_app_glue.c)
	target_include_directories(native_app_glue PUBLIC
			${ANDROID_NDK}/sources/android/native_app_glue)

	set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} -u ANativeActivity_onCreate")
endif()

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
		src/Utils/FileMapper.cpp
		src/Utils/File.cpp
		src/Graphics/GraphicsDevice.cpp
		src/Graphics/GraphicsDeviceOpenGL.cpp
		src/Graphics/GraphicsResource.cpp
		src/Graphics/Sprite.cpp
		src/Graphics/Texture.cpp
		src/Graphics/TextureManager.cpp
		src/Graphics/Shader.cpp
		src/Graphics/ShaderManager.cpp
		src/Graphics/Program.cpp
		src/Graphics/ProgramManager.cpp
		src/Graphics/GraphicsHelper.cpp
		src/Type/Type.cpp
		src/NetWork/SingleSocketPool.cpp
		src/NetWork/TCSocket.cpp
		src/NetWork/NetClient.cpp
		src/NetWork/NetPacket.cpp
		src/NetWork/NetPacketWriter.cpp
		src/NetWork/NetPacketReader.cpp
		src/NetWork/NetSession.cpp
		)

add_library(${PROJECT_NAME} SHARED ${TARGET_SOURCE_FILES})

target_include_directories(${PROJECT_NAME} PUBLIC
        src
        src/Game
        src/Utils
        src/Graphics
		src/Core
		src/NetWork
				)

add_subdirectory(libs/glm)

target_include_directories(${PROJECT_NAME} PUBLIC libs/stb)

# 暂时不使用SDL库
#add_library(libSDL2 SHARED IMPORTED)
#set_property(TARGET libSDL2
#		PROPERTY IMPORTED_LOCATION
#		${PROJECT_SOURCE_DIR}/libs/SDL2/${ANDROID_ABI}/libSDL2.so)
#
#add_library(libhidapi SHARED IMPORTED)
#set_property(TARGET libhidapi
#		PROPERTY IMPORTED_LOCATION
#		${PROJECT_SOURCE_DIR}/libs/SDL2/${ANDROID_ABI}/libhidapi.so)
#
#add_library(libSDL2_image SHARED IMPORTED)
#set_property(TARGET libSDL2_image
#		PROPERTY IMPORTED_LOCATION
#		${PROJECT_SOURCE_DIR}/libs/SDL2/${ANDROID_ABI}/libSDL2_image.so)
#
#target_include_directories(${PROJECT_NAME} PUBLIC libs/SDL2/include)

target_link_libraries(${PROJECT_NAME} PRIVATE
	glm
#	libSDL2
#	libhidapi
#	libSDL2_image
)

if(ANDROID)
	target_link_libraries(${PROJECT_NAME} PRIVATE
	android
	native_app_glue
	log
	EGL
	GLESv2
	)
endif()