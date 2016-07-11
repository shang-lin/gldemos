CC=g++ -g -Wall
LFLAGS=-L/usr/ug/lib -L/usr/X11R6/lib -lglut -lGL -lGLU -lXmu -lXext -lXi -lX11 -lm

all: shapes

shapes: robot.h robot.cpp shapes.cpp
	$(CC) robot.cpp shapes.cpp -o shapes $(LFLAGS)

clean:
	-rm -f *.o
