INCDIR = include/
LIBDIR = lib/
LDFLAGS = -lfmt

all:
	g++ -I ${INCDIR} -L ${LIBDIR} src/cpu.cpp src/main.cpp -o bin/gb.app ${LDFLAGS}

clean:
	rm bin/gb.app

run:
	./bin/gb.app