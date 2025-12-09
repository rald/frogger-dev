game: main.o gl2d.o canvas.o frog.o
	gcc main.o gl2d.o canvas.o frog.o -o game -I. -L. -lGL -lglfw -lm

main.o: main.c
gl2d.o: gl2d.c gl2d.h
canvas.o: canvas.c canvas.h
frog.o: frog.c frog.h

clean:
	rm *.o game


