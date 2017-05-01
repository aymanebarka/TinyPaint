# Makefile

CC=gcc

CPPFLAGS= `pkg-config --cflags --libs gtk+-3.0`
CFLAGS= -Wall -Wextra -Werror -std=c99 -pedantic -O3 -lm
LDFLAGS=
LDLIBS= `pkg-config  --libs gtk+-3.0`

SRC= src/GUI.c
OBJ= ${SRC:.c=.o}

all: GUI

GUI:
	${CC} ${SRC} -o TinyPaint ${CFLAGS} ${CPPFLAGS}
	
clean:
	rm -f *~ *.o
	rm -f TinyPaint .png.tmp*

# END
