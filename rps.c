#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <limits.h>
#include <stdint.h>
#include "rps.h"

int games_played = 0, total_score = 0;
int isGameStarted = 0;

void Menu()
{
	if (games_played == 0)
	{
		printf("Welcome to Rock Paper Scissors !\n\n");
	}
	
	printf("Total score: %d		Games Played: %d\n\n", total_score, games_played);
	printf("Enter \'1\' to start a new game			Enter \'2\' to play again		Enter \'0\' to exit\n\n");

}

MOVE GeneratePlay()
{
	unsigned int ran;
	FILE* random = fopen("/dev/urandom", "rb");

	if (random == NULL)
	{
		return -1;
	}
	

	fread(&ran, sizeof(ran), 1, random);
	ran = ran % 3 + 1;

	return ran;
}

MOVE GetPlay()
{
	char move;
	
	do
	{
		ReadChar(&move);
		move = UpperToLower(move);

		if (move != 'r' && move != 'p' && move != 's')
		{
			printf("Invalid option! Try again:\n");
		}
		
	} while (move != 'r' && move != 'p' && move != 's');
	
	switch (move)
	{
	case 'r':
		return ROCK;
		break;

	case 's':
		return SCISSORS;
		break;

	case 'p':
		return PAPER;
		break;
	}
}

int PlayRound(MOVE *computer_move)
{

	games_played++;

	MOVE comp = GeneratePlay();
	*computer_move = comp;
	MOVE player = GetPlay();

	if (comp == PAPER && player == ROCK)
	{
		return 0;
	}
	else if (comp == ROCK && player == PAPER)
	{
		return 1;
	}
	else if (comp == player)
	{
		return 2;
	}
	else
	{
		return (player > comp);
	}
	
	
}


void ReadNum(char *input, size_t size_of_input, TYPE type, void *var)
{
	long long tmp;
	unsigned long long tmp_u;
	double tmp_frac;

	while (1)
	{

		zero_out_arr(input, size_of_input);

		fgets(input, size_of_input, stdin);

		if (strchr(input, '\n') == NULL)
		{
			int c = getchar();
			if (c != '\n')
			{
				while ((c = getchar()) != '\n' && c != EOF);

				printf("Invalid input, the number you entered might be too large!\nTry again: ");
				continue;
			}
		}
		if (input[0] == '\0')
		{
			printf("Input can't be empty, try again: \n");
			continue;
		}
		
		char *endptr = NULL;
		errno = 0;

		switch (type)
		{
		case INT:

			tmp = strtoll(input, &endptr, 10);

			if (*endptr != '\0' && *endptr != '\n' && *endptr != '\n')
			{
				printf("Input contains Invalid characters for integers!\ntry again: ");
				continue;
			}

			if (errno == ERANGE || tmp > INT_MAX || tmp < INT_MIN)
			{
				printf("The number you entered is too large!\nTry again: ");
				continue;
			}

			*(int *)var = (int)tmp;

			break;

		case SIZET:

			if (input[0] == '-')
			{
				printf("Size_t must be a positive number\nTry again: ");
				continue;
			}

			tmp_u = strtoull(input, &endptr, 10);

			if (*endptr != '\0' && *endptr != '\n')
			{
				printf("Input contains Invalid characters for size_t!\ntry again: ");
				continue;
			}

			if (errno == ERANGE || tmp_u > SIZE_MAX)
			{
				printf("The number you entered is too large!\nTry again: ");
				continue;
			}

			*(size_t *)var = (size_t)tmp_u;

			break;

		case LONG:

			tmp = strtoll(input, &endptr, 10);

			if (*endptr != '\0' && *endptr != '\n')
			{
				printf("Input contains Invalid characters for longs!\ntry again: ");
				continue;
			}

			if (errno == ERANGE)
			{
				printf("The number you entered is too large!\nTry again: ");
				continue;
			}

			*(long *)var = (long)tmp;

			break;

		case FLOAT:

			tmp_frac = strtof(input, &endptr);

			if (*endptr != '\0' && *endptr != '\n')
			{
				printf("Input contains Invalid characters for floats!\ntry again: ");
				continue;
			}

			if (errno == ERANGE)
			{
				printf("The number you entered is too large!\nTry again: ");
				continue;
			}

			*(float *)var = (float)tmp_frac;

			break;

		case DOUBLE:

			tmp_frac = strtod(input, &endptr);

			if (*endptr != '\0' && *endptr != '\n')
			{
				printf("Input contains Invalid characters for doubles!\ntry again: ");
				continue;
			}

			if (errno == ERANGE)
			{
				printf("The number you entered is too large!\nTry again: ");
				continue;
			}

			*(double *)var = tmp_frac;

			break;
		default:

			printf("Type unavailable or unsupported\n");
			break;
		}

		break;
	}

}

char UpperToLower(char in)
{
	if ((in >= 'A' && in <= 'Z') || (in >= 'a' && in <= 'z'))
	{
		return in | 0x20;
	}
	else return 0;
	
}

void ReadChar(char *var)
{
	char input[2];
	
	while (1)
	{
		zero_out_arr(input, sizeof(input));
		fgets(input, sizeof(input), stdin);

		int c;
		if ((c =getchar()) != '\n')
		{
			printf("You must only enter one character !\nTry again: ");
			while((c = getchar()) != '\n' && c != EOF);

			continue;
		}
		
		break;
	}

	*var = input[0];
	
}