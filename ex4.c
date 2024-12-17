/******************
Name: Maxim Muradov
ID: 346975386
Assignment: ex4
*******************/
#include <stdio.h>
#include <string.h>

#define SIZE = 20

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

int CheckBraces(char ch, int b00l)
{
    char nextch;
    scanf_s(" %c", &nextch);

    //Base case
    if (nextch == '\n' || b00l == 0)
        return b00l;

    //Check if braces are closed
    if (ch == '(' && nextch == ')' || ch == nextch - 2)
        return b00l;

    //Moving right
    if (nextch == '(' || nextch == '[' || nextch == '{' || nextch == '<')
        return CheckBraces(nextch, b00l);

    return 0;
}

void task3ParenthesisValidator()
{
    char ch;
    int b00l;
    scanf_s(" %c", &ch);
    if (ch == '(' || ch == '[' || ch == '{' || ch == '<')
    {
        b00l = 1;
        if (CheckBraces(ch, b00l) == 0)
            printf("The parentheses are not balanced correctly.");
        else
            printf("The parentheses are balanced correctly.");
    }
    else
        printf("The parentheses are not balanced correctly.");
}

int checkUnusedColor(char c, char Color[20], int size)
{
    for (int i = 0; i < size; i++)
        if (Color[i] == c)
            return i;
        else
            return -1;
}

int checkInArray(char ch, char Array[20], int size)
{
    for (int i = 0; i < size; i++)
        if (Array[i] == ch)
            return 1;

    return 0;
}

int PlaceQueen(int x, int y, int X_axis[20], int Y_axis[20], char Color[20], char Board[20][20], int size)
{
    if (X_axis[x] == 0 && Y_axis[y] == 0 && checkUnusedColor(Board[x][y], Color, size) != -1)
    {
        X_axis[x] = 1;
        Y_axis[y] = 1;
        Color[checkUnusedColor(Board[x][y], Color, size)] = '0';
        return 1;
    }

    if (checkUnusedColor(Board[x][y], Color, size) == -1)
        return 0;

    if (X_axis[x] != 0 && check_bounds(x, 0, size - 1) == 1)
        return PlaceQueen(x + 1, y, X_axis, Y_axis, Color, Board, size);

    if (Y_axis[y] != 0 && check_bounds(y, 0, size - 1) == 1)
        return PlaceQueen(x, y + 1, X_axis, Y_axis, Color, Board, size);

   
}

void task4QueensBattle()
{
    char Board[20][20];
    int X_axis[20];
    int Y_axis[20];
    char Color[20];
    int size, counter = 0, c = 0;
    printf("Please enter the board dimensions:\n");
    scanf_s(" %d", &size);
    printf("Please enter the %d*%d puzzle board:\n", size, size);

    for (int i = 0; i < size; i++)
        for (int j = 0; j < size; j++)
        {
            X_axis[i] = Y_axis[i] = 0;

            scanf_s(" %c", &Board[i][j]);

            if (checkInArray(Board[i][j], Color, size) == 0)
            {
                Color[counter++] = Board[i][j];
            }

        }

    for (int i = 0; i < size; i++)
    PlaceQueen(i, 0, X_axis, Y_axis, Color, Board, size);

    /*for (int i = 0; i < size; i++, printf("\n"))
        for (int j = 0; j < size; j++)
            printf("%c", Board[i][j]);*/

}

void task5CrosswordGenerator()
{
    // Todo
}
