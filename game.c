#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "time.h"

#define LONG_STRING 100
#define SHORT_STRING  20

int MainMenu();
int SubMenu();
void registration();
int login();
int StartGaming();
int NumForDir();

//Login Structure
struct Login
{
  char fname[LONG_STRING];
  char lname[LONG_STRING];
  char username[SHORT_STRING];
  char password[SHORT_STRING];
};

//Definitions for Log in and Board
enum { LOGGED_OUT, LOGGED_IN, EXIT };

enum { NOUGHTS, CROSSES, BORDER, EMPTY };
enum { HUMANWIN, COMPWIN, DRAW };

const int Directions[4] = { 1, 5, 4, 6 };

const int ConvertTo25[9] = {
	6, 7, 8,
	11,12,13,
	16,17,18
};

const int InMiddle = 4;
const int Corners[4] = { 0, 2, 6, 8 };

int ply = 0;
int positions = 0;
int maxPly = 0;

//Main Function
int main() {
	int user_state = LOGGED_OUT;		
	
	srand(time(NULL));
	while (user_state!=EXIT)
	{
		if (user_state==LOGGED_OUT)
		{
			//User is not logged in Handle main menu
			user_state=MainMenu();
		}
		else
		{// user is logged in, handle sub menu
			user_state=SubMenu();
		}
	}
		
	return 0;
}

//Main Menu
int MainMenu()
{
  int choice;
  while ( 1 )
  {
    printf("Welcome to our tick tack toe game!!!\n");
    printf("\n");
    printf("\n1 : Register!!!\n");
    printf("2 : Login!!!\n");
    printf("3 : Quit\n");
    printf("Enter your choice : \n");

    if ( scanf("%d", &choice) == 1)
    {
      switch ( choice)
      {
      case 1:
        registration();
        break;
      case 2:
        if ( login())
          return LOGGED_IN;
        break;
      case 3:
        printf("Thank you for playing our tick tack toe game !! \n");
        return EXIT;
      default:
        printf("Invalid choice, please insert a valid number\n");
        break;
      }
    }
  }
}

//Sub Menu
int SubMenu()
{
  int choice;

  while ( 1 )
  {
    printf("\nGame Menu\n");

    printf("1 : Play Game\n");
    printf("2 : Main Menu\n");
    printf("Enter your choice : \n");
    if (scanf("%d", &choice)==1)
    {
      switch (choice)
      {
      case 1:
        StartGaming();
        break;
      case 2:
        return LOGGED_OUT;
        break;
        
      default:
        printf("Please enter a valid choice!!");
        break;
      }
    }
  }
}

//User Registration
void registration()
{
  FILE *log = fopen("login.txt", "a+");
  struct Login l;
  printf("\nEnter first name : ");
  scanf("%s", (l.fname));
  printf("\nEnter last name : ");
  scanf("%s", l.lname);
  printf("\nEnter your Username : ");
  scanf("%s", l.username);
  printf("\nEnter your password : ");
  scanf("%s", l.password);
  fwrite(&l, sizeof(l), 1, log);
  fclose(log);
  printf("\nYou are successfully registered!!");
  printf("\nYour UserId is %s and your password is %s", l.username, l.password);
  printf("\nNow login with your username and password!!");
  printf("\nPress any key to continue ...");
  getchar();
}

//User Login
int login()
{
  FILE *log;
  struct Login linput, lfile;
  log = fopen("login.txt", "r");
  if (log == NULL)
  {
    printf("FILE NOT FOUND!!!\n");
    return 0; // login failed
  }
  printf("\nUserID : ");
  scanf("%s", linput.username);
  printf("\nPassword : ");
  scanf("%s", linput.password);
  while ( fread(&lfile, sizeof(lfile), 1, log)  )
  {
    if (strcmp(linput.username, lfile.username) == 0
      && strcmp(linput.password, lfile.password)==0)
    {
      printf("\nYou are successfully logged in !!\n");
      fclose(log);
      return 1; // login succeeded
    }
  }
  printf("\nYour UserID or password is incorrect !!\n");
  printf("Press any key to continue ...\n");
  getchar();
  fclose(log);
  return 0; // login failed
}


int ThreeInRow(const int *board, const int ourindex, const int us) {

	int DirIndex = 0;
	int Dir = 0;
	int threeCount = 1;
	
	for(DirIndex = 0; DirIndex < 4; ++DirIndex) {
		Dir = Directions[DirIndex];
		threeCount += NumForDir(ourindex + Dir, Dir, board, us);
		threeCount += NumForDir(ourindex + Dir * -1, Dir * -1, board, us);
		if(threeCount == 3) {
			break;
		}
		threeCount = 1;
	}
	return threeCount;
}

//Three naughts/crosses in a row
int ThreeInRowAllBoard(const int *board, const int us) {
	int threeFound = 0;
	int index;
	for(index = 0; index < 9; ++index) {
		if(board[ConvertTo25[index]] == us) {
			if(ThreeInRow(board, ConvertTo25[index], us) == 3) {				
				threeFound = 1; 
				break;
			}
		}
	}	
	return threeFound;
}

//Evaluation for a win
int EvalForWin(const int *board, const int us) {

	if(ThreeInRowAllBoard(board, us) != 0)
		return 1;
	if(ThreeInRowAllBoard(board, us ^ 1) != 0)
		return -1;
	
	return 0;
}

int MinMax(int *board, int side) {

	// check is a win
	// gen all moves for side
	// loop moves, make move, mimax() on move to get score
	// assess bestscore
	// end moves return bestscore
	
	int MoveList[9];
	int MoveCount = 0;
	int bestScore = -2;
	int score = -2;
	int bestMove = -1;
	int Move;
	int index;
	
	if(ply > maxPly) maxPly = ply;	
	positions++;
	
	if(ply > 0) {
		score = EvalForWin(board, side);
		if(score != 0) {					
			return score;
		}		
	}
	
	// fill Move List
	for(index = 0; index < 9; ++index) {
		if( board[ConvertTo25[index]] == EMPTY) {
			MoveList[MoveCount++] = ConvertTo25[index];
		}
	}
	
	// loop all moves
	for(index = 0; index < MoveCount; ++index) {
		Move = MoveList[index];
		board[Move] = side;	
		
		ply++;
		score = -MinMax(board, side^1);
		if(score > bestScore) {			
			bestScore = score;	
			bestMove = Move;
		}
		board[Move] = EMPTY;
		ply--;
	}
	
	if(MoveCount==0) {
		bestScore = ThreeInRowAllBoard(board, side);	
	}
	
	if(ply!=0)
		return bestScore;	
	else 
		return bestMove;	
}

//Direction
int NumForDir(int startSq, const int dir, const int *board, const int us) {
	int found = 0;
	while(board[startSq] != BORDER) {		
		if(board[startSq] != us) {	
			break;
		}
		found++;	
		startSq += dir;
	}	
	return found;
}

//Initialize Board
void InitialiseBoard(int *board) {
	int index = 0;
	
	for(index = 0; index < 25; ++index) {
		board[index] = BORDER;
	}
	
	for(index = 0; index < 9; ++index) {
		board[ConvertTo25[index]] = EMPTY;
	}	
}

//PrintBoard
void BoardPrint(const int *board) {
	int index = 0;
	char pceChars[] = "OX|-";	
	
	printf("\n\nBoard:\n\n");
	for(index = 0; index < 9; ++index) {
		if(index!=0 && index%3==0) {
			printf("\n\n");
		}
		printf("%4c",pceChars[board[ConvertTo25[index]]]);
	}
	printf("\n");
}

int HasEmpty(const int *board) {
	int index = 0;
	
	for(index = 0; index < 9; ++index) {
		if( board[ConvertTo25[index]] == EMPTY) return 1;
	}
	return 0;
}


int NextBest(const int *board) {

	int ourMove = ConvertTo25[InMiddle];
	if(board[ourMove] == EMPTY) {
		return ourMove;
	}
	
	int index = 0;
	ourMove = -1;
	
	for(index = 0; index < 4; index++) {
		ourMove = ConvertTo25[Corners[index]];
		if(board[ourMove] == EMPTY) {
			break;
		}
		ourMove = -1;
	}
	
	return ourMove;
}

//Make a move
void MakeMove(int *board, const int sq, const int side) {
	board[sq] = side;
}

//Computer Move
int ComputerMove(int *board, const int side) {
	
	ply=0;
	positions=0;
	maxPly=0;
	int best = MinMax(board, side);
	printf("Finished Searching positions:%d maxDepth:%d bestMove:%d\n",positions,maxPly,best);
	return best;
	
}

//HumanMove
int HumanMove(const int *board) {
	
    char userInput[64];
	
	int moveOk = 0;
	int move = -1;
	
	while (moveOk == 0) {
	
		printf("Please enter a move from 1 to 9:");	
		if(!fgets(userInput, 64, stdin)) continue;
		
		if(strlen(userInput) != 2) {
			continue;			
		}
		
		if( sscanf(userInput, "%d", &move) != 1) {
			move = -1;
			printf("Invalid sscanf()\n");
			continue;
		}
		
		if( move < 1 || move > 9) {
			move = -1;
			printf("Invalid range\n");
			continue;
		}
		
		move--; // Zero indexing
		
		if( board[ConvertTo25[move]]!=EMPTY) {
			move=-1;
			printf("Square not available\n");
			continue;
		}
		moveOk = 1;
	}
	printf("Making Move...%d\n",(move+1));
	return ConvertTo25[move];
}

//Winning Move
int WinningMove(int *board, const int side) {

	int ourMove = -1;
	int winFound = 0;
	int index = 0;
	
	for(index = 0; index < 9; ++index) {
		if( board[ConvertTo25[index]] == EMPTY) {
			ourMove = ConvertTo25[index];
			board[ourMove] = side;
			
			if(ThreeInRow(board, ourMove, side) == 3) {
				winFound = 1;
			}	
			board[ourMove] = EMPTY;
			if(winFound == 1) {
				break;
			}
			ourMove = -1;
		};
	} 
	return ourMove;
}


//Starts the game
int StartGaming() {

	int GameOver = 0;
	int Side = CROSSES;
	int LastMoveMade = 0;
	int board[25];
	
	InitialiseBoard(&board[0]);
	BoardPrint(&board[0]);
	
	while(!GameOver) {
		if(Side==NOUGHTS) {	
			LastMoveMade = HumanMove(&board[0]);
			MakeMove(&board[0],LastMoveMade,Side);
			Side=CROSSES;
		} else {
			LastMoveMade = ComputerMove(&board[0], Side);
			MakeMove(&board[0],LastMoveMade,Side);
			Side=NOUGHTS;
			BoardPrint(&board[0]);
		}
		
		// if three in a row exists Game is over
		if( ThreeInRow(board, LastMoveMade, Side ^ 1) == 3) {
			printf("Game over!\n");
			GameOver = 1;
			if(Side==NOUGHTS) {
				printf("Computer Wins\n");
			} else {
				printf("Human Wins\n");
			}
		}	
		
		// if no more moves, game is a draw	
		if(!HasEmpty(board)) {
			printf("Game over!\n");
			GameOver = 1;
			printf("It's a draw\n");
		}
	}
	
	
	BoardPrint(&board[0]);
}


