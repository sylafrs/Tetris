bin/tetris: obj/Input.o obj/Video.o obj/main.o obj/SDL_Object.o obj/Exception.o
	g++ obj/Input.o obj/Video.o obj/main.o obj/Exception.o obj/SDL_Object.o -o bin/tetris -lSDL

obj/Exception.o: src/Exception.cpp include/Exception.h
	g++ -c src/Exception.cpp -o obj/Exception.o

obj/SDL_Object.o: src/SDL_Object.cpp include/SDL_Object.h
	g++ -c src/SDL_Object.cpp -o obj/SDL_Object.o

obj/Input.o: src/Input.cpp include/Input.h
	g++ -c src/Input.cpp -o obj/Input.o

obj/Video.o: src/Video.cpp include/Video.h
	g++ -c src/Video.cpp -o obj/Video.o

obj/main.o: src/main.cpp
	g++ -c src/main.cpp -o obj/main.o

clean:
	rm -rf obj/*.o
