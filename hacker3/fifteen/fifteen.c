/**
 * fifteen.c
 *
 * Computer Science 50
 * Problem Set 3
 *
 * Implements the Game of Fifteen (generalized to d x d).
 *
 * Usage: ./fifteen d
 *
 * whereby the board's dimensions are to be d x d,
 * where d must be in [MIN,MAX]
 *
 * Note that usleep is obsolete, but it offers more granularity than
 * sleep and is simpler to use than nanosleep; `man usleep` for more.
 */
 
#define _XOPEN_SOURCE 500

#include "/users/wojtekswiderski/documents/cs50/library50-c-5/cs50.c"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

// board's minimal dimension
#define MIN 3

// board's maximal dimension
#define MAX 9

// board, whereby board[i][j] represents row i and column j
int board[MAX][MAX];
int blank[2];

// board's dimension
int d;

// prototypes
void clear(void);
void greet(void);
void init(void);
void draw(void);
bool move(int tile);
bool won(void);
void save(void);

int main(int argc, string argv[])
{
    // greet player
    greet();

    // ensure proper usage
    if (argc != 2)
    {
        printf("Usage: ./fifteen d\n");
        return 1;
    }

    // ensure valid dimensions
    d = atoi(argv[1]);
    if (d < MIN || d > MAX)
    {
        printf("Board must be between %i x %i and %i x %i, inclusive.\n",
            MIN, MIN, MAX, MAX);
        return 2;
    }
    // initialize the board
    init();
	
	// initializing code to work with god mode
	/*int god = 0;
	int goal[d][d];
	int count = 1;
	for(int i = 0; i < d; i++)
	{
		for(int j = 0; j < d; j++)
		{
			if(count == d * d)
			{
				count = 0;
			}
			goal[i][j] = count;
			count++;
		}
	}*/

    // accept moves until game is won
    while (true)
    {
        // clear the screen
        clear();

        // draw the current state of the board
        draw();

        // saves the current state of the board (for testing)
        save();

        // check for win
        if (won())
        {
            printf("ftw!\n");
            break;
        }

        // prompt for move
        printf("Tile to move: ");
		int tile;
		
		tile = GetInt();
		
		// broken god mode
		/*int last;
		int flag = 0;
		while(flag == 0)
		{
			if(god == 0)
			{
				char* input = GetString();
				if(strcmp(input, "GOD") == 0)
				{
					god = 1;
					tile = 0;
					flag++;
				}
				else if(atoi(input) > 0)
				{
					tile = atoi(input);
					flag++;
				}
				else
				{
					printf("Retry: ");
				}
			}
			else
			{
				int tmp[d][d];
				int sits[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
				int priority[4];
				int changed[4];
				for(int i = 0; i < 4; i++)
				{
					priority[i] = 0;
					changed[i] = 0;
					if(blank[0] + sits[i][0] > -1 && blank[0] + sits[i][0] < d && blank[1] + sits[i][1] > -1 && blank[1] + sits[i][1] < d)
					{
						for(int j = 0; j < d; j++)
						{
							for(int k = 0; k < d; k++)
							{
								tmp[j][k] = board[j][k];
							}
						}
						changed[i] = tmp[blank[0] + sits[i][0]][blank[1] + sits[i][1]];
						if(changed[i] == last)
						{
							priority[i] = priority[i] + 3;
						}
						int temp = tmp[blank[0]][blank[1]];
						tmp[blank[0]][blank[1]] = tmp[blank[0] + sits[i][0]][blank[1] + sits[i][1]];
						tmp[blank[0] + sits[i][0]][blank[1] + sits[i][1]] = temp;
						for(int j = 0; j < d; j++)
						{
							for(int k = 0; k < d; k++)
							{
								for(int l = 0; l < d; l++)
								{
									for(int m = 0; m < d; m++)
									{
										if(goal[j][k] == tmp[l][m] && goal[j][k] > 0)
										{
											priority[i] = abs(j - l) + abs(k - m) + priority[i];
										}
									}
								}
							}
						}
					}
				}
				int sorted = 0;
				do
				{
					sorted = 0;
					for(int i = 0; i < 4 - 1; i++)
					{
						if(priority[i] > priority[i + 1])
						{
							int temp = priority[i];
							priority[i] = priority[i + 1];
							priority[i + 1] = temp;
							int temp1 = changed[i];
							changed[i] = changed[i + 1];
							changed[i + 1] = temp1;
							sorted++;
						}
					}
				}
				while(sorted != 0);
				for(int i = 0; i < 4; i++)
				{
					if(priority[i] != 0)
					{
						tile = changed[i];
						last = changed[i];
						break;
					}
				}
				flag++;
			}
		}*/
        
        // move if possible, else report illegality
        if (!move(tile))
        {
            printf("\nIllegal move.\n");
            usleep(500000);
        }

        // sleep for animation's sake
        usleep(250000);
    }

    // that's all folks
    return 0;
}

/**
 * Clears screen using ANSI escape sequences.
 */
void clear(void)
{
    printf("\033[2J");
    printf("\033[%d;%dH", 0, 0);
}

/**
 * Greets player.
 */
void greet(void)
{
    clear();
    printf("GAME OF FIFTEEN\n");
    usleep(2000000);
}

/**
 * Initializes the game's board with tiles numbered 1 through d*d - 1,
 * (i.e., fills board with values but does not actually print them),
 * whereby board[i][j] represents row i and column j.
 */
void init(void)
{
	int count = (d * d) - 1;
	for(int i = 0; i < d; i++)
	{
		for(int j = 0; j < d; j++)
		{
			board[i][j] = count;
			count--;
			
		}
	}
	if((d * d) % 2 == 0)
	{
		int temp = board[d - 1][d - 2];
		board[d - 1][d - 2] = board[d - 1][d - 3];
		board[d - 1][d - 3] = temp;
	}
	for(int i = 0; i < 2; i++)
	{
		blank[i] = d - 1;
	}
	
	// randomizes the board
	srand((unsigned int) time(NULL));
	for(int i = 0; i < 100 * d * d; i++)
	{
		int number = rand() % (d * d);
		if(!move(number))
		{
			i--;
		}
	}
}

/**
 * Prints the board in its current state.
 */
void draw(void)
{
	for(int i = 0; i < d; i++)
	{
		for(int j = 0; j < d; j++)
		{
			if(board[i][j] == 0)
			{
				printf("%2c   ", '_');
			}
			else
			{
				printf("%2i   ", board[i][j]);
			}
		}
		printf("\n\n");
	}
}

/**
 * If tile borders empty space, moves tile and returns true, else
 * returns false. 
 */
bool move(int tile)
{
	if(board[blank[0]][blank[1] + 1] == tile && blank[1] + 1 < d)
	{
		int temp = board[blank[0]][blank[1]];
		board[blank[0]][blank[1]] = board[blank[0]][blank[1] + 1];
		board[blank[0]][blank[1] + 1] = temp;
		blank[1]++;
		return true;
	}
	else if(board[blank[0]][blank[1] - 1] == tile && blank[1] - 1 > -1)
	{
		int temp = board[blank[0]][blank[1]];
		board[blank[0]][blank[1]] = board[blank[0]][blank[1] - 1];
		board[blank[0]][blank[1] - 1] = temp;
		blank[1]--;
		return true;
	}
	else if(board[blank[0] + 1][blank[1]] == tile && blank[0] + 1 < d)
	{
		int temp = board[blank[0]][blank[1]];
		board[blank[0]][blank[1]] = board[blank[0] + 1][blank[1]];
		board[blank[0] + 1][blank[1]] = temp;
		blank[0]++;
		return true;
	}
	else if(board[blank[0] - 1][blank[1]] == tile && blank[0] - 1 > -1)
	{
		int temp = board[blank[0]][blank[1]];
		board[blank[0]][blank[1]] = board[blank[0] - 1][blank[1]];
		board[blank[0] - 1][blank[1]] = temp;
		blank[0]--;
		return true;
	}
	else
	{
		return false;
	}
}

/**
 * Returns true if game is won (i.e., board is in winning configuration), 
 * else false.
 */
bool won(void)
{
    int count = 1;
	for(int i = 0; i < d; i++)
	{
		for(int j = 0; j < d; j++)
		{
			if(board[i][j] == count)
			{
				count++;
			}
			else if(count == d * d)
			{
				return true;
			}
			else
			{
				return false;
			}
		}
	}
	return false;
}

/**
 * Saves the current state of the board to disk (for testing).
 */
void save(void)
{
    // log
    const string log = "log.txt";

    // delete existing log, if any, before first save
    static bool saved = false;
    if (!saved)
    {
        unlink(log);
        saved = true;
    }

    // open log
    FILE* p = fopen(log, "a");
    if (p == NULL)
    {
        return;
    }

    // log board
    fprintf(p, "{");
    for (int i = 0; i < d; i++)
    {
        fprintf(p, "{");
        for (int j = 0; j < d; j++)
        {
            fprintf(p, "%i", board[i][j]);
            if (j < d - 1)
            {
                fprintf(p, ",");
            }
        }
        fprintf(p, "}");
        if (i < d - 1)
        {
            fprintf(p, ",");
        }
    }
    fprintf(p, "}\n");

    // close log
    fclose(p);
}
