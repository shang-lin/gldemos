#CC=g++ -g -Wall
#LFLAGS=-I/opt/X11/include -L/opt/X11/lib -lglut -lGL -lGLU -lXmu -lXext -lXi -lX11 -lm

include include.mk

all: shapes animate
animate: robot.h robot.cpp animate.cpp
	$(CC) robot.cpp animate.cpp -o animate $(INCLUDES) $(LDFLAGS)

shapes: robot.h robot.cpp shapes.cpp
	$(CC) $(INCLUDES) robot.cpp shapes.cpp -o shapes $(INCLUDES) $(LDFLAGS)

clean:
	-rm -f *.o
