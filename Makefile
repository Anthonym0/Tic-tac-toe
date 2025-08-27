RAYLIB = libraylib.a
RAYLIB_SRC = raylib/src/
SRCS = main.cpp Game.cpp Cell.cpp
CC = c++
CFLAGS = -g3 -lGL -lm -lpthread -ldl -lrt -lX11


all:
	${CC} ${SRCS} ${RAYLIB_SRC}${RAYLIB} -Iraylib/src ${CFLAGS} -o a.out
