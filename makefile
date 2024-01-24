all:
	g++ -Isrc/include -Lsrc/lib -o target/step_test src/tests/step_test.cpp src/doomy.cpp src/mathy.cpp src/draw.cpp -lmingw32 -lSDL2main -lSDL2