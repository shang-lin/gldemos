CC=g++ -g -Wall
LFLAGS=-I/opt/X11/include -L/opt/X11/lib -lglut -lGL -lGLU -lXmu -lXext -lXi -lX11 -lm

all: robot

robot: 
	make -C robot

clean:
	-rm -f *.o
