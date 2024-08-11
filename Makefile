build/main: scanner.o lexer.o build
	g++ src/main.cpp build/scanner.o build/lexer.o -o build/main

scanner.o: src/scanner.cpp build
	g++ -c src/scanner.cpp -o build/scanner.o

lexer.o: src/lexer.cpp
	g++ -c src/lexer.cpp -o build/lexer.o

build:
	mkdir build

clean:
	rm -rf build