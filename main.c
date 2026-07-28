#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "rps.h"

extern int isGameStarted;
extern int total_score;
extern int games_played;

int main(int argc, char const *argv[])
{
	int choice, result;
	MOVE vsm;
	char choice_in[2];
	char vsm_out[15];
	
	system("clear");

	do
	{

		Menu();

		do
		{
			ReadNum(choice_in, sizeof(choice_in), INT, &choice);

			if (choice < 0 || choice > 2)
			{
				printf("Invalid option, Try again: ");
			}

		} while (choice < 0 && choice > 2);

		if (isGameStarted == 0 && choice == 2)
		{
			printf("Game hasn't started yet, starting new game instead...\n\n\n");
		}
		

		switch (choice)
		{
		case 0:
			exit(EXIT_SUCCESS);
			break;

		case 1:
		isGameStarted = 1;
		games_played = 0;
		total_score = 0;
		
		case 2:
		
		printf("Enter: R for Rock\n       P for paper\n       S for scissors\n\n");
		result = PlayRound(&vsm);
		
		system("clear");

			switch (result)
			{
			case 1:
				total_score++;
				printf("You Won ! ");
				break;

			case 2:
				printf("Tie ! ");
				break;

			case 0:
				printf("You lose ! ");
				break;
	
			}
			
			switch (vsm)
			{
			case 1:
				strcpy(vsm_out, "Paper");
				break;

			case 2:
				strcpy(vsm_out, "Scissors");
				break;

			case 3:
				strcpy(vsm_out, "Rock");
				break;
			}

			printf("Computer played %s\n\n\n", vsm_out);
			
		default:
			break;
		}
		
	}while (choice != 0);
	
	return 0;
}
