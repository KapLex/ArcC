# ########## Project setup ##########
PROJECT(ARCC)
CMAKE_MINIMUM_REQUIRED(VERSION 2.4.5)

## Required Libraries 
Find_Package ( SDL REQUIRED )
Find_Package ( SDL_image REQUIRED ) 
Find_Package ( OpenGL REQUIRED )
Find_Package ( OpenAL REQUIRED )
Find_Package ( Freetype REQUIRED )

# ######### General setup ##########
INCLUDE_DIRECTORIES(${CMAKE_SOURCE_DIR} /usr/include /usr/include/freetype2)
ADD_DEFINITIONS(-O0 -g3 -Wall -c -fmessage-length=0 -std=gnu99 -Wstrict-prototypes -Wall -fPIC -shared)

# ########## ARCC library ##########
# Sources:
SET(ARCC_library_SRCS
    Rect.c
    Math.c
    Window.c
    Sound.c
    Log.c
    Draw.c
    Input.c
    Font.c
    Texture.c
    Point.c
    Size.c
    Util.c
    Time.c
    Collision.c
    Keyboard.c
    Mouse.c
)

# Headers:
SET(ARCC_library_HDRS
    Texture.h
    Rect.h
    ARC.h
    Window.h
    Font.h
    Util.h
    Time.h
    Point.h
    Sound.h
    Math.h
    Log.h
    Input.h
    Draw.h
    Collision.h
    Size.h
    Types.h
    Keyboard.h
    Mouse.h
)

# actual target:
ADD_LIBRARY(ARCC SHARED ${ARCC_library_SRCS} ${ARCC_library_HDRS})
SET_TARGET_PROPERTIES(ARCC PROPERTIES VERSION 0.0.0)
SET_TARGET_PROPERTIES(ARCC PROPERTIES LINKER_LANGUAGE C)
SET_TARGET_PROPERTIES(ARCC PROPERTIES PUBLIC_HEADER "${ARCC_library_HDRS}")

# add install target:
INSTALL(TARGETS ARCC DESTINATION lib
                PUBLIC_HEADER DESTINATION include/ARCC)

