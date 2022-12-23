#include <iostream>
#include <cstring>  // for strcmp()

const int ROWS = 3;
const int COLS = 3;

char board[ROWS][COLS] = {};  // Initialize all cells to be empty
int moves = 0;  // Keep track of the number of moves

void clearScreen() {
    // Clear the screen
    std::cout << "\033[2J\033[1;1H";
}

bool isValidMove(int row, char col) {
    // Convert the column letter to a column index (0, 1, or 2)
    int colIndex = -1;
    if (col == 'A' || col == 'a') {
        colIndex = 0;
    }
    else if (col == 'B' || col == 'b') {
        colIndex = 1;
    }
    else if (col == 'C' || col == 'c') {
        colIndex = 2;
    }

    // Check if the column index is within the valid range
    if (colIndex < 0 || colIndex >= COLS) {
        std::cout << "Invalid move. Please try again." << std::endl;
        return false;
    }

    // Check if the row value is within the valid range
    if (row < 1 || row > ROWS) {
        std::cout << "Invalid move. Please try again." << std::endl;
        return false;
    }

    // Convert the row label to a row index (0, 1, or 2)
    int rowIndex = row - 1;

    // Check if the cell is empty
    if (board[rowIndex][colIndex] != '\0') {
        std::cout << "That cell is already occupied. Please try again." << std::endl;
        return false;
    }

    // If the row and column values are within the valid range and the cell is empty, return true
    return true;
}

void updateBoard(int row, int col, char player) {
    board[row][col] = player;  // Update the game board with the player's move
    moves++;  // Increment the number of moves
}

bool checkForWin(char player) {
    // Check for three in a row horizontally
    for (int i = 0; i < ROWS; i++) {
        if (board[i][0] == player && board[i][1] == player && board[i][2] == player) {
            return true;
        }
    }
    // Check for three in a row vertically
    for (int j = 0; j < COLS; j++) {
        if (board[0][j] == player && board[1][j] == player && board[2][j] == player) {
            return true;
        }
    }

    // Check for three in a row diagonally
    if (board[0][0] == player && board[1][1] == player && board[2][2] == player) {
        return true;
    }
    if (board[0][2] == player && board[1][1] == player && board[2][0] == player) {
        return true;
    }

    // If none of the above conditions are met, return false
    return false;
}

bool checkForDraw() {
    // Check if all cells are filled
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            if (board[i][j] == '\0') {  // '\0' represents an empty cell
                return false;
            }
        }
    }

    // If all cells are filled and no winner, return true
    std::cout << "The game has ended in a draw." << std::endl;
    return true;
}

void resetGame() {
    // Reset the game board
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            board[i][j] = '\0';
        }
    }
    moves = 0;  // Reset the number of moves

    // Prompt the players to start a new game
    std::cout << "New game started. Player X goes first." << std::endl;
}
int main() {
    bool gameOver = false;
    char player = 'X';  // Start with X
    while (!gameOver) {
        clearScreen();  // Clear the screen before displaying the game board

        // Display the game board
        std::cout << "    A B C" << std::endl;
        for (int i = 0; i < ROWS; i++) {
            std::cout << i + 1 << "   ";
            for (int j = 0; j < COLS; j++) {
                std::cout << board[i][j] << " ";
            }
            std::cout << std::endl;
        }

        // Prompt the player for their move
        std::cout << "Player " << player << ", enter your move (row column): ";
        int row;
        char col;
        std::cin >> row >> col;

        // Check if the move is vaild
        if (isValidMove(row, col)) {
            // Convert the column letter to a column index (0, 1, or 2)
            int colIndex = -1;
            if (col == 'A' || col == 'a') {
                colIndex = 0;
            }
            else if (col == 'B' || col == 'b') {
                colIndex = 1;
            }
            else if (col == 'C' || col == 'c') {
                colIndex = 2;
            }

            // Convert the row label to a row index (0, 1, or 2)
            int rowIndex = row - 1;

            // Update the game board with the player's move
            updateBoard(rowIndex, colIndex, player);

            // Check if the player has won
            if (checkForWin(player)) {
                std::cout << "Player " << player << " has won!" << std::endl;
                gameOver = true;
                continue;
            }
            // Check if the game has ended in a draw
            if (checkForDraw()) {
                gameOver = true;
                continue;
            }

            // Switch to the other player
            if (player == 'X') {
                player = 'O';
            }
            else {
                player = 'X';
            }
        }
    }
    // Prompt the players to start a new game
    std::cout << "Type 'reset' to start a new game: ";
    std::string input;
    std::cin >> input;
    // If the player wants to start a new game, reset the game
    if (strcmp(input.c_str(), "reset") == 0) {
        resetGame();
    }

    return 0;
}