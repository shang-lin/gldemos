include ../include.mk

all: animate 

animate: robot.h robot.cpp animate.cpp
	$(CC) robot.cpp animate.cpp -o animate $(INCLUDES) $(LDFLAGS)

clean:
	-rm -f *.o animate
	-rm -f -r *.dSYM
