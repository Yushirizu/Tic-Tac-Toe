#include <iostream>
#include <cstring>  // for strcmp()

const int ROWS = 3;
const int COLS = 3;

char board[ROWS][COLS] = {};  // Initialize all cells to be empty
int moves = 0;  // Keep track of the number of moves

void updateBoard(int row, int col, char player, bool& clearScreen) {
    if (board[row][col] == '\0') {  // Check if the cell is empty
        board[row][col] = player;  // Update the game board with the player's move
        moves++;  // Increment the number of moves
    }
    else {
        std::cout << "That cell is already occupied. Please try again." << std::endl;
        clearScreen = false;  // Do not clear the screen
    }
}

bool checkForWin(char player, bool& clearScreen) {
    // Check for three in a row horizontally
    for (int i = 0; i < ROWS; i++) {
        if (board[i][0] == player && board[i][1] == player && board[i][2] == player) {
            clearScreen = false;  // Do not clear the screen
            return true;
        }
    }

    // Check for three in a row vertically
    for (int j = 0; j < COLS; j++) {
        if (board[0][j] == player && board[1][j] == player && board[2][j] == player) {
            clearScreen = false;  // Do not clear the screen
            return true;
        }
    }

    // Check for three in a row diagonally
    if (board[0][0] == player && board[1][1] == player && board[2][2] == player) {
        clearScreen = false;  // Do not clear the screen
        return true;
    }
    if (board[0][2] == player && board[1][1] == player && board[2][0] == player) {
        clearScreen = false;  // Do not clear the screen
        return true;
    }

    // If none of the above conditions are met, return false
    return false;
}

bool checkForDraw(bool& clearScreen) {
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
    clearScreen = false;  // Do not clear the screen
    return true;
}


int main() {
    bool gameOver = false;
    char player = 'X';  // Start with X
    bool gameWon = false;  // Flag to track whether the game has been won
    bool gameDrawn = false;  // Flag to track whether the game has been declared a draw
    while (!gameOver) {
        bool clearScreen = true;  // Flag to determine whether to clear the screen

        // Display the game board
        std::cout << "  0 1 2" << std::endl;
        for (int i = 0; i < ROWS; i++) {
            std::cout << i << " ";
            for (int j = 0; j < COLS; j++) {
                std::cout << board[i][j] << " ";
            }
            std::cout << std::endl;
        }

        // Prompt the player for their move
        std::cout << "Player " << player << ", enter your move (row column): ";
        int row, col;
        std::cin >> row >> col;

        // Check if the row and column values are within the valid range
        if (row < 0 || row >= ROWS || col < 0 || col >= COLS) {
            std::cout << "Invalid move. Please try again." << std::endl;
            clearScreen = false;  // Do not clear the screen
        }
        else {
            // Update the game board with the player's move
            updateBoard(row, col, player, clearScreen);

            // Check if the player has won
            gameWon = checkForWin(player, clearScreen);
            if (gameWon) {
                std::cout << "Player " << player << " wins!" << std::endl;
                gameOver = true;  // End the game
            }

            // Check if the game has ended in a draw
            gameDrawn = checkForDraw(clearScreen);
            if (gameDrawn) {
                gameOver = true;  // End the game
            }
        }

        // Clear the screen if necessary
        if (clearScreen) {
            // Clear the screen
            system("cls");
        }

        // Switch to the other player
        if (player == 'X') {
            player = 'O';
        }
        else {
            player = 'X';
        }
    }

    // Display the final game board
    std::cout << "  0 1 2" << std::endl;
    for (int i = 0; i < ROWS; i++) {
        std::cout << i << " ";
        for (int j = 0; j < COLS; j++) {
            std::cout << board[i][j] << " ";
        }
        std::cout << std::endl;
    }

    return 0;
}
