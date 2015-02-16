include ../include.mk

SHARED=robot.h robot.cpp
all: textures

#animate: robot.h robot.cpp animate.cpp
#	$(CC) robot.cpp animate.cpp -o animate $(INCLUDES) $(LDFLAGS)

#shapes: robot.h robot.cpp shapes.cpp
#	$(CC) robot.cpp shapes.cpp -o shapes $(LDFLAGS)

textures: $(SHARED) scenery.h scenery.cpp textures.cpp
	$(CC) robot.cpp scenery.cpp textures.cpp -o textures $(INCLUDES) $(LDFLAGS)
 
clean:
	-rm -f *.o textures
	-rm -f -r *.dSYM
