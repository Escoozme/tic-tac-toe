#include <iostream>
#include <limits>

//rows = 1, 4, 7
//columns = 1, 5, 9

//Checks to see if a square is taken by an X or O
bool squareTaken(int playaMove, bool reset) {
    static int squaresArray[10] = { 0 };

    if(reset) {
        for(int i = 0; i <= 9; ++i) {
            squaresArray[i] = 0;
        }
        return false;
    }

    if(squaresArray[playaMove] == 0) {
        squaresArray[playaMove] = 1;
        return false;
    }
    else {
        return true;
    }
}

//Creates TicTacToe Table
char& initTable(char tttTableArray[][11]) {
    for(int r = 0; r < 9; ++r) {
        for(int c = 0; c < 11; ++c) {
            if(c == 3 || c == 7) {
                tttTableArray[r][c] = '|';
            }
            else if(r == 2 || r == 5) {
                tttTableArray[r][c] = '_';
            }
            else {
                tttTableArray[r][c] = ' ';
            }
        }
    }
}

int main() {
    char tttTableArray[9][11];

    initTable(tttTableArray);

    //Instructions
    std::cout << "1 = top left, 4 = middle left, 9 = bottom right, etc.\n\n";

    //All the things are in this loop
    do {
        int playerMove = 0;
        char playerSymbol;
        static int counter = 1;
        bool shitIsWrong = false;
        bool gameOver = false;

        //Draws updated TicTacToe table with most recent player input
        std::cout << std::endl;
        for(int r = 0; r < 9; ++r) {
            for(int c = 0; c < 11; ++c) {
                std::cout << tttTableArray[r][c];
            }
            std::cout << std::endl;
        }

        //Checks for possible winning strings
        if(counter > 5) {
            const std::string ONE_STRING = "XXX", TWO_STRING = "OOO";
            std::string playerWins1 = "", playerWins2 = "", playerWins3 = "", playerWins4 = "";

            for(int r1 = 1, c2 = 1; r1 <= 7, c2 <= 9; r1 += 3, c2 += 4) {
                for(int c1 = 1, r2 = 1; c1 <= 9, r2 <= 7; c1 += 4, r2 += 3) {
                    playerWins1 += tttTableArray[r1][c1];
                    playerWins2 += tttTableArray[r2][c2];
                }

                for(int r3 = 1, c3 = 1; r3 <= 7, c3 <= 9; r3 += 3, c3 += 4) {
                    playerWins3 += tttTableArray[r3][c3];
                }
                for(int r4 = 1, c4 = 9; r4 <= 7, c4 >= 1; r4 += 3, c4 -= 4) {
                    playerWins4 += tttTableArray[r4][c4];
                }

                //Declares winner, redraws table, resets squareTaken boolean function
                //resets counter to 1 which is used to determine player turn
                if(playerWins1 == ONE_STRING || playerWins2 == ONE_STRING || playerWins3 == ONE_STRING || playerWins4 == ONE_STRING) {
                    std::cout << "\n\nPlayer 1 Wins!\n\n";
                    initTable(tttTableArray);
                    squareTaken(0, 1);
                    counter = 1;
                    gameOver = true;
                }
                else if(playerWins1 == TWO_STRING || playerWins2 == TWO_STRING || playerWins3 == TWO_STRING || playerWins4 == TWO_STRING) {
                    std::cout << "\n\nPlayer 2 Wins!\n\n";
                    initTable(tttTableArray);
                    squareTaken(0, 1);
                    counter = 1;
                    gameOver = true;
                }
                //If tie
                if(counter == 10 && r1 == 7 && !gameOver) {
                    std::cout << "\n\nTIE GAME HOLY SHIT!!!\n\n";
                    initTable(tttTableArray);
                    squareTaken(0, 1);
                    counter = 1;
                    gameOver = true;
                }

                //Asks if players want to play again
                if(gameOver) {
                    char playAgain;

                    std::cout << "\nPlay again? (Y/N): ";

                    do {
                        std::cin >> playAgain;
                    }
                    while(playAgain != 'Y' && playAgain != 'N' && playAgain != 'y' && playAgain != 'n');

                    if(playAgain == 'Y' || playAgain == 'y') {
                        playAgain = ' ';
                        gameOver = false;
                        break;
                    }
                    else {
                        return 0;
                    }
                }

                //Resets winner determiners
                playerWins1 = "";
                playerWins2 = "";
                playerWins3 = "";
                playerWins4 = "";
            }
        }

        //Gets input from players and updates TicTacToe table
        do {
            bool valid_input = false;
            //Result of counter % 2 = 1 > Player 1's turn
            //                      = 0 > Player 2's turn
            do {
                if(counter % 2 == 1) {
                    std::cout << "\nPlayer 1 Input: ";
                    std::cin >> playerMove;
                    playerSymbol = 'X';
                }
                else {
                    std::cout << "\nPlayer 2 Input: ";
                    std::cin >> playerMove;
                    playerSymbol = 'O';
                }

                if(!(valid_input = std::cin.good())) {
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                }
            } while(!valid_input);


            if(playerMove >= 1 && playerMove <= 9 && !squareTaken(playerMove, 0)) {
                shitIsWrong = false;

                switch(playerMove) {
                case 1: tttTableArray[1][1] = playerSymbol;
                    break;
                case 2: tttTableArray[1][5] = playerSymbol;
                    break;
                case 3: tttTableArray[1][9] = playerSymbol;
                    break;
                case 4: tttTableArray[4][1] = playerSymbol;
                    break;
                case 5: tttTableArray[4][5] = playerSymbol;
                    break;
                case 6: tttTableArray[4][9] = playerSymbol;
                    break;
                case 7: tttTableArray[7][1] = playerSymbol;
                    break;
                case 8: tttTableArray[7][5] = playerSymbol;
                    break;
                case 9: tttTableArray[7][9] = playerSymbol;
                }
            }
            else {
                shitIsWrong = true;
            }

        } while(shitIsWrong);

        ++counter;

    } while(true);

    return 0;
}
