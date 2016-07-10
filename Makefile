#CC=g++ -g -Wall
#LFLAGS=-I/opt/X11/include -L/opt/X11/lib -lglut -lGL -lGLU -lXmu -lXext -lXi -lX11 -lm

include include.mk

all: shapes

shapes: robot.h robot.cpp shapes.cpp
	$(CC) $(INCLUDES) robot.cpp shapes.cpp -o shapes $(LDFLAGS)

clean:
	-rm -f *.o
