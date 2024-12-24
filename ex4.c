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

void task1RobotPaths();
int task2HumanPyramid();
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

        if (scanf("%d", &task))
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
    if (x == 0 && y == 0) {
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
    int x, y;
    printf("Please enter the coordinates of the robot (column, row):\n");
    scanf(" %d %d", &x, &y);
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

    if (check_bounds(i - 1, 0, 4) == 1 && check_bounds(j - 1, 0, 9) == 1)
        l_schoulder = Weight(Pyramid, i - 1, j - 1);
    else
        l_schoulder = 0;

    if (check_bounds(i - 1, 0, 4) == 1 && check_bounds(j + 1, 0, 9) == 1)
        r_schoulder = Weight(Pyramid, i - 1, j + 1);
    else
        r_schoulder = 0;

    return (l_schoulder / 2) + (r_schoulder / 2) + Pyramid[i][j];
}

int task2HumanPyramid()
{
    printf("Please enter the weights of the cheerleaders:\n");
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

                scanf(" %f", &HumanPyramid[i][j]);
                if (HumanPyramid[i][j] < 0)
                {
                    printf("Negative weights are not supported.\n");
                    return 0;
                }
            }
        }
    }

    printf("The total weight on each cheerleader is:\n");
    for (int i = 0; i <= n; i++, printf("\n"))
        for (int j = 0; j < 9; j++)
            printf(" %2.2f", Weight(HumanPyramid, i, j)); 
    return 1;
}

int CheckBraces(char ch, int b00l, int* firstClosure)
{
    char nextch;
    scanf("%c", &nextch);

    // Base case: end of input
    if (nextch == '\n')
        return b00l - *firstClosure;

    // Skip invalid characters
    if (nextch != '(' && nextch != ')' &&
        nextch != '[' && nextch != ']' &&
        nextch != '{' && nextch != '}' &&
        nextch != '<' && nextch != '>')
    {
        return CheckBraces(ch, b00l, firstClosure);
    }

    // Check if the current brace is matched by the next
    if ((ch == '(' && nextch == ')') ||
        (ch == '[' && nextch == ']') ||
        (ch == '{' && nextch == '}') ||
        (ch == '<' && nextch == '>'))
    {
        *firstClosure = 0;
        return 1;
    }

    // Check for opening braces to process further
    if (nextch == '(' || nextch == '[' || nextch == '{' || nextch == '<')
    {
        return CheckBraces(nextch, b00l, firstClosure) && CheckBraces(ch, b00l, firstClosure);
    }

    // Unmatched
    return 0;
}


void task3ParenthesisValidator()
{
    char ch;
    int b00l, firstClosure;
    b00l = 1;
    firstClosure = 1;
    ch = '\n';
    printf("Please enter a term for validation:\n");
    scanf("%*c");
    //i have used pointer to check if there is a least one closure
    //we learned pointers on prev lesson so i think its fine
    //i could actually make this check in other form but it will be much more comlicated 
    //so if its illegal to use them im sorry pleease dont reduce points

    if (CheckBraces(ch, b00l, &firstClosure) == 0)
    {
        printf("The parentheses are not balanced correctly.\n");
        scanf("%*s");
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


int CheckAround(int X_arr[SIZE_QUEEN], int Y_arr[SIZE_QUEEN], int x, int y, int size, int countQueen)
{
    //check corners pos
    if (check_bounds(x + 1, 0, size - 1) && check_bounds(y + 1, 0, size - 1))
        for (int i = 0; i < countQueen; i++)
            if (X_arr[i] == x + 1 && Y_arr[i] == y + 1)
                return 0;

    if (check_bounds(x + 1, 0, size - 1) && check_bounds(y - 1, 0, size - 1))
        for (int i = 0; i < countQueen; i++)
            if (X_arr[i] == x + 1 && Y_arr[i] == y - 1)
                return 0;

    if (check_bounds(x - 1, 0, size - 1) && check_bounds(y + 1, 0, size - 1))
        for (int i = 0; i < countQueen; i++)
            if (X_arr[i] == x - 1 && Y_arr[i] == y - 1)
                return 0;

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

    // If row index exceeds the board size
    if (y >= size) {
        return 0;
    }

    //Move to the next row
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
    scanf(" %d", &size);
    printf("Please enter the %d*%d puzzle board:\n", size, size);

    for (int i = 0; i < size; i++)
        for (int j = 0; j < size; j++)
        {
            scanf(" %c", &Board[i][j]);

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

struct Square {
    char letter;
    char direction; // 'H', 'V', 'B' (bidirectional)
    int lengthH;
    int lengthV;
    int startOfWord;
    int connectpoint;
};

 struct Optional {
    int dirV;
    int dirH;
    int counter;
};

void initCross(Square Board[SIZE_CROSS][SIZE_CROSS], int size) {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            Board[i][j].letter = '#';
            Board[i][j].direction = ' ';
            Board[i][j].lengthH = 0;
            Board[i][j].lengthV = 0;
            Board[i][j].startOfWord = 0;
            Board[i][j].connectpoint = 0;
        }
    }
}


Optional CheckPlacementWord(int row, int col, Square Board[SIZE_CROSS][SIZE_CROSS],
    int size_board, char lib[SIZE_LIB][MAX_LENGTH], int size_lib) {
    Optional OP;
    OP.dirV = OP.dirH = -1;
    int counter = 0;


    for (int w = 0; w < size_lib; w++) {
        int validV = 1, validH = 1;


        // Check vertical placement
        if ((Board[row][col].direction == 'V' || Board[row][col].direction == 'B')) {
            for (int k = 0; k < Board[row][col].lengthV; k++) {
                if (row + k >= size_board ||
                    (Board[row + k][col].letter != ' ' && Board[row + k][col].letter != lib[w][k])) {
                    validV = 0;
                }
            }
            if (validV && strlen(lib[w]) == Board[row][col].lengthV) {
                if (OP.dirV == -1)
                {
                    OP.dirV = w;
                }
                counter++;
            }
        }

        // Check horizontal placement
        if ((Board[row][col].direction == 'H' || Board[row][col].direction == 'B')) {
            for (int k = 0; k < Board[row][col].lengthH; k++) {
                if (col + k >= size_board ||
                    (Board[row][col + k].letter != ' ' && Board[row][col + k].letter != lib[w][k])) {
                    validH = 0;
                }
            }
            if (validH && strlen(lib[w]) == Board[row][col].lengthH) {
                if (OP.dirH == -1)
                {
                    OP.dirH = w;
                }
                counter++;
            }

        }

        
        if (OP.dirV != -1 && OP.dirH != -1) break; // Early exit if both directions are valid
    }
    OP.counter = counter;
    return OP;
}


void PlaceWord(int row, int col, Square Board[SIZE_CROSS][SIZE_CROSS], char word[MAX_LENGTH],
    char direction, char B[MAX_LENGTH]) {
    if (direction == 'H') {
        for (int k = 0; word[k] != '\0'; k++) {
            if (Board[row][col + k].letter != ' ')
                B[col + k] = Board[row][col + k].letter;
            Board[row][col + k].letter = word[k];
        }
    }
    else if (direction == 'V') {
        for (int k = 0; word[k] != '\0'; k++) {
            if (Board[row + k][col].letter != ' ')
                B[row + k] = Board[row + k][col].letter;
            Board[row + k][col].letter = word[k];
        }
    }
}

void UnplaceWord(int row, int col, Square Board[SIZE_CROSS][SIZE_CROSS], char word[MAX_LENGTH],
    char direction, char B[MAX_LENGTH]) {
    if (direction == 'H') {
        for (int k = 0; word[k] != '\0'; k++) {
            if (Board[row][col + k].letter != B[col + k])
                Board[row][col + k].letter = ' ';
        }
    }
    else if (direction == 'V') {
        for (int k = 0; word[k] != '\0'; k++) {
            if (Board[row + k][col].letter != B[row + k])
                Board[row + k][col].letter = ' ';
        }
    }
}

void PrintBoard(Square Board[SIZE_CROSS][SIZE_CROSS], int size_board) {
    for (int i = 0; i < size_board; i++, printf("\n")) {
        printf("| ");
        for (int j = 0; j < size_board; j++) {
            printf("%c |", Board[i][j].letter);
        }
    }
}

int SolveCrossword(int row, int col, Square Board[SIZE_CROSS][SIZE_CROSS], int size_board,
    char lib[SIZE_LIB][MAX_LENGTH], int size_lib, int count_word, char used[SIZE_LIB][MAX_LENGTH],
    int used_counter, int slots)
{
    if (count_word == slots)
        return 1;

    if (col >= size_board)
        return SolveCrossword(row + 1, 0, Board, size_board, lib, size_lib, count_word, used, used_counter, slots);

    if (row >= size_board)
        return 0;

    if (!Board[row][col].startOfWord)
        return SolveCrossword(row, col + 1, Board, size_board, lib, size_lib, count_word, used, used_counter, slots);

    Optional OptPlace = CheckPlacementWord(row, col, Board, size_board, lib, size_lib);

    if (OptPlace.dirV != -1) {
        char letters[MAX_LENGTH];
        //printf("Placing word %s verticaly:\n", lib[OptPlace.dirV]);
        PlaceWord(row, col, Board, lib[OptPlace.dirV], 'V', letters);
        //PrintBoard(Board, size_board);

        strcpy(used[used_counter], lib[OptPlace.dirV]);
        lib[OptPlace.dirV][0] = '\0';

        if (OptPlace.dirH != -1)
            if (SolveCrossword(row, col, Board, size_board, lib, size_lib, count_word + 1, used, used_counter + 1,
                slots))
                return 1;
        if (SolveCrossword(row, col + 1, Board, size_board, lib, size_lib, count_word + 1, used, used_counter + 1,
            slots))
            return 1;

        //printf("Deleting word %s verticaly:\n", used[used_counter]);
        UnplaceWord(row, col, Board, used[used_counter], 'V', letters);
        //PrintBoard(Board, size_board);
        strcpy(lib[OptPlace.dirV], used[used_counter]);

        char tmp[MAX_LENGTH] = { '\0' };
        strcpy(lib[OptPlace.dirV], tmp);
        strcpy(lib[OptPlace.dirV], lib[size_lib - 1]);
        strcpy(lib[size_lib - 1], tmp);

    }

    if (OptPlace.dirH != -1) {
        char letters[MAX_LENGTH];

        //printf("Placing word %s horizontaly:\n", lib[OptPlace.dirH]);
        PlaceWord(row, col, Board, lib[OptPlace.dirH], 'H', letters);
        //PrintBoard(Board, size_board);

        strcpy(used[used_counter], lib[OptPlace.dirH]);
        lib[OptPlace.dirH][0] = '\0';

        if (OptPlace.dirV != -1)
            if (SolveCrossword(row, col, Board, size_board, lib, size_lib, count_word + 1, used, used_counter + 1,
                slots))
                return 1;
        if (SolveCrossword(row, col + 1, Board, size_board, lib, size_lib, count_word + 1, used, used_counter + 1,
            slots))
            return 1;


        //printf("Deleting word %s horizonaly:\n", used[used_counter]);
        UnplaceWord(row, col, Board, used[used_counter], 'H', letters);
        //PrintBoard(Board, size_board);
        strcpy(lib[OptPlace.dirH], used[used_counter]);

        char tmp[MAX_LENGTH] = { '\0' };
        strcpy(lib[OptPlace.dirH], tmp);
        strcpy(lib[OptPlace.dirH], lib[size_lib - 1]);
        strcpy(lib[size_lib - 1], tmp);

    }

    if (OptPlace.counter != 1)
        return SolveCrossword(row, col, Board, size_board, lib, size_lib, count_word, used, used_counter, slots);
    return SolveCrossword(row, col + 1, Board, size_board, lib, size_lib, count_word, used, used_counter, slots);
}

void task5CrosswordGenerator() {
    Square Board[SIZE_CROSS][SIZE_CROSS];
    int size_cross;
    printf("Please enter the dimensions of the crossword grid:\n");
    scanf("%d", &size_cross);
    initCross(Board, size_cross);

    int numSlots;
    printf("Please enter the number of slots in the crossword:\n");
    scanf("%d", &numSlots);

    int row, col, length;
    char direction;
    printf("Please enter the details for each slot (Row, Column, Length, Direction):\n");
    for (int i = 0; i < numSlots; i++) {
        scanf(" %d", &row);
        scanf(" %d", &col);
        scanf(" %d", &length);
        scanf(" %c", &direction);

        Board[row][col].startOfWord++;
        if (direction == 'H') {
            Board[row][col].direction = 'H';
            Board[row][col].lengthH = length;
            for (int i = col; i < Board[row][col].lengthH + col; i++)
            {
                Board[row][i].letter = ' ';
                Board[row][i].connectpoint++;
            }
        }

        if (direction == 'V') {
            Board[row][col].direction = 'V';
            Board[row][col].lengthV = length;
            for (int i = row; i < Board[row][col].lengthV + row; i++)
            {
                Board[i][col].letter = ' ';
                Board[i][col].connectpoint++;
            }

            if (Board[row][col].startOfWord == 2) {
                Board[row][col].direction = 'B';
            }
        }
    }

    char library[SIZE_LIB][MAX_LENGTH];
    char Used[SIZE_LIB][MAX_LENGTH];
    int size_lib;
    printf("Please enter the number of words in the dictionary:\n");
    scanf("%d", &size_lib);
    while (size_lib < numSlots)
    {
        printf("The dictionary must contain at least 8 words.Please enter a valid dictionary size:\n");
        scanf("%d", &size_lib);
    }
    
    printf("Please enter the words for the dictionary:\n");
    for (int i = 0; i < size_lib; i++) {
        scanf(" %s", library[i]);
        //fgets(library[i], MAX_LENGTH, stdin);
        //library[i][strcspn(library[i], "\n")] = '\0';
    }


    if (SolveCrossword(0, 0, Board, size_cross, library, size_lib, 0 , Used, 0, numSlots) == 0) {
        printf("This crossword cannot be solved.\n");
    }
    else {
        PrintBoard(Board, size_cross);
    }
}

