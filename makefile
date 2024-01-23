all:
	g++ -Isrc/include -Lsrc/lib -o target/main src/main.cpp src/mathy.cpp -lmingw32 -lSDL2main -lSDL2