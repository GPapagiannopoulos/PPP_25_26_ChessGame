testing: testing.o ChessGame.o ChessPieces.o 
	g++ -Wall -g testing.o ChessGame.o ChessPieces.o -o testing 

testing.o: testing.cpp ChessGame.h ChessPieces.h
	g++ -Wall -g -c testing.cpp -o testing.o

ChessGame.o: ChessGame.cpp ChessGame.h
	g++ -Wall -g -c ChessGame.cpp -o ChessGame.o

ChessPieces.o: ChessPieces.cpp ChessPieces.h
	g++ -Wall -g -c ChessPieces.cpp -o ChessPieces.o

.PHONY: clean 
clean: 
	rm -f *.o
