#include <string>

// Forward declarations 
class ChessPiece;
enum class PieceColour;

class ChessGame {
    private:
        //----------------------------------------
        // Attributes 
        //----------------------------------------
        bool validBoard;
        PieceColour toGo;    
        ChessPiece *boardState[64];
        int blackKingPosition;
        int whiteKingPosition;

        //----------------------------------------
        // Helper functions for internal use only 
        //----------------------------------------
        /**
         * @brief prints the current board state to standard output 
         * Pieces displayed as in FEN string (char for piece type, capitalization for side)
         * Empty squares shown as dots
         * NOTE:: Not used in this implementation to match the output of the tester 
         */
        void printBoard();

        /**
         * @brief checks that the piece at coordinates belongs to the player whose turn it is. Helper to validMove
         * @param index the index of the 1D array boardState selected, calculated as (rank - '1')/8 + (file -'A')%8
         * @return true if "colour" attribute of piece matches ChessGame's toGo attribute, false otherwise   
         */
        bool validTurn(const int index) const;

        /**
         * @brief resets the board state between games 
         * Clears out the board by replacing all the pointers in the boardState array with nullptr, 
         * setting toGo attribute as PieceColour::w (white), markign the board as invalid, 
         * and passing -1 as the indexes of both kings. Helper function to loadState
         */
        void clearBoard();

        /**
         * @brief checks whether there is a piece at the coordinates selected 
         * Helper function to the validMove function, confirms there is a piece at coordinates selected 
         * @param index the index of the 1D array boardState selected 
         * @return true if the value of the array isn't nullptr, otherwise false
         */
        bool piecePresent(const int index) const;

        /**
         * @brief checks whether pieces are blocking the path of the piece selected 
         * Helper function for hasLegalMoves and validMove. Does *NOT* check whether the start or the end index are nullptr
         * Does *NOT* validate the geometry of the movement, and does *NOT* validate that the target location can be captured
         * as these are all functionalities handled elsewhere. Determine the movement vector of the piece and checks whether 
         * ant pieces are on the squares the piece needs to traverse to get to the target square. 
         * @param startIndex the starting point of the piece flattened into a 1D index
         * @param endIndex the ending point of the piece flattened into a 1D index 
         * @param piece a pointer to the ChessPiece object whose path we are examining 
         * @return true if there are no other pieces on the path or if the type of piece is Knight, otherwise false 
         */
        bool noPiecesBetween(const int startIndex, const int endIndex, const ChessPiece *piece) const;
        
        /**
         * @brief determines whether any opposing pieces can capture a given square 
         * Helper function for kingInCheck and Castle possible. Checks whether a specific square can be attacked by 
         * any enemy pieces by checking squares depending on their attack patterns. 
         * @param index the index of the square of interest flattened into a 1D index
         * @param colour the colour of the team that is THREATENED
         * @return true if any enemy pieces can capture this square, otherwise false
         */
        bool locationUnderAttack(const int index, const PieceColour colour) const;

        /**
         * @brief checks whether castling is available and possible 
         * Helper function for validMove. Validates castling availability as determined by the FEN string, piece movement, 
         * and locations being threatened by enemy pieces. 
         * @param startIndex the starting point of the piece flattened into a 1D index
         * @param endIndex the ending point of the piece flattened into a 1D index
         * @return true if the king can castle to that side, otherwise false 
         */
        bool castlePossible(const int startIndex,const int endIndex) const;

        /**
         * @brief checks whether the moving piece can capture the target square
         * Helper function for validMove. Checks whether the moving piece can "capture" another square by comparing 
         * the sides of the pieces on the two squares. Does *NOT* validate whether a piece is on startIndex and 
         * does *NOT* validate piece geometry as these are handled elsewhere. 
         * @param startIndex the starting position of the moving piece as index to the 1D boardState array 
         * @param endIndex the target position of the moving piece as index to the 1D boardState array 
         * @return true if at endIndex boardState has a nullptr, or if the colour attribute of the two pieces is different, 
         * otherwise false
         */
        bool canCapture(const int startIndex, const int endIndex) const;

        /**
         * @brief validates whether a move submitted is valid 
         * Helper function for submitMove. Checks whether a move is valid in terms of having valid coordinates, 
         * pieces being present, special moves (e.g. castling), piece geometry, and possible captures.
         * @param startIndex the starting position of the moving piece as index to the 1D boardState array
         * @param endIndex the ending position of the moving piece as index to the 1D boardState array
         * @return true if all of the above factors are valid, otherwise false 
         */
        bool validMove(const int startIndex, const int endIndex);

        /**
         * @brief checks whether the king is currently in check 
         * Basically a wrapper for locationUnderAttack(). Logs in terminal that the player is in check 
         * @param kingCoordinates the index of boardState where the king of interest resides 
         * @return true if the king is in check, otherwise false
         */
        bool kingInCheck(const int kingCoordinates) const ;

        /**
         * @brief checks whether a proposed move is illegal (i.e. exposing your own king to a check)
         * Helper function for submitMove. Checks whether a proposed move would expose you own king to a check. 
         * Does *NOT* check whether the move is valid under any other conditions (e.g. geometry), since this is handled by validMove. 
         * Does *NOT* check whether your move is smart
         * @param startIndex the starting position of the moving piece as index to the 1D boardState array
         * @param endIndex the ending position of the moving piece as index to the 1D boardState array
         * @return true if the king is not exposed to a check, false otherwise.
         */
        bool isMoveSafe(const int startIndex, const int endIndex);
        
        /**
         * @brief commits the changes to the board
         * Helper function for submitMove. Logs the movement and updates ChessGame to reflect the latest gamestate 
         * Does NOT check for move validity, and does NOT check for end conditions to the game. 
         * @param startIndex the starting position of the moving piece as index to the 1D boardState array
         * @param endIndex the ending position of the moving piece as index to the 1D boardState array
         */
        void commitMove(const int startIndex, const int endIndex);
        
        /**
         * @brief simulates all possible moves to determine end game conditions 
         * Helper function for isCheckmate and isStalemate. Simulates all possible moves to identify whether 
         * a given player has moves available to them. 
         * @param colour the colour of the pieces we are investigating 
         * @return true if any legal moves remain, false otherwise
         */
        bool hasLegalMoves(const PieceColour colour);

        /**
         * @brief checks whether a player with no legal moves is in check
         * Uses kingInCheck and hasLegalMoves to confirm whether a player is in checkmate. By default it checks whether 
         * after a move the OPPONENT is in checkmate 
         * @param colour the colour of the player who might be in checkmate 
         * @return true if player is in checkmate, false otherwise
         */
        bool isCheckmate(const PieceColour colour);

        /**
         * @brief checks whether a player with no legal moves is in check 
         * @param colour the colour of the player in question 
         * @return true if we have a stalemate, false otherwise
         */
        bool isStalemate(const PieceColour colour);

    public:
        //----------------------------------------
        // Interface for users 
        //----------------------------------------
        
        /**
         * @brief constructor for the ChessGame Class 
         * ChessGame works as the engine for the game keeping track of whose turn it is, where the kings are, which board 
         * pieces are at a given location, whether the board has been set, and provides an interface for the users to play. 
         * The constructor initializes these variables to  nullptr and values that would 
         * otherwise flag the game as in a non-playable state, but without causing breaks 
         * @return returns a ChessGame object 
         */
        ChessGame();

        /**
         * @brief destructor for the ChessGame Class 
         * calls delete on every pointer in the boardState array to prevent memory leaks
         */
        ~ChessGame();

        /**
         * @brief making the copy constructor forbidden 
         * Because of the raw pointers stored in boardState, copying the object could lead to double free errors or 
         * other memory management issues. There is also no reason why you would want to copy a 
         * ChessGame as anything other than a FEN string to use later. Rather than implementing a deep copy mechanism
         * we make the act of copying or assigning to a ChessGame forbidden  
         */
        ChessGame(const ChessGame&) = delete;

        /**
         * @brief making the assignment operator forbidden 
         */
        ChessGame &operator=(const ChessGame&) = delete;

        /**
         * @brief prepares the ChessGame variable into a given board state 
         * Allows the user to resume a game by passing in the string. The function takes care of setting the piece positions 
         * clearing the board of previous pieces, and setting the internal variables that track turn etc. 
         * @param fen the FEN representation of the game being loaded 
         */
        void loadState(std::string fen);

        /**
         * @brief submits the desired move into the chess engine 
         * The primary interface through which the players interact with the game. They just need to submit their desired move
         * in standard chess notation. The validation checks happen through helper functions as part of the submitMove call
         * Invalid moves (e.g. invalid coordinates, illegal moves) are rejected and a message is logged. If an invalid move is 
         * entered, the player retains their turn and is allowed to submit another move. 
         * @param startPosition the square on which the piece you wish to move is in standard chess notation (e.g. A2)
         * @param endPosition the square to which you wish to move the piece in standard chess notation(e.g. A3)
         */
        void submitMove(const char *startPosition,const char *endPosition);
    };