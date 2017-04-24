shell=/bin/bash

all:
	gcc demo.c fancy-progress.c -I. -o demo
	./demo

clean:
	rm -f demo
