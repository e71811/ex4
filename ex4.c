/******************
Name:ilay hefgot
ID:212398648
Assignment:ex4
*******************/
#include <stdio.h>
#include <string.h>
#define pyramidSize 5
#define pyramidForLoop 15
#define pyramidHeight 5
#define boardSize 20
#define maximalGrid 30
#define maximalSlots 100
#define maximalWords 100
#define maximalLength 15
// this is a struct i used in the crossword mission
typedef struct {
    int row;        // represents index for the row
    int col;        // represents index for the colum
    int length;     // the length we got from the user for the specific word
    char direction; // horizontal or vertical
} Slot;


int  robotMaze(int x,int y);
float calculatePyramid(float pyramid[pyramidSize][pyramidSize],int i,int j);
int parenthesesValid(char left_parenthesis);
int isRight(char c);
char matchLeft(char right);
int queenClash(int size,char board[size][size],int infoArray[size],int position,int goDown);
int check( int infoArray[boardSize],int goDown,int position,int index,char board[boardSize][boardSize]) ;
void markTheBoard(int size, int infoArray[size], int i, int j);
int makeTheBoard(char board[maximalSlots][maximalLength], int row, int col);
int charValid(char board[maximalSlots][maximalLength], int row, int col, char c);
int wordValid(Slot slot, char word[], char board[maximalSlots][maximalLength], int position) ;
void placeWord(Slot slot, char word[], char board[maximalSlots][maximalLength], int position);
void removeWord(Slot slot, int length, char board[maximalSlots][maximalLength], int position) ;
int solveCrossword(Slot slots[], char dictionary[maximalLength][maximalLength],
int numberOfWords, char board[maximalSlots][maximalLength],
int currentSlot, int currentWord, int numOfSlots,int usedWords[maximalLength]);
int main()
{
    int task = -1;
    do
    {
        printf("Choose an option:\n"
               "1. Robot Paths\n"
               "2. The Human Pyramid\n"
               "3. Parenthesis Validation\n"
               "4. Queens Battle\n"
               "5. Crossword Generator\n"
               "6. Exit\n");

        if (scanf("%d", &task))
        {
            switch (task)
            {
            case 6:
                {
                    printf("Goodbye!\n");
                    break;
                }

            case 1:
                {
                    int y = 0;
                    int x = 0;
                    printf("Please enter the coordinates of the robot (column, row):\n");
                    scanf("%d%d",&x,&y);
                    printf("The total number of paths the robot can take to reach home is: %d\n",
                        robotMaze(x,y));
                    break;
                }

            case 2:
                {
                    float pyramid[pyramidHeight][pyramidHeight]={0};
                    int checker=1;
                    printf("Please enter the weights of the cheerleaders:\n");
                    for (int i = 0; i <  pyramidHeight ; i++) {
                        for (int j = 0; j <= i; j++) {
                            scanf("%f", &pyramid[i][j]);
                            if (pyramid[i][j] <= 0) {
                                printf("Negative weights are not supported.\n");
                                checker=0;
                                break;
                            }
                        }

                        if (checker==0) {
                            break;
                        }
                    }
                    if (checker) {
                        printf("The total weight on each cheerleader is:\n");
                        for(int i=0;i<pyramidHeight;i++) {
                            for(int j=0;j<=i;j++) {
                                printf("%.2f ",calculatePyramid(pyramid,i,j));
                            }
                            printf("\n");
                        }
                    }
                    break;
                }

            case 3:
                {
                    printf("Please enter a term for validation:\n");
                    //clean buffer if its not [{(< chars
                    scanf("%*[^][(){}<>]");
                    if (parenthesesValid('\0')==1) {
                        printf("The parentheses are balanced correctly.\n");
                    }else{
                        printf("The parentheses are not balanced correctly.\n");
                    }
                    break;
                }

            case 4:
                {
                    int goDown=0;
                    int size = 0;
                    int position =0;
                    printf("Please enter the board dimensions:\n");
                    scanf("%d",&size);
                    // this array will hold the data for the queens
                    int infoArray[boardSize];
                    char board[boardSize][boardSize]={0};
                    printf("Please enter a %d*%d puzzle board:\n",size,size);
                    for (int j=0;j<size;j++)
                    {
                           scanf("%s",board[j]);
                    }

                   if(queenClash(size,board,infoArray,position,goDown)==1)
                   {
                       printf("Solution:\n");
                     markTheBoard(size,infoArray,0,0);
                   } else {
                       printf("This puzzle cannot be solved.\n");
                   }


                    break;

                }
            case 5: {
                    char board[maximalSlots][maximalLength];
                    Slot slots[maximalSlots];
                    int numOfSlots;
                    int numberOfWords;
                    char dictionary[maximalLength][maximalLength];
                    int usedWords[maximalLength] = {0};
                    int gridSize;
                    makeTheBoard(board, 0, 0);
                    printf("Please enter the dimensions of the crossword grid:\n");
                    scanf("%d", &gridSize);
                    printf("Please enter the number of slots in the crossword:\n");
                    scanf("%d", &numOfSlots);
                    printf("Please enter the details for each slot (Row, Column, Length, Direction):\n");
                    for (int i = 0; i < numOfSlots; i++) {
                        scanf("%d %d %d %c", &slots[i].row, &slots[i].col,
                              &slots[i].length, &slots[i].direction);
                    }
                    printf("Please enter the number of words in the dictionary:\n");
                    scanf("%d", &numberOfWords);
                   //check if the user gave a dictionary with less word then number of slots
                    if (numberOfWords < numOfSlots) {
                        printf("The dictionary must contain at least %d words. "
                               "Please enter a valid dictionary size:\n", numOfSlots);
                        scanf("%d", &numberOfWords);
                    }
                    //insert the words to the dictionary
                    printf("Please enter the words for the dictionary:\n");
                    for (int i = 0; i < numberOfWords; i++) {
                        scanf("%s", dictionary[i]);
                    }
                    //check if it can be solved
                    if (solveCrossword(slots, dictionary, numberOfWords, board,
                        0, 0, numOfSlots,usedWords)) {
                        for (int i = 0; i < gridSize; i++) {
                            for (int j = 0; j < gridSize; j++) {
                                printf("| %c ", board[i][j]);
                            }
                            printf("|\n");
                        }
                    } else {
                        printf("This crossword cannot be solved.\n");
                    }
                break;
                }

            default:
                {
                    printf("Please choose a task number from the list.\n");
                    break;
                }
            }
        }
        else
        {
            scanf("%*s");
        }

    } while (task != 6);
}

int robotMaze(int x, int y)
{
    int sumWays = 0;
    if (y<0||x<0)
    {
        return 0;
    }
    if(x==0&&y==0)
    {
        return 1;
    }
    sumWays=sumWays+robotMaze(x-1,y)+robotMaze(x,y-1);
    return sumWays;
}
float calculatePyramid(float pyramid[pyramidSize][pyramidSize],int i,int j)
{
    //we arrived to the top of the pyramid so i return her weight
    if (i==0) {
        return pyramid[i][j];
    }
    float leftWeight = 0, rightWeight = 0;
    //here i calculate all the added weight on the left shoulder
    if (j > 0) {
        leftWeight = 0.5 * calculatePyramid(pyramid, i -1, j - 1);
    }
    //here i calculate all the added weight on the left shoulder
    if (j < i) {
        rightWeight = 0.5 * calculatePyramid(pyramid, i-1, j);
    }
    //here i calculate all the weight on the specific cheerleader
    return  leftWeight + rightWeight+pyramid[i][j];

}
int parenthesesValid(char left_parenthesis) {
    char character;
    //ignore all characters that are not parentheses
    scanf("%*[^][(){}<>\n]");
    //read the next character
    scanf("%c", &character);
    //here i check if the user ended inserting data
    if (character == '\n') {
        //this checks if no unmatched parenthesis are left
        if (left_parenthesis == '\0')
            return 1;
        else {
            //ignore all the characters until the new line if there's no unmatched parenthesis are left
            scanf("%*[^\n]");
            return 0;
        }
    }
       //i check if the char is matching to the left parenthesis and also if its the right type
    if (left_parenthesis == matchLeft(character) && isRight(character))
        return 1;
    // if i found that a specifc character dont match return false
    if (isRight(character)) {
        scanf("%*[^\n]");
        return 0;
    }
    //call again the function to check the next charcters compared to the remaining input
    return parenthesesValid (character) && parenthesesValid(left_parenthesis);
}
int isRight(char c) {
    // this check if the char is equal to one of the parentheses
    return (c == ')' || c == '}' || c == ']' || c == '>');
}
char matchLeft(char right) {
    //i check if the  character is a closing parenthesis
    switch (right) {
    case ')':
        return '(';
    case '}':
        return '{';
    case ']':
        return '[';
    case '>':
        return '<';
    default:
        return '\0';
    }
}
int queenClash(int size,char board[size][size],int infoArray[size],int position,int goDown)
{
    //if we checked all the queens first colum and none of them is valid it means the board isn't valid
   if (goDown==size&&position ==0)
   {
       return 0;
   }// if i went through all the queens in all the columns it means i found a valid board
    if(position==size)
    {
        return 1;
    }//we checked the column and didn't find a fitting queen so we need to backtrack
     if(goDown==size)
     {
         infoArray[position]=-1;

         return queenClash(size,board,infoArray,position-1,infoArray[position-1]+1);
     }else
     {
         infoArray[position]=goDown;
         if (check(infoArray,goDown,position,0,board))
             {
             return queenClash(size,board,infoArray,position+1,0);

             }else {
                 return queenClash(size, board, infoArray, position, goDown+1);
             }
     }
}
void markTheBoard(int size, int infoArray[size], int i, int j)
{
    if(i<size)
    {
        if(j<size)
        {
            //if we arrived to coordinates i saved as a queen printf "X"
            if (infoArray[i] ==j) {
                printf("X");
            }else {
                printf("*");
            }
            printf(" ");
            markTheBoard(size,infoArray,i,j+1);
        }//if we arrived to the last queen in the row go to the next row
        else
        {
            printf("\n");
            i++;
            markTheBoard(size,infoArray,i,0);
        }

    }else
    {
        printf("\n");
    }

}
int check( int infoArray[boardSize],int goDown,int position,int index,char board[boardSize][boardSize]) {
    //if the function checked all the queens in the infoArray return 1
    if (index==position) {
        return 1;
    }
    //i check if any of the queen in info array is in the same row as the queen i want to check
    if(infoArray[index]==goDown){
        return 0;
    }
    // here i check if any of the queen in info array are similar type to the queen i want to check
    if (board[index][infoArray[index]]==board[position][goDown]) {
        return 0;
    }//if we are not in the first colum
    if(position!=0)
    {
        //check if the queen is threatened diagonally
        if (infoArray[position-1]==infoArray[position]-1 || infoArray[position-1]==infoArray[position]+1) {
            return 0;
        }
    }

    //do the same check but for the next queen in the info array
    return check(infoArray,goDown,position,index+1,board);

}
int makeTheBoard(char board[maximalSlots][maximalLength], int row, int col) {
    //first i make the board in all places ='#'
    if (row >= maximalSlots)
    {
        return 1;
    }
    if (col >= maximalLength) {
        return makeTheBoard(board, row + 1, 0);
    }
    board[row][col] = '#';
    return makeTheBoard(board, row, col + 1);
}
void placeWord(Slot slot, char word[], char board[maximalSlots][maximalLength], int pos) {
    if (pos >= (int)strlen(word)) return;
    //place the word in the slot according to its direction
    if (slot.direction == 'H') {
        board[slot.row][slot.col + pos] = word[pos];
    } else {
        board[slot.row + pos][slot.col] = word[pos];
    }

    placeWord(slot, word, board, pos + 1);
}
void removeWord(Slot slot, int length, char board[maximalSlots][maximalLength], int pos) {
    if (pos >= length) return;
    //remove the word according to it direction
    if (slot.direction == 'H') {
        board[slot.row][slot.col + pos] = '#';
    } else {
        board[slot.row + pos][slot.col] = '#';
    }

    removeWord(slot, length, board, pos + 1);
}
int charValid(char board[maximalSlots][maximalLength], int row, int col, char c) {
    //we check if we can place the char
    if (board[row][col] == '#') return 1;
    if(board[row][col] == c) {
        return 1;
    }
    return 0;
}
int solveCrossword(Slot slots[], char dictionary[maximalLength][maximalLength],
                   int numberOfWords, char board[maximalSlots][maximalLength],
                   int currentSlot, int currentWord, int numOfSlots,int usedWords[maximalLength]) {
    // if the function passed over all the slots it means we found a solution
    if (currentSlot >= numOfSlots) {
        return 1;
    }

    // if the first slot didnt got any solution it means we didnt foind solution at all
    if (currentSlot == -1 || (currentWord >= numberOfWords && currentSlot == 0)) {
        return 0;
    }

    // if we check all the word we return to the previous slot
    if (currentWord >= numberOfWords) {
        return solveCrossword(slots, dictionary, numberOfWords, board,
                            currentSlot - 1, 0, numOfSlots, usedWords);
    }

    // if the word was used or the size wont fit move to the next word
    if (usedWords[currentWord] || (int)strlen(dictionary[currentWord]) != slots[currentSlot].length) {
        return solveCrossword(slots, dictionary, numberOfWords, board,
                            currentSlot, currentWord + 1, numOfSlots,usedWords);
    }

    // check if the word match and we can put it
    if (wordValid(slots[currentSlot], dictionary[currentWord], board, 0)) {
        // replace the word
        placeWord(slots[currentSlot], dictionary[currentWord], board, 0);
        usedWords[currentWord] = 1;

        // try to fit in the next slot
        if (solveCrossword(slots, dictionary, numberOfWords, board,
                          currentSlot + 1, 0, numOfSlots,usedWords)) {
            return 1;
                          }

        // if none of the word fit remove the word and check the next one
        removeWord(slots[currentSlot], slots[currentSlot].length, board, 0);
        usedWords[currentWord] = 0;
    }

    // check the next word
    return solveCrossword(slots, dictionary, numberOfWords, board,
                         currentSlot, currentWord + 1, numOfSlots,usedWords);
}

int wordValid(Slot slot, char word[], char board[maximalSlots][maximalLength], int position) {
    // if we checked all the characters and we didnt return 0 it means the word i valid
    if (position >=(int) strlen(word))
    {
        return 1;
    }

    int row, col;

    if (slot.direction == 'H') {
        row = slot.row;          // if horizontal the row remains the same
        col = slot.col + position;    // if horizontal the column + position
    } else { // Assuming 'C' represents vertical direction
        row = slot.row + position;    // if vertical the row + position
        col = slot.col;         // if vertical the column remains the same
    }
    //  checks is the char is valid
    if (!charValid(board, row, col, word[position])) {
        return 0;
    }
    //check the next character in this word
    return wordValid(slot, word, board, position + 1);
}