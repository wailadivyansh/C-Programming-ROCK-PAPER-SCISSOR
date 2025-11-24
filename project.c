#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

char *moves[] = {"STONE", "PAPER", "SCISSOR"};

int score[2] = {0, 0};
int *you_point = &score[0];
int *comp_point = &score[1];

int game(char you, char computer)
{
    if (you == computer)
        return -1;

    if (you == 's' && computer == 'p')
        return 0;
    else if (you == 'p' && computer == 's')
        return 1;

    if (you == 's' && computer == 'z')
        return 1;
    else if (you == 'z' && computer == 's')
        return 0;

    if (you == 'p' && computer == 'z')
        return 0;
    else if (you == 'z' && computer == 'p')
        return 1;

    return -1;
}

int main()
{
    FILE *file;
    file = fopen("game_log.txt", "a");  
    if (file == NULL)
    {
        printf("Error opening file!\n");
        return 1;
    }

    char play_again;
    int n;
    char you, computer, result;

    do
    {
        srand(time(NULL));
        n = rand() % 100;

        if (n < 33)
            computer = 's';
        else if (n >= 33 && n < 66)
            computer = 'p';
        else
            computer = 'z';

        printf("\n\n\n\n\t\t\tEnter s for STONE, p for PAPER and z for SCISSOR\n\t\t\t\t\t");
        scanf(" %c", &you);

        result = game(you, computer);

        if (result == -1)
        {
            printf("\n\n\t\t\tGame Draw!\n");
            fprintf(file, "Round: Draw (You: %c, Computer: %c)\n", you, computer);
        }
        else if (result == 1)
        {
            printf("\n\n\t\t\tYou WON!\n");
            (*you_point)++;
            fprintf(file, "Round: You WON (You: %c, Computer: %c)\n", you, computer);
        }
        else
        {
            printf("\n\n\t\t\tYou LOST!\n");
            (*comp_point)++;
            fprintf(file, "Round: You LOST (You: %c, Computer: %c)\n", you, computer);
        }

        int you_index = (you == 's' ? 0 : you == 'p' ? 1 : 2);
        int comp_index = (computer == 's' ? 0 : computer == 'p' ? 1 : 2);

        printf("\t\tYou chose : %s | Computer chose : %s\n",
               moves[you_index], moves[comp_index]);

        printf("\n\t\t-----------------------\n");
        printf("\t\t|---- SCOREBOARD ----|\n");
        printf("\t\t| YOU = %d | COMPUTER = %d |\n", *you_point, *comp_point);
        printf("\t\t-----------------------\n");

        printf("Do you want to play again?\n");
        printf("Enter (Y/y) for YES and (N/n) for NO: ");
        scanf(" %c", &play_again);

    } while (play_again == 'Y' || play_again == 'y');

    
    fprintf(file, "\nFINAL SCORE => YOU: %d | COMPUTER: %d\n", *you_point, *comp_point);
    fprintf(file, "--------------------------------------\n\n");

    fclose(file);

    printf("\n\t\t----- FINAL SCOREBOARD -----\n");
    printf("\t\tYOU = %d | COMPUTER = %d\n", *you_point, *comp_point);
    printf("\t\tThanks for playing!\n");

    return 0;
}
