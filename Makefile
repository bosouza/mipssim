.PHONY: build
build: simulator.exe

bin:
	mkdir bin

bin/%.o: src/%.cpp bin
	g++ $< -std=c++11 -c -Iinc -o $@
	
simulator.exe: $(patsubst src/%.cpp,bin/%.o,$(wildcard src/*.cpp))
	g++ $^ -o $@ -std=c++11