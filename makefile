chess: ChessMain.o ChessGame.o ChessPieces.o 
	g++ -Wall -g ChessMain.o ChessGame.o ChessPieces.o -o chess 

ChessMain.o: testing.cpp ChessGame.h ChessPieces.h
	g++ -Wall -g -c ChessMain.cpp -o ChessMain.o

ChessGame.o: ChessGame.cpp ChessGame.h
	g++ -Wall -g -c ChessGame.cpp -o ChessGame.o

ChessPieces.o: ChessPieces.cpp ChessPieces.h
	g++ -Wall -g -c ChessPieces.cpp -o ChessPieces.o

.PHONY: clean 
clean: 
	rm -f *.o
