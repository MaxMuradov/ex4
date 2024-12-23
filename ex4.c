/******************
Name: Maxim Muradov
ID: 346975386
Assignment: ex4
*******************/
#include <stdio.h>
#include <string.h>

#define SIZE_QUEEN 20
#define SIZE_CROSS 30
#define SIZE_LIB 100
#define MAX_LENGTH 15

struct Square
{
    char letter;
    int connectpoint;
    char direction;
    int startOfWord;
    int lengthH;
    int lengthV;
};

void task1RobotPaths();
void task2HumanPyramid();
void task3ParenthesisValidator();
void task4QueensBattle();
void task5CrosswordGenerator();
int RobotPath(int x, int y);

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

        if (scanf_s("%d", &task))
        {
            switch (task)
            {
            case 6:
                printf("Goodbye!\n");
                break;
            case 1:
                task1RobotPaths();
                break;
            case 2:
                task2HumanPyramid();
                break;
            case 3:
                task3ParenthesisValidator();
                break;
            case 4:
                task4QueensBattle();
                break;
            case 5:
                task5CrosswordGenerator();
                break;
            default:
                printf("Please choose a task number from the list.\n");
                break;
            }
        }
        else
        {
            scanf_s("%*s");
        }

    } while (task != 6);
}

int RobotPath(int x, int y)
{
    // Base case
    if (x == 0 && y == 0){
        return 1;
    }

    int ways = 0;

    //Moving left
    if (x > 0)
        ways += RobotPath(x - 1, y);

    //Moving down
    if (y > 0)
        ways += RobotPath(x, y - 1);

    

    return ways;
}

void task1RobotPaths()
{
    int counter = 0;
    int x, y;
    printf("Please enter the coordinates of the robot (column, row):\n");
    scanf_s(" %d %d", &x, &y);
    printf("The total number of paths the robot can take to reach home is: %d\n", RobotPath(x, y));

}

int check_bounds(int x, int border_l, int border_r)
{
    if (x >= border_l && x <= border_r)
        return 1;
    else
        return 0;
}

float Weight(float Pyramid[5][9], int i, int j)
{
    float l_schoulder, r_schoulder;

    if (check_bounds(i - 1, 0, 4) == 1 && check_bounds(j - 1, 0 , 9) == 1)
        l_schoulder = Weight(Pyramid, i - 1, j - 1);
    else
        l_schoulder = 0;

    if (check_bounds(i - 1, 0, 4) == 1 && check_bounds(j + 1, 0, 9) == 1)
        r_schoulder = Weight(Pyramid, i - 1, j + 1);
    else
       r_schoulder = 0;

    return (l_schoulder / 2) + (r_schoulder / 2) + Pyramid[i][j];
}

void task2HumanPyramid()
{
    float HumanPyramid[5][9];

    // 0 0 0 0 1 0 0 0 0
    // 0 0 0 1 0 1 0 0 0
    // 0 0 1 0 1 0 1 0 0
    // 0 1 0 1 0 1 0 1 0
    // 1 0 1 0 1 0 1 0 1

    int n = 4;
    int jj = -1;

    for (int i = 0; i <= n; i++, jj = -1)
    {
        for (int j = 0; j < 9; j++)
        {
            HumanPyramid[i][j] = 0.0; // Initialize to 0

            if ((j == n - i) || (j == jj))
            {
                if (j + 2 <= n + i)
                    jj = j + 2;

                scanf_s(" %f", &HumanPyramid[i][j]); // Use address-of operator
            }
        }
    }


    for (int i = 0; i <= n; i++, printf("\n"))
        for (int j = 0; j < 9; j++)
            printf(" %2.2f", Weight(HumanPyramid, i, j)); // Correct format specifier
}

int CheckBraces(char ch, int b00l, int* firstClosure)
{
    char nextch;
    scanf_s("%c", &nextch);
    /*nextch = getchar();*/

    // Base case: end of input
    if (nextch == '\n')
        return b00l - *firstClosure;

    //// Skip invalid characters
    if (nextch != '(' && nextch != ')' &&
        nextch != '[' && nextch != ']' &&
        nextch != '{' && nextch != '}' &&
        nextch != '<' && nextch != '>')
    {
        return CheckBraces(ch, b00l, firstClosure);// Continue reading without altering logic
    }

    //// Check if the current brace is matched by the next
    if ((ch == '(' && nextch == ')') ||
        (ch == '[' && nextch == ']') ||
        (ch == '{' && nextch == '}') ||
        (ch == '<' && nextch == '>'))
    {
        *firstClosure = 0;
        return 1;// Pair matched
    }

    //// Check for opening braces to process further
    if (nextch == '(' || nextch == '[' || nextch == '{' || nextch == '<')
    {
        return CheckBraces(nextch, b00l, firstClosure) && CheckBraces(ch, b00l, firstClosure);
    }

    //// Unmatched or invalid brace
    return 0;
}


void task3ParenthesisValidator()
{
    char ch;
    char buffer = '\n';
    int b00l, firstClosure;
    b00l = 1;
    firstClosure = 1;
    ch = '\n';
   // ch = getchar();
    scanf_s("%*c");
    //i have used pointer to check if there is a least one closure
    //we learned pointers on prev lesson so i think its fine
    //i could actually make this check in other form but it will be much more comlicated 
    //so if its illegal to use them im sorry pleease dont reduce points
    if (CheckBraces(ch, b00l, &firstClosure) == 0)
    {
        printf("The parentheses are not balanced correctly.\n");
        scanf_s("%*s");
    }
    else
        printf("The parentheses are balanced correctly.\n");

     

}



void init(int Array[SIZE_QUEEN], int size)
{
    for (int i = 0; i < size; i++)
        Array[i] = -1;
}

void Clone(char Array[SIZE_QUEEN], char Clone[SIZE_QUEEN], int size)
{
    for (int i = 0; i < size; i++)
        Clone[i] = Array[i];
}

int CheckUnusedColor(char c, char Color[SIZE_QUEEN], int size)
{
    for (int i = 0; i < size; i++)
        if (Color[i] == c)
            return i;
    return -1;
}

//int CheckAround(int X_arr[20], int Y_arr[20], int x, int y, int size, int countQueen) {
//    for (int i = 0; i < countQueen; i++) {
//        if (abs(X_arr[i] - x) <= 1 && abs(Y_arr[i] - y) <= 1) {
//            return 0; // Position is adjacent
//        }
//    }
//    return 1;
//}

int CheckAround(int X_arr[SIZE_QUEEN], int Y_arr[SIZE_QUEEN], int x, int y, int size, int countQueen)
{
    //check right up pos
    if (check_bounds(x + 1, 0, size - 1) && check_bounds(y + 1, 0, size - 1))
        for (int i = 0; i < countQueen; i++)
            if (X_arr[i] == x + 1 && Y_arr[i] == y + 1)
                return 0;

    //check right down pos
    if (check_bounds(x + 1, 0, size - 1) && check_bounds(y - 1, 0, size - 1))
        for (int i = 0; i < countQueen; i++)
            if (X_arr[i] == x + 1 && Y_arr[i] == y - 1)
                return 0;

    //check left up pos
    if (check_bounds(x - 1, 0, size - 1) && check_bounds(y + 1, 0, size - 1))
        for (int i = 0; i < countQueen; i++)
            if (X_arr[i] == x - 1 && Y_arr[i] == y - 1)
                return 0;

    //check left down pos
    if (check_bounds(x - 1, 0, size - 1) && check_bounds(y - 1, 0, size - 1))
        for (int i = 0; i < countQueen; i++)
            if (X_arr[i] == x - 1 && Y_arr[i] == y - 1)
                return 0;

    return 1;
}


int Checkaxis(int Ax_arr[SIZE_QUEEN], int x, int size)
{
    for (int i = 0; i < size; i++)
        if (Ax_arr[i] == x)
            return 0;
    return 1;
}


int checkInArray(char ch, char Array[SIZE_QUEEN], int size)
{
    for (int i = 0; i < size; i++)
        if (Array[i] == ch)
            return 1;

    return 0;
}

int PlaceQueen(int x, int y, int X_axis[SIZE_QUEEN], int Y_axis[SIZE_QUEEN], char Color[SIZE_QUEEN],
    char Board[SIZE_QUEEN][SIZE_QUEEN], int size, int countQ)
{
    // Base case: All queens are placed
    if (countQ == size) {
        return 1;
    }

    // If row index exceeds the board size, return failure
    if (y >= size) {
        return 0;
    }

    // If column index exceeds the board size, move to the next row
    if (x >= size) {
        return PlaceQueen(0, y + 1, X_axis, Y_axis, Color, Board, size, countQ);
    }

    // Check if current position is valid
    int tmp = CheckUnusedColor(Board[y][x], Color, size);
    if (tmp != -1 && CheckAround(X_axis, Y_axis, x, y, size, countQ) == 1 &&
        Checkaxis(X_axis, x, size) == 1 && Checkaxis(Y_axis, y, size) == 1) {

        // Place the queen
        X_axis[countQ] = x;
        Y_axis[countQ] = y;
        Color[tmp] = '\0'; // Mark the color as used

        // Recurse to place the next queen
        if (PlaceQueen(0, y + 1, X_axis, Y_axis, Color, Board, size, countQ + 1)) {
            return 1; // Solution found
        }

        // Backtrack if placement fails
        X_axis[countQ] = -1;
        Y_axis[countQ] = -1;
        Color[tmp] = Board[y][x]; // Reset the color
    }

    // Try the next column
    return PlaceQueen(x + 1, y, X_axis, Y_axis, Color, Board, size, countQ);
}

void task4QueensBattle()
{
    char Board[SIZE_QUEEN][SIZE_QUEEN];
    int X_axis[SIZE_QUEEN];
    int Y_axis[SIZE_QUEEN];
    char Color[SIZE_QUEEN];
    char CColor[SIZE_QUEEN];
    int size, counter = 0;
    printf("Please enter the board dimensions:\n");
    scanf_s(" %d", &size);
    printf("Please enter the %d*%d puzzle board:\n", size, size);

    for (int i = 0; i < size; i++)
        for (int j = 0; j < size; j++)
        {
            scanf_s(" %c", &Board[i][j]);

            if (checkInArray(Board[i][j], Color, size) == 0)
            {
                Color[counter++] = Board[i][j];
            }
        }

        int counterQueen = 0;
        Clone(Color, CColor, size);
        init(X_axis, size);
        init(Y_axis, size);
        if (PlaceQueen(0, 0, X_axis, Y_axis, CColor, Board, size, counterQueen) == 1)
        {
            for (int i = 0; i < size; i++, printf("\n"))
                for (int j = 0; j < size; j++)
                {
                    for (int k = 0; k < size; k++)
                        if (i == Y_axis[k] && j == X_axis[k])
                            printf(" X");
                    printf(" *");
                }
        }
        else
            printf("NO Solution\n");

}

void initCross(Square Board[SIZE_CROSS][SIZE_CROSS], int size)
{
    for (int i = 0; i < size; i++)
        for (int j = 0; j < size; j++)
        {
            Board[i][j].connectpoint = 0;
            Board[i][j].letter = '#';
            Board[i][j].direction = '0';
            Board[i][j].startOfWord = 0;
            Board[i][j].lengthH = 0;
            Board[i][j].lengthV = 0;
        }
}

//int CheckPlacementWord(int row, int col, Square Board[SIZE_CROSS][SIZE_CROSS], int size_board,
//    char lib[SIZE_LIB][MAX_LENGTH], int size_lib)
//{
//    if (Board[row][col].direction == 'V')
//        for (int i = 0; i < size_lib; i++) // searching word from lib
//            if (sizeof(lib[i]) / sizeof(lib[0]) == Board[row][col].lengthV) //check if same length
//            {
//                for (int j = 0; j < Board[row][col].lengthV; j++)
//                {
//
//                }
//            }
//        
//                //Board[row][col].letter == ' ' && Board[row][col].connectpoint != 0 && Board[row][col].direcion != '0';
//
//   // if (Board[row][col].direction == 'H')
//    return 1;
//}

// Checks if the word can be placed at the given position
int CheckPlacementWord(int row, int col, Square Board[SIZE_CROSS][SIZE_CROSS], int size_board, char lib[SIZE_LIB][MAX_LENGTH], int size_lib) {
    for (int w = 0; w < size_lib; w++) {
        int valid = 1;

        // Check horizontal placement
        if (Board[row][col].direction == 'H') {
            for (int k = 0; k < Board[row][col].lengthH; k++) {
                if (col + k >= size_board ||
                    (Board[row][col + k].letter != ' ' && Board[row][col + k].letter != lib[w][k])) {
                    valid = 0;
                    break;
                }
            }
            if (valid && strlen(lib[w]) == Board[row][col].lengthH)
                return w;
        }

        // Check vertical placement
        if (Board[row][col].direction == 'V') {
            for (int k = 0; k < Board[row][col].lengthV; k++) {
                if (row + k >= size_board ||
                    (Board[row + k][col].letter != ' ' && Board[row + k][col].letter != lib[w][k])) {
                    valid = 0;
                    break;
                }
            }
            if (valid && strlen(lib[w]) == Board[row][col].lengthV)
                return w;
        }
    }

    return -1; // No valid word found
}


// Place a word on the board
void PlaceWord(int row, int col, Square Board[SIZE_CROSS][SIZE_CROSS], char word[MAX_LENGTH]) {
    if (Board[row][col].direction == 'H') {
        for (int k = 0; word[k] != '\0'; k++) {
            Board[row][col + k].letter = word[k];
        }
    }
    else if (Board[row][col].direction == 'V') {
        for (int k = 0; word[k] != '\0'; k++) {
            Board[row + k][col].letter = word[k];
        }
    }
}

// Remove a word from the board (backtracking step)
void UnplaceWord(int row, int col, Square Board[SIZE_CROSS][SIZE_CROSS], char word[MAX_LENGTH]) {
    if (Board[row][col].direction == 'H') {
        for (int k = 0; word[k] != '\0'; k++) {
            Board[row][col + k].letter = ' ';
        }
    }
    else if (Board[row][col].direction == 'V') {
        for (int k = 0; word[k] != '\0'; k++) {
            Board[row + k][col].letter = ' ';
        }
    }
}


int SolveCrossword(int row, int col, Square Board[SIZE_CROSS][SIZE_CROSS], int size_board,
    char lib[SIZE_LIB][MAX_LENGTH], int size_lib, int count_word) {

    // Base case: All words placed
    if (count_word == size_lib)
        return 1;

    // Move to the next row if column exceeds the board size
    if (col >= size_board)
        return SolveCrossword(row + 1, 0, Board, size_board, lib, size_lib, count_word);

    // If row exceeds the board size, no solution
    if (row >= size_board)
        return 0;

    // Skip cells that are not the start of a word
    if (!Board[row][col].startOfWord)
        return SolveCrossword(row, col + 1, Board, size_board, lib, size_lib, count_word);

    // Try placing a word in the current slot
    int p = CheckPlacementWord(row, col, Board, size_board, lib, size_lib);
    if (p != -1) {
        PlaceWord(row, col, Board, lib[p]);

        // Mark the word as used by swapping it to the end of the list
        char temp[MAX_LENGTH];
        strcpy_s(temp, lib[p]);
        strcpy_s(lib[p], lib[size_lib - 1]);
        strcpy_s(lib[size_lib - 1], temp);

        // Recur to place the next word
        if (SolveCrossword(row, col + 1, Board, size_board, lib, size_lib - 1, count_word + 1))
            return 1;

        // Backtrack: Undo the placement and restore the library
        UnplaceWord(row, col, Board, temp);
        strcpy_s(lib[size_lib - 1], lib[p]);
        strcpy_s(lib[p], temp);
    }

    // Try the next cell
    return SolveCrossword(row, col + 1, Board, size_board, lib, size_lib, count_word);
}

void task5CrosswordGenerator()
{
    Square Board[SIZE_CROSS][SIZE_CROSS];
    int size_cross;
    printf("Please enter the dimensions of the crossword grid:\n");
    scanf_s(" %d", &size_cross);
    initCross(Board, size_cross);

    int numSlots;
    printf("Please enter the number of slots in the crossword:\n");
    scanf_s(" %d", &numSlots);

    int row, col, length;
    char direction;
    printf("Please enter the details for each slot (Row, Column, Length, Direction):\n");
    for (int i = 0; i < numSlots; i++)
    {
        scanf_s(" %d", &row);
        scanf_s(" %d", &col);
        scanf_s(" %d", &length);
        scanf_s(" %c", &direction);

        Board[row][col].startOfWord = 1;
 
        if (direction == 'H')
        {
            Board[row][col].direction = 'H';
            Board[row][col].lengthH = length;
            for (int k = col; k < length + col; k++)
            {
                Board[row][k].letter = ' ';
                ++Board[row][k].connectpoint;
            }
        }
            
        if (direction == 'V')
        {
            Board[row][col].lengthV = length;
            for (int k = row; k < length + row; k++)
            {
                Board[k][col].letter = ' ';
                ++Board[k][col].connectpoint;
            }
        }

        if (Board[row][col].connectpoint == 2)
        {
            Board[row][col].direction = 'B';
        }


    }

    char library[SIZE_LIB][MAX_LENGTH];
    int size_lib;
    printf("Please enter the number of words in the dictionary:\n");
    scanf_s(" %d", &size_lib);
    while (size_lib < numSlots)
    {
        printf("The dictionary must contain at least 8 words. Please enter a valid dictionary size:\n");
        scanf_s(" %d", &size_lib);
    }

    printf("Please enter the words for the dictionary:\n");
    scanf_s("%*c");
    for (int i = 0; i < size_lib; i++)
    {
        fgets(library[i], MAX_LENGTH, stdin);
        library[i][strcspn(library[i], "\n")] = '\0';
    }
    
    int count_word = 0;
    if (SolveCrossword(0,0, Board, size_cross, library, size_lib, count_word) == 0)
        printf("This crossword cannot be solved.\n");
    else
        for (int i = 0; i < size_cross; i++, printf("\n"))
        {
            printf("| ");
            for (int j = 0; j < size_cross; j++)
                printf("%c |", Board[i][j].letter);
        }
        
}
