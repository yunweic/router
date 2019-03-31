
C_FILES = io.C boundary.C main.C fig.C area.C length.C

H_FILES = route.h

route: $(C_FILES) $(H_FILES) Makefile

	g++ -o route $(C_FILES) -ggdb