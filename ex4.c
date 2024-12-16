/******************
Name: Maxim Muradov
ID: 346975386
Assignment: ex4
*******************/
#include <stdio.h>
#include <string.h>

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

                scanf(" %f", &HumanPyramid[i][j]); // Use address-of operator
            }
        }
    }


    for (int i = 0; i <= n; i++, printf("\n"))
        for (int j = 0; j < 9; j++)
            printf(" %2.2f", Weight(HumanPyramid, i, j)); // Correct format specifier
}

int CheckBraces(char ch, int b00l)
{
    char nextch = getchar();

    // Debugging outputs
    printf("Char: %c\n", ch);
    printf("Next: %c\n", nextch);

    // Base case: end of input or mismatch
    if (nextch == '\n' || b00l == 0)
        return b00l;

    // Skip invalid characters
    if (nextch != '(' && nextch != ')' &&
        nextch != '[' && nextch != ']' &&
        nextch != '{' && nextch != '}' &&
        nextch != '<' && nextch != '>')
    {
        return CheckBraces(ch, b00l); // Continue reading without altering logic
    }

    // Check if the current brace is matched by the next
    if ((ch == '(' && nextch == ')') ||
        (ch == '[' && nextch == ']') ||
        (ch == '{' && nextch == '}') ||
        (ch == '<' && nextch == '>'))
    {
        return 1; // Pair matched
    }

    // Check for opening braces to process further
    if (nextch == '(' || nextch == '[' || nextch == '{' || nextch == '<')
    {
        return CheckBraces(nextch, b00l) && CheckBraces(ch, b00l);
    }

    // Unmatched or invalid brace
    return 0;
}

void task3ParenthesisValidator()
{
    char ch;
    int b00l;
    scanf(" %c", &ch);
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

void task4QueensBattle()
{
    // Todo
}

void task5CrosswordGenerator()
{
    // Todo
}
