SET(arcc_lib_src Collision.c Font.c Log.c Point.c Size.c Texture.c Util.c Draw.c Input.c Math.c Rect.c Sound.c Time.c Window.c internal/input/Mouse.c internal/input/Keyboard.c)
INCLUDE_DIRECTORIES(/usr/include /usr/include/freetype2)
ADD_DEFINITIONS(-O0 -g3 -Wall -c -fmessage-length=0 -std=gnu99 -Wstrict-prototypes -Wall -fPIC -shared)
ADD_LIBRARY(arcc SHARED ${arcc_lib_src})


