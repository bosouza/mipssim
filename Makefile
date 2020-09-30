.PHONY: build
build: simulator.exe

.PHONY: build-debug
build-debug: simulator-debug.exe

bin:
	mkdir -p bin

bin/%.o: src/%.cpp bin
	g++ $< -std=c++17 -c -Iinc -o $@

bin/%.o.dbg: src/%.cpp bin
	g++ -g $< -std=c++17 -c -Iinc -o $@
	
simulator.exe: $(patsubst src/%.cpp,bin/%.o,$(wildcard src/*.cpp))
	g++ $^ -o $@ -std=c++17

simulator-debug.exe: $(patsubst src/%.cpp,bin/%.o.dbg,$(wildcard src/*.cpp))
	g++ -g $^ -o $@ -std=c++17