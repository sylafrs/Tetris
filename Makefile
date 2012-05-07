tetris: Input.o Video.o main.o SDL_Object.o
	g++ Input.o Video.o main.o -o tetris -lSDL

Exception.o: Exception.h
	g++ -c Exception.cpp -o Exception.o

SDL_Object.o: SDL_Object.h
	g++ -c SDL_Object.cpp -o SDL_Object.o

Input.o: Input.h
	g++ -c Input.cpp -o Input.o

Video.o: Video.h
	g++ -c Video.cpp -o Video.o

main.o: header.h
	g++ -c main.cpp -o main.o

clean:
	rm -rf *.o
