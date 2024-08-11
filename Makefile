main: scanner.o lexer.o
	g++ src/main.cpp scanner.o lexer.o -o main

scanner.o: src/scanner.cpp
	g++ -c src/scanner.cpp

lexer.o: src/lexer.cpp
	g++ -c src/lexer.cpp

clean:
	rm -f main lexer.o scanner.o