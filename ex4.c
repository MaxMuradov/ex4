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

void task2HumanPyramid()
{
    // Todo
}

int CheckBraces(char ch, int b00l)
{
    char nextch;
    scanf(" %c", &nextch);

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
    scanf(" %*c", &ch);
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
