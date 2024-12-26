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

struct Crossword 
{
    int row;        
    int col;        
    int length;     
    char dir;       
};

void task1RobotPaths();
int task2HumanPyramid();
int task3ParenthesisValidator();
void task4QueensBattle();
void task5CrosswordGenerator();

int RobotPath(int x, int y);

int check_bounds(int x, int border_l, int border_r);
float Weight(float Pyramid[5][9], int i, int j);

int CheckBraces(char ch, int b00l, int* firstClosure);

void init(int Array[SIZE_QUEEN], int size);
void Clone(char Array[SIZE_QUEEN], char Clone[SIZE_QUEEN], int size);
int CheckUnusedColor(char c, char Color[SIZE_QUEEN], int size);
int CheckAround(int X_arr[SIZE_QUEEN], int Y_arr[SIZE_QUEEN], int x, int y, int size, int countQueen);
int Checkaxis(int Ax_arr[SIZE_QUEEN], int x, int size);
int checkInArray(char ch, char Array[SIZE_QUEEN], int size);
int PlaceQueen(int x, int y, int X_axis[SIZE_QUEEN], int Y_axis[SIZE_QUEEN], char Color[SIZE_QUEEN],
    char Board[SIZE_QUEEN][SIZE_QUEEN], int size, int countQ);

int TryPlaceWord(char Lib[], char Board[][SIZE_CROSS], int row, int col, char direction, int i);
void PlaceWord(char Board[][SIZE_CROSS], int row, int col, char direction, char Lib[], int i);
void UnplaceWord(char Board[][SIZE_CROSS], int row, int col, int length, char direction);
int SolveCrossword(int row, int col, char Lib[][SIZE_LIB], struct Crossword cword[],  
                   int words_placed, char Board[][SIZE_CROSS], int Used[], 
                   int size_lib, int slots, int index_slot);


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
            scanf("%*s");
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

    if (check_bounds(i - 1, 0, 4) == 1 && check_bounds(j - 1, 0, 8) == 1)
        l_schoulder = Weight(Pyramid, i - 1, j - 1);
    else
        l_schoulder = 0;

    if (check_bounds(i - 1, 0, 4) == 1 && check_bounds(j + 1, 0, 8) == 1)
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

  for (int i = 0; i <= n; i++) {
    int jj = -1; 
    for (int j = 0; j < 9; j++) {
        HumanPyramid[i][j] = 0.0; 

        
        if ((j == n - i) || (j == jj)) {
            if (jj == -1) jj = n - i; 
            if (j + 2 <= n + i) jj = j + 2;

            // Input weight for valid cheerleaders
            scanf(" %f", &HumanPyramid[i][j]);
            if (HumanPyramid[i][j] < 0) {
                printf("Negative weights are not supported.\n");
                return 0;
            }
        }
    }
}

printf("The total weight on each cheerleader is:\n");
for (int i = 0; i <= n; i++,  printf("\n")) {
    int jj = -1; 
    for (int j = 0; j < 9; j++) {
        
        if ((j == n - i) || (j == jj)) {
            if (jj == -1) jj = n - i; // Start from the leftmost valid position
            if (j + 2 <= n + i) jj = j + 2;

            
            printf(" %2.2f", Weight(HumanPyramid, i, j));
        }
    }
}

    
    return 1;
}

int CheckBraces(char ch, int b00l, int* Closure)
{
    char nextch;
    scanf("%c", &nextch);

    // Base case: end of input
    if (nextch == '\n')
        return b00l - *Closure;

    // Skip invalid characters
    if (nextch != '(' && nextch != ')' &&
        nextch != '[' && nextch != ']' &&
        nextch != '{' && nextch != '}' &&
        nextch != '<' && nextch != '>')
    {
        return CheckBraces(ch, b00l, Closure);
    }

    // Check if the current brace is matched by the next
    if ((ch == '(' && nextch == ')') ||
        (ch == '[' && nextch == ']') ||
        (ch == '{' && nextch == '}') ||
        (ch == '<' && nextch == '>'))
    {
        *Closure = 0;
        return = 1;
    }

    // Check for opening braces to process further
    if (nextch == '(' || nextch == '[' || nextch == '{' || nextch == '<')
    {
        *Closure = 1;
        return CheckBraces(nextch, b00l, Closure) && CheckBraces(ch, b00l, Closure);
    }

    // Unmatched
    return 0;
}


int task3ParenthesisValidator()
{
    char ch;
    int b00l, Closure;
    b00l = 1;
    Closure = 1;
    ch = '\n';
    printf("Please enter a term for validation:\n");
    scanf("%*c");
    
    //i have used pointer to check if there is a closure
    //we learned pointers on prev lesson so i think its fine
    //i could actually make this check in other form but it will be much more comlicated 
    //so if its illegal to use them im sorry pleease dont reduce points

    if (CheckBraces(ch, b00l, &Closure) == 0)
    {
        printf("The parentheses are not balanced correctly.\n");
        return 1;
    }
    else
    {
        printf("The parentheses are balanced correctly.\n");
        return 0;
    }


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
    printf("Please enter a %d*%d puzzle board:\n", size, size);

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
        printf("Solution:\n");
        for (int i = 0; i < size; i++, printf("\n")) {
            for (int j = 0; j < size; j++) {
                int isQueen = 0;
                for (int k = 0; k < size; k++) {
                    if (i == Y_axis[k] && j == X_axis[k]) {
                    printf("X ");
                    isQueen = 1;
                    break; // Stop checking after finding a queen for this position
                }
        }
        if (!isQueen) {
            printf("* ");
        }
    }
}
    }
    else
        printf("This puzzle cannot be solved.\n");

}


// Function to check if a word can be placed in the given slot
int TryPlaceWord(char Lib[], char Board[][SIZE_CROSS], int row, int col, char direction, int i) 
{
    // If we have placed the whole word, return 1
    if (Lib[i] == '\0') 
        return 1;

    // If not return 0
    if (Board[row][col] != '#' && Board[row][col] != Lib[i])
        return 0;

    // Move to the next cell
    if (direction == 'H') 
        return TryPlaceWord(Lib, Board, row, col + 1, direction, i + 1);
        
    if (direction == 'V')
        return TryPlaceWord(Lib, Board, row + 1, col, direction, i + 1); 

    return 0;
}


void PlaceWord(char Board[][SIZE_CROSS], int row, int col, char direction, char Lib[], int i) 
{
    // Base case
    if (Lib[i] == '\0') 
        return; 
        
    // Place the current character
    Board[row][col] = Lib[i];
    
    // Move to the next character 
    if (direction == 'H') 
        PlaceWord(Board, row, col + 1, direction, Lib, i + 1);
    else if (direction == 'V') 
        PlaceWord(Board, row + 1, col, direction, Lib, i + 1);
}


void UnplaceWord(char Board[][SIZE_CROSS], int row, int col, int length, char direction) 
{ 
    // Base case
    if (length == 0) 
        return;
        
    // Reset cell
    Board[row][col] = '#';  
    
    // Move to the next cell
    if (direction == 'H')
        UnplaceWord(Board, row, col + 1, length - 1, direction);
    else if (direction == 'V')
        UnplaceWord(Board, row + 1, col, length - 1, direction);
}


int SolveCrossword(int row, int col, char Lib[][SIZE_LIB], struct Crossword cword[],  
                   int words_placed, char Board[][SIZE_CROSS], int Used[], 
                   int size_lib, int slots, int index_slot) 
{
    // Base case: if all words are placed or all slots are filled, return 
    if (words_placed >= size_lib)
        return 0;
    if (index_slot >= slots)
        return 1;

    // Get the current word
    char tmp[MAX_LENGTH];
    strcpy(tmp, Lib[words_placed]); 

    // Check if the word can be placed
    if (!Used[words_placed] && (int)strlen(tmp) == cword[index_slot].length)
    {
        if (TryPlaceWord(tmp, Board, cword[index_slot].row, cword[index_slot].col, cword[index_slot].dir, 0))
        {
            // Place the word
            PlaceWord(Board, cword[index_slot].row, cword[index_slot].col, cword[index_slot].dir, tmp, 0);
            Used[words_placed] = 1;
            
            // Move to the next slot
            if (SolveCrossword(row, col, Lib, cword, 0, Board, Used, size_lib, slots, index_slot + 1))
                return 1;

            // Backtrack
            UnplaceWord(Board, cword[index_slot].row, cword[index_slot].col, cword[index_slot].length, cword[index_slot].dir);
            Used[words_placed] = 0;
        }
    }
    
    // Try the next word
    return SolveCrossword(row, col, Lib, cword, words_placed + 1, Board, Used, size_lib, slots, index_slot); 
}

void task5CrosswordGenerator() {
    
    int size_board;
    printf("Please enter the dimensions of the crossword grid:\n");
    scanf("%d", &size_board);
    
    int slots;
    printf("Please enter the number of slots in the crossword:\n");
    scanf("%d", &slots);
    
    struct Crossword crossword[SIZE_LIB];
    printf("Please enter the details for each slot (Row, Column, Length, Direction):\n");
    for (int i = 0; i < slots; i++) {
        scanf(" %d", &crossword[i].row);
        scanf(" %d", &crossword[i].col);
        scanf(" %d", &crossword[i].length);
        scanf(" %c", &crossword[i].dir);
    }
    
    int size_lib;
    printf("Please enter the number of words in the dictionary:\n");
    scanf("%d", &size_lib);
    while (size_lib < slots) {
        printf("The dictionary must contain at least %d words. Please enter a valid dictionary size:\n", slots);
        scanf("%d", &size_lib);
    }
    
    char Library[MAX_LENGTH][SIZE_LIB];
    printf("Please enter the words for the dictionary:\n");
    for (int i = 0; i < size_lib; i++)
        scanf(" %s", Library[i]);
    
    
    char Board[SIZE_CROSS][SIZE_CROSS];
    for (int i = 0; i < size_board; i++) {
        for (int j = 0; j < size_board; j++) {
            Board[i][j] = '#'; 
        }
    }
    
    int Used[SIZE_LIB] = {0}; // Array to track used words


    if (SolveCrossword(0, 0, Library, crossword, 0, Board, Used, size_lib, slots, 0))
    {
        for (int i = 0; i < size_board; i++, printf("\n"))
            {
            printf("|");
            for (int j = 0; j < size_board; j++) 
                printf(" %c|", Board[i][j]);
            }
    }
    else 
        printf("This crossword cannot be solved.\n");
    
}
