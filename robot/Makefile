CC=g++ -g -Wall
LFLAGS=-I/opt/X11/include -L/opt/X11/lib -lglut -lGL -lGLU -lXmu -lXext -lXi -lX11 -lm

all: shapes

shapes: robot.h robot.cpp shapes.cpp
	$(CC) robot.cpp shapes.cpp -o shapes $(LFLAGS)

clean:
	-rm -f *.o
