#CC=g++ -g -Wall
#LFLAGS=-I/opt/X11/include -L/opt/X11/lib -lglut -lGL -lGLU -lXmu -lXext -lXi -lX11 -lm

include include.mk

all: shapes animate textures
animate: robot.h robot.cpp animate.cpp
	$(CC) robot.cpp animate.cpp -o animate $(INCLUDES) $(LDFLAGS)

shapes: robot.h robot.cpp shapes.cpp
	$(CC) $(INCLUDES) robot.cpp shapes.cpp -o shapes $(INCLUDES) $(LDFLAGS)

textures: robot.h robot.cpp scenery.h scenery.cpp textures.cpp
	$(CC) robot.cpp scenery.cpp textures.cpp -o textures $(INCLUDES) $(LDFLAGS)

clean:
	-rm -f *.o
