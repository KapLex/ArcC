PROJECT(ArcLib)

INCLUDE_DIRECTORIES(ARCC)
ADD_DEFINITIONS(-O0 -g3 -Wall -c -fmessage-length=0 -std=gnu99 -Wstrict-prototypes -Wall -fPIC -shared)

ADD_SUBDIRECTORY(ARCC) 
