# ########## Project setup ##########
PROJECT(examples)
CMAKE_MINIMUM_REQUIRED(VERSION 2.4.5)

## Required libraries  
Find_Package ( SDL REQUIRED )
Find_Package ( SDL_image REQUIRED ) 
Find_Package ( OpenGL REQUIRED )
Find_Package ( OpenAL REQUIRED )
Find_Package ( Freetype REQUIRED )

# ######### General setup ##########
INCLUDE_DIRECTORIES(${CMAKE_SOURCE_DIR} /usr/local/include/ARCC /usr/include/freetype2)
ADD_DEFINITIONS(-O0 -g3 -Wall -fmessage-length=0 -std=gnu99 -Wall -Wunused)

# actual target:
ADD_EXECUTABLE(input input.c)
TARGET_LINK_LIBRARIES(input ARCC SDL SDL_image GL GLU freetype log4c openal alut vorbisfile ogg)

ADD_EXECUTABLE(window window.c)
TARGET_LINK_LIBRARIES(window ARCC SDL SDL_image GL GLU freetype log4c openal alut vorbisfile ogg)

ADD_EXECUTABLE(draw draw.c)
TARGET_LINK_LIBRARIES(draw ARCC SDL SDL_image GL GLU freetype log4c openal alut vorbisfile ogg)

