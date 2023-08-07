#include <stdio.h>
#include <string.h>

#define MAX_SIZE 300
#define MAX_BOARD 5
#define ONE 1
#define MAX_PARTICIPANTS 10
#define MAX_LETTERS 21

/***********************
* Name:ofir  rothchild
* ID: 207434960
* Assignment:4
***********************/

int main ();
void startGame (char* ,char [][MAX_BOARD], int , char, char* , char*);
void ParticipantsNames (char*, char* , char* );
void removeSpaces (char [][MAX_LETTERS]);
void boardDesign(char [][MAX_BOARD], int );
void restartBoard (char [][MAX_BOARD], int , char );
void printBoard(char [][MAX_BOARD], int);
void lexicographicalOrder(char [][MAX_LETTERS], int );
void printNames (char [][MAX_LETTERS],int );
void printPlayers (char [][MAX_LETTERS], char* , char* );
void changeSign(char [][MAX_BOARD] ,int,  int*, int* ,char*, char);
int locationIntegrity(char boardArr[][MAX_BOARD], int* , int*);
int theWinner(char [][MAX_BOARD], int ,int* , int* , char);
int tie(char boardArr[][MAX_BOARD],int, int* , int* , char);
int isRow (char boardArr[][MAX_BOARD], int, int*, char);
int isColumn (char boardArr[][MAX_BOARD],int ,int*, char);
int isMd (char boardArr[][MAX_BOARD],int, char);
int isSd (char boardArr[][MAX_BOARD],int, char);
void processGame(char [][MAX_BOARD],int  , char* , char* );



/******************
*Function Name: startGame
* Input: an array of strings, 2D array that describes the places on the game board,
 int of size  rows board and size columns board (valid values 1 <= size <= 5)
* Output: none
* Function Operation:The function is intended to include the beginning of the game for example,
 printing the players, organizing in lexicographic order and printing the appropriate board
 ******************/

void startGame (char s [MAX_SIZE],char boardArr[][MAX_BOARD],int sizeRowColumn ,char sign ,char name1[],char name2[]){
    // A call to a function that prints the participants and arranges the names in lexicographic order

    ParticipantsNames (s, name1, name2);
    // Printing the numbered board

    boardDesign (boardArr,sizeRowColumn);
    printf("\nlet start the game!\n-\t-\t-\t-\n");
    // printing the board in the start of the game

    restartBoard(boardArr, sizeRowColumn, sign);
    // Call to a function that prints the board in its updated state

    printBoard(boardArr, sizeRowColumn);
}

/******************
*Function Name:ParticipantsNames
* Input: an array of strings, array, array
* Output: none
* Function Operation: The function organizes the order of printing the names, and a lexicographic arrangement
 ******************/

void ParticipantsNames (char s[], char name1[], char name2[]) {
    int numElementInArray = 0;
    //Definition of a 2D new array for the names of the participants

    char participants[MAX_PARTICIPANTS][MAX_LETTERS] = { 0 };
    //A pointer designed to separate the commas from the array of participants' names

    const char *comma = ",";
    char *pointerOfParticipants;
    //This function separates the commas from the names of the participants

    pointerOfParticipants = strtok(s, comma);
    while (pointerOfParticipants != NULL) {
        //Filling of the participants names array using the strcpy function designed to copy content between strings

        strcpy(participants[numElementInArray], pointerOfParticipants);
        pointerOfParticipants = strtok(NULL, comma);
        numElementInArray++;
    }
    //calling to function to get rid of excess spaces between names of participants
    removeSpaces(participants);
    //Calling a function that orders the order of participants in lexicographic order

    lexicographicalOrder (participants, numElementInArray);
    //A call to a function that prints the game participants according to their numbering

    printNames(participants,numElementInArray);
    //A function that prints the strings of the selected partners as the first and second player

    printPlayers(participants, name1, name2);
}
/******************
*Function Name:removeSpaces
* Input: 2D array
* Output:none
* Function Operation:The function is designed to remove excess spaces
 in case the names the user enters will be "padded" with spaces
 ******************/

void removeSpaces (char participants[][MAX_LETTERS]){
    //Variables to define the beginning and end of the name

    int start=0, end=0;
    //The first loop starts from the first place in the array and checks if there is unnecessary space

    for (int i = 0; i < MAX_PARTICIPANTS; i++) {
        char auxName[MAX_LETTERS] = { 0 };
        start =0;
        //If there is indeed an unnecessary space, the loop will stop and "skip" the space

        while (participants[i][start] == ' ')
            start++;

        //Definition of the end of the set of names
        end= MAX_LETTERS-2;

        //This loop ran from the last place in the array and checks if there is unnecessary space,
        // in such a situation will "skip" the space

        while (participants[i][end] == ' ' || participants[i][end] == '\0')
            end--;
        for (int j = start; j <= end ; j++)
            auxName[j-start] = participants[i][j];

//we will copy the current array, from the temporary array so that the new array is updated without unnecessary spaces

        strcpy(participants[i],auxName);
        }
    }

/******************
*Function Name:lexicographicalOrder
* Input: 2D array, int
* Output:none
* Function Operation:The function sorts the names of the players in lexicographic order
* by using strcmp which compares strings by the value of the letters in the ascii table
******************/

void lexicographicalOrder(char participants[][MAX_LETTERS], int numElementInArray){
    char tempArray[MAX_LETTERS]={0};
    //program to sort elements in lexicographical order

        for (int row = 0; row <= numElementInArray; row++) {
            for (int column = row + 1; column < numElementInArray; column++) {

                /* Each character of the string is compared with all others strings using strcmp function
                 * The function returns a positive value when the second string is smaller than the first string
                 */

                if (strcmp(participants[row], participants[column]) > 0) {

                    /* In this case, the second string is replaced or swap with the first string
                     * To swap these strings we use 'str copy' function
                     */

                    strcpy(tempArray, participants[row]);
                    strcpy(participants[row], participants[column]);
                    strcpy(participants[column], tempArray);
                    strcpy(tempArray, "");
                }
            }
        }
}
/******************
*Function Name:printNames
* Input:2D array, int
* Output:none
* Function Operation:The function prints the names of the players after sorting the lexicographic order
 ******************/

void printNames (char participants[][MAX_LETTERS], int numElementInArray){
    /*
    This loop used to print the names stored in the array in the correct order
    num is the number corresponding to the location of the name in the array
    that we need to print it Next to the appropriate player name (num+1)
     */
        for (int num = 0; num < numElementInArray; num++) {
            printf("%d.\t%s\n", num+1, participants[num]);
        }
}
/******************
*Function Name:printPlayers
* Input:2D array, array1, array2
* Output:none
* Function Operation:The function prints the names of the players selected by the user to play in the upcoming game
 ******************/

void printPlayers (char participants[][MAX_LETTERS], char name1[], char name2[]){
    int firstPlayer=0, secondPlayer=0;
    // The user enters the two players he has selected

    scanf("%d%*c%d", &firstPlayer, &secondPlayer);
    //Copy the names of the first and second participants into new strings

    strcpy(name1 ,participants[firstPlayer-1]);
    strcpy(name2 ,participants[secondPlayer-1]);
    printf("Hi %s and %s,\n"
           "This cell numbered:\n", name1, name2);

}
/******************
*Function Name:boardDesign
* Input:2D array, int
* Output:none
* Function Operation:The function shapes the board and prints it numbered as the board size
 as required at the beginning of the game
 ******************/

void boardDesign(char boardArr[][MAX_BOARD], int sizeRowColumn) {
    // countNumber Used for numbering the board from the number 1 to the size of the board, double-column rows
    // lastElement- is the last element in row and in column

    int countNumber = 1, lastElement = sizeRowColumn - ONE;
    for (int i = 0; i < sizeRowColumn; i++) {
        //locationInArray Indicates the location of the elements in the array to printing the board

            for (int locationInArray = 0; locationInArray < sizeRowColumn; locationInArray++) {

                //This condition is intended to print a 1X1 board

                if (sizeRowColumn == 1)
                {
                    printf("   1   |\n-----+\n");
                    return;
                }
                // When locationInArray is the last number in the row we are in the array

                if (locationInArray == lastElement) {
                    printf("   %d", countNumber);
                }
                    //When locationInArray is not the last number in the row we are in the array

                else {
                    printf("   %d   |", countNumber);
                }
                countNumber++;
            }
            printf("\n");
            //As long as we have not reached the last position in a row or column

            if (i < lastElement) {
                //We will need to print the spaces between the lines of the board as requested

                for (int k = 0; k < sizeRowColumn; ++k) {
                    if (k == lastElement) {
                        printf("-----");
                    } else {
                        printf("-----+");
                    }
                }
                printf("\n");
            }
        }
    }

/******************
*Function Name:restartBoard
* Input:2D array, int, char
* Output:none
* Function Operation:The function initializes the game board with the _ mark
 that is required to appear at the beginning of the game when the board is empty
 ******************/

void restartBoard (char boardArr[][MAX_BOARD], int sizeRowColumn, char sign) {
    //row and column Indicates the location of the current place in the array
    for (int row = 0; row < sizeRowColumn; row++) {
        for (int column = 0; column < sizeRowColumn; column++) {
            // Placement of the corresponding mark in all places on the board
            boardArr[row][column] = sign;
        }
    }
}
/******************
*Function Name: printBoard
* Input: 2D array, int
* Output:none
* Function Operation:The function prints the board according to the values that are in the array
 at that moment in the game
 ******************/

void printBoard(char boardArr[][MAX_BOARD], int sizeRowColumn) {
    int lastElement = sizeRowColumn - ONE;
    for (int row = 0; row < sizeRowColumn; row++) {

        for (int column = 0; column < sizeRowColumn; column++) {
            //This condition is intended to print a 1X1 board

            if (sizeRowColumn == 1)
            {
                printf("   %c   |\n-----+\n", boardArr[row][column]);
                return;
            }
            // Where column is the last number in the row we are in the array
            if (column == lastElement) {
                printf("   %c", boardArr[row][column]);
            }
                //Where column is not the last number in the row we are in the array
            else {
                printf("   %c   |",  boardArr[row][column]);
            }
        }

        printf("\n");
        if (row< lastElement){
            for (int k = 0; k < sizeRowColumn; ++k) {
                if (k == lastElement) {
                    printf("-----");
                } else {
                    printf("-----+");
                }
            }
        }
        printf("\n");
    }
}
/******************
*Function Name:processGame
* Input:2D array, int, array1, array2
* Output:none
* Function Operation:The function includes the entire course of the game,
 the part from inserting the corresponding mark to the place that the user has chosen
 to calling the function that determines victory or tie
 ******************/

void processGame(char boardArr[][MAX_BOARD],int sizeRowColumn, char name1[], char name2[]) {
    int turns1, turns2, row, column;
    // the valid sign in the game While X is associated with the first player and O with the second player

    char sign1 = 'X', sign2 = 'O', name[MAX_LETTERS];
    //A calculation to determine the number of turns of each player according to the size of the board selected

    turns2 = (sizeRowColumn * sizeRowColumn) / 2;
    turns1 = (sizeRowColumn * sizeRowColumn) - turns2;
    //The loop ran as long as there was still a turn to perform for one of the players

    for (int i = 0; i < turns1; ++i) {

        if (i < turns1) {
            //turn of player 1
            //A call to a function that inserts the mark of player 1 depending on the position on the board he chooses
            changeSign(boardArr, sizeRowColumn, &row, &column, name1, sign1);
            printBoard(boardArr, sizeRowColumn);
        }

        //The condition is intended to limit the victory test according to the minimum number of turns
        // that will allow the victory of one of the players

        if (i >= sizeRowColumn - 1) {
            //Calling to a function that tests a player's 1 victory

            if (theWinner(boardArr, sizeRowColumn, &row, &column, sign1) == 1) {
                printf("%s has win! You played well!", name1);
                break;
            }
        }

        if (i < turns2) {
            //turn of player 1
            //A call to a function that inserts the mark of player 2 depending on the position on the board he chooses
            changeSign(boardArr, sizeRowColumn, &row, &column, name2, sign2);
            printBoard(boardArr, sizeRowColumn);
        }
        //The condition is intended to limit the victory test according to the minimum number of turns
        // that will allow the victory of one of the players

        if (i >= sizeRowColumn - 1) {
            //Calling to a function that tests a player's 1 victory

            if (theWinner(boardArr, sizeRowColumn, &row, &column, sign2) == 1) {
                printf("%s has win! You played well!\n", name2);
                break;
            }
        }
    }
    //At the end of the game we will check if there is equality between the players by calling the function tie

    if (tie(boardArr, sizeRowColumn, &row, &column, sign1) == 3) {
        printf("The game end, No one wins. You played well\n");

    }
}
/******************
*Function Name:changeSign
* Input:2D array, int, int, int, array, char
* Output:none
* Function Operation:The function inserts the mark associated with the player (X \ O)
 depending on the position on the board he selected
 ******************/

void changeSign(char boardArr[][MAX_BOARD],int sizeRowColumn,int *row, int *column, char name[MAX_LETTERS], char sign) {
    int location = 0;
    //As long as the number entered by the user is incorrect for its insertion to the desired location
    //the loop will continue to run
    while (1) {
        // A print that indicates the beginning of the turn

        printf("It %s turn, you %c:\n", name, sign);
        scanf("%d", &location);

        //If the location entered by the user is larger than the size of the board

        if (location > (sizeRowColumn * sizeRowColumn)) {
            printf("This place not exist!\n");
            continue;
        }

        //If the location entered by the user is not valid

        if (location <= 0){
            printf("This place not exist!\n");
            continue;
        }
        //A calculation designed to convert the numeric location selected by the user
        // to the correct position on the board according to the relevant row and column

        location -= 1;
        int r = location / sizeRowColumn;
        int c = location % sizeRowColumn;
        *row = r;
        *column = c;

        //The condition calls for a function that checks whether the location the user entered is indeed empty

        if (locationIntegrity(boardArr, row, column) == 1) {
            continue;
        }
        //If the location entered by the user is correct and empty,
        // we will insert the appropriate mark for the desired position on the board

        if (locationIntegrity(boardArr, row, column) == 0){
            boardArr[*row][*column] = sign;
            break;
        }
    }
}
/******************
*Function Name:locationIntegrity
* Input:2D array
* Output:int
* Function Operation:the function checks whether the location the user entered is empty
 ******************/

int locationIntegrity(char boardArr[][MAX_BOARD],
                      int *row, int *column){
    //If a sign is already found in the location selected by the user,
    // we will print a message indicating that the location is not empty

    if (boardArr[*row][*column] == 'X' || boardArr[*row][*column] == 'O') {
        printf("This place not empty!\n");
        return 1;
    }
    //else, we return 0

    return 0;
}

/******************
*Function Name:isRow
* Input:2D array, int, int, char
* Output:int
* Function Operation:The function checks whether there is a continuous row of the same sign (X\O) of the player,
 * depending on the specific location he has chosen
 ******************/

int isRow (char boardArr[][MAX_BOARD],int sizeRowColumn, int *row, char sign){
    //count designed to count the number of relevant characters in a row

    int count=0;
    for (int j = 0; j < sizeRowColumn; ++j) {
       if (boardArr[*row][j] == sign){
           count++;
       }
    }

    //If there are indeed a number of symbols equal in row to the size of the line,
    // then the player wins and the function return 1

    if (count == sizeRowColumn){
        return 1;
    }
    //If there is no win, the function returns 0

    return 0;
}
/******************
*Function Name:isColumn
* Input:char, int, int, char
* Output:int
* Function Operation:The function checks whether there is a continuous column of the same sign (X\O) of the player,
 * depending on the specific location he has chosen
 ******************/

int isColumn (char boardArr[][MAX_BOARD],int sizeRowColumn,int *column, char sign) {
    //count designed to count the number of relevant characters in a column

    int count = 0;
    for (int i = 0; i < sizeRowColumn; ++i) {
        if (boardArr[i][*column] == sign) {
            count++;
        }
    }
    //If there are indeed a number of symbols equal in column to the size of the line,
    // then the player wins and the function return 1

    if (count == sizeRowColumn) {
        return 1;
    }
    //If there is no win, the function returns 0

    return 0;
}
/******************
*Function Name:isMd
* Input:char, int, char
* Output:int
* Function Operation:The function checks whether there is a continuous main diagonal
 of the same sign (X\O) of the player,depending on the specific location he has chosen
 ******************/

int isMd (char boardArr[][MAX_BOARD],int sizeRowColumn, char sign) {
    //In the loop we run on the consts positions of the main diagonal depending on the size of the board

    int i, j, count = 0;
    for (i = 0, j = 0; i < sizeRowColumn && j < sizeRowColumn; ++i, ++j) {
        if (boardArr[i][j] == sign )
        {
            count++;
        }
    }

    //If there are indeed a number of symbols equal in main diagonal to the size of the line,
    // then the player wins and the function return 1

    if (count == sizeRowColumn) {
        return 1;
    }
    //If there is no win, the function returns 0

    return 0;
}
/******************
*Function Name:isSd
* Input:char, int, char
* Output:
* Function Operation:The function checks whether there is a continuous main diagonal
 of the same sign (X\O) of the player,depending on the specific location he has chosen
 ******************/

int isSd (char boardArr[][MAX_BOARD],int sizeRowColumn, char sign){
    int i, j, count = 0;
    //In the loop we run on the fixed positions of the secondary diagonal depending on the size of the board

    for (i = sizeRowColumn-1, j = 0; i >= 0 && j < sizeRowColumn; --i, ++j) {
        if (boardArr[i][j] == sign) {
            count++;
        }
    }

    //If there are indeed a number of symbols equal in secondary diagonal to the size of the line,
    // then the player wins and the function return 1

    if (count == sizeRowColumn) {
        return 1;
    }
    //If there is no win, the function returns 0

    return 0;
}
/******************
*Function Name:theWinner
* Input:char, int, int, int, chaar
* Output:int
* Function Operation:The function summarizes all the possibilities for winning the game
that are listed in the various functions and determines in total which participant won and if there is a victory at all
 ******************/

int theWinner(char boardArr[][MAX_BOARD],int sizeRowColumn,int *row, int *column, char sign){
                //Conditions for determining victory if one of the option to victory is true

                if (isRow(boardArr,sizeRowColumn, row,sign) == ONE ||
                isColumn(boardArr,sizeRowColumn,column, sign) == ONE ||
                isMd(boardArr,sizeRowColumn,sign) == ONE ||
                isSd(boardArr,sizeRowColumn,sign) == ONE)
                {
                    //If there is  wining, the function returns 1

                    return 1;
                }
    //If there is no win, the function returns 0

    return 0;
}
/******************
*Function Name:tie
* Input:char, int, int, int, char
* Output:int
* Function Operation:The function summarizes all the possibilities for winning the game
that are listed in the various functions and determines in total,
if there was no victory in any of the functions, the game ended in a draw
 ******************/

int tie(char boardArr[][MAX_BOARD],int sizeRowColumn,int *row, int *column, char sign){
    //Conditions for determining equality between the players

    if ( (isRow(boardArr,sizeRowColumn, row,sign) == 0 &&
          isColumn(boardArr,sizeRowColumn,column, sign) == 0 &&
          isMd(boardArr,sizeRowColumn,sign) == 0 &&
          isSd(boardArr,sizeRowColumn,sign) == 0))
    {

        //If there is tie in all the function

        return 3;

        //If there is no tie, the function returns 0

    }
    return 0;
}


int main() {
    int sizeRow=0, sizeColumn=0, sizeRowColumn;
    char name1 [MAX_LETTERS] = {0};
    char name2 [MAX_LETTERS] = {0};
    char s [MAX_SIZE] = {0} , boardArr[MAX_BOARD][MAX_BOARD] = {0}, sign='_', coma = {0};
    printf("Enter size of the game and the participants names:\n");
    scanf(" %d%*c%d%c", &sizeRow, &sizeColumn, &coma);
    scanf("%[^\n\r]s", s);
    printf("Your board size is %dx%d!\n", sizeRow, sizeColumn);
    printf("Choose 2 participants:\n");
    sizeRowColumn=sizeRow=sizeColumn;
    startGame(s, boardArr, sizeRowColumn, sign, name1, name2);
    processGame(boardArr, sizeRowColumn, name1, name2);
    return 0;
}