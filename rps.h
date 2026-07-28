#ifndef RPC
#define RPC

typedef enum TYPE
{
	CUSTOM_STRUCT = -1,
	STATIC_DATA = -2,
	INT = 0,
	SIZET = 1,
	LONG = 2,
	FLOAT = 3,
	DOUBLE = 4,
	CHAR = 5,
	STRING = 6,
}TYPE;

typedef enum MOVE
{
	PAPER = 1,
	SCISSORS = 2,
	ROCK = 3,
}MOVE;

void Menu();
MOVE GeneratePlay();
MOVE GetPlay();
void ReadNum(char *input, size_t size_of_input, TYPE type, void *var);
static inline void zero_out_arr(void *ptr, size_t size)
{
	volatile unsigned char* t = ptr;
	while(size--) *t++ = 0;
}

char UpperToLower(char in);
int PlayRound(MOVE *computer_move);
void ReadChar(char *var);
static inline void ClearInputBuffer()
{
	int c;
	while((c = getchar()) != '\n' && c != EOF);
}

#endif