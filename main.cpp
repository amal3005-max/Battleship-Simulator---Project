#include<iostream>
#include<windows.h>
#include<cstdlib>
#include<fstream>
#include<ctime>
#include<conio.h>
#include<string>
using namespace std;



// FUNCTION PROTOTYPES
void showmainmenu();
void instructions();
void startnewgame();
void showLeaderboard(const string playerName, const int scores[], int totalPlayers);
void clearScreen();
void setColor(int textColor, int bgColor);
void setRandomShips(char board[10][10]);
void setManualShips(char board[10][10]);
void printBoard(char board[10][10], bool hideShips);
void initializeBoard(char board[10][10]);
void clearBoard(char board[10][10]);
void updateScore(int &score);
void combineBoard(char enemyView[10][10],char computerBoard[10][10],char playerBoard[10][10],bool hideShips);
bool allShipsDestroyed(char board[10][10]);
void displayResult(int player1Score, int player2Score);


void vsComputer(char playerBoard[10][10],char computerBoard[10][10]);
void computerAttack(char playerBoard[10][10], int &computerScore);
void playerAttack(char opponentBoard[10][10], int &playerScore);

// ====================================================
// global variables
int shipColor=6;
string playerName;
int scores[100];
int totalPlayers = 0; 
char computerBoard[10][10];
char playerBoard[10][10];
char playerboard1[10][10];
char playerboard2[10][10];


// =====================================================
// MAIN
int main()
{
	srand(time(0));
	showmainmenu();
	return 0;
}

//======================================================
// CLEAR SCREEN
void clearScreen()
{
    system("CLS");
}

// =====================================================
// SET COLOR
void setColor(int textColor, int bgColor) 
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, (bgColor << 4) | textColor);
}

// =====================================================
// ---------------- COLOR CONSTANTS ----------------
const int BLACK = 0;
const int BLUE = 1;
const int GREEN = 2;
const int CYAN = 3;
const int RED = 4;
const int MAGENTA = 5;
const int YELLOW = 6;
const int WHITE = 7;

// =====================================================

// INITIALIZE BOARD
void initializeBoard(char board[10][10]) 
{
    for(int i=0;i<10;i++)
    {
	    for(int j=0;j<10;j++)
        {
		    board[i][j]='~';
		}
	}
}

//======================================================
// print board
void printBoard(char board[10][10], bool hideShips)
{
	// Print column headers
	cout<<"     0    1    2    3    4    5    6    7    8    9  "<<endl;
	//TOP BORDER
    cout << "    +-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+" << endl;
	//rows
    for(int i=0;i<10;i++)
    {
        cout<<"  "<<i<<" ¦";

        for(int j=0;j<10;j++)
        {
            char cell=board[i][j];

            //hiding ships
            if(hideShips&&(cell=='S'||cell=='A'||cell=='B'||cell=='D'||cell=='P'))
			{
    			cell = '~';
			}
			
            //colors
            if(cell=='~')
            {
                setColor(7,1);      //WATER 
	        }
			else if(cell=='X')
            {
			    setColor(15,12);    //HIT
            }
			else if(cell=='O')
            {
			    setColor(0,8);      //MISS
            }
			else if(cell=='S')
            {
			    setColor(0,shipColor);      //SHIP
			}
			else if(cell=='Z')
			{
				setColor(15,5);
			}
		
            cout<<"  "<<cell<<"  ";

            setColor(7,0);
            cout << "¦";
        }
        cout<<endl;
        //BOTTOM BORDER
        cout<<"    +-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+"<<endl;
    }
}
 
//========================================================================
// Clear board
void clearBoard(char board[10][10]) 
{
    for(int i=0;i<10;i++) 
	{
        for(int j=0;j<10;j++) 
		{
            board[i][j]='~';
        }
    }
}


// =====================================================
// MAIN MENU
void showmainmenu()
{
    int choice;

    while (true)
    {
        clearScreen();
        cout<<"============================================\n"<<endl;
        cout<<"\tWELCOME TO BATTLESHIP GAME\n"<<endl;
        cout<<"============================================\n"<<endl;
        cout<<"\t\tMAIN MENU\n"<<endl;
        cout<<"--------------------------------------------\n"<<endl;

        setColor(RED, BLACK);
        cout<<"1. ";
        setColor(WHITE, BLACK);
        cout<<"Start New Game "<<endl;

        setColor(RED, BLACK);
        cout<<"2. ";
        setColor(WHITE, BLACK);
        cout<<"Instructions "<<endl;

        setColor(RED, BLACK);
        cout<<"3. ";
        setColor(WHITE, BLACK);
        cout<<"View Leaderboard "<<endl;

        setColor(RED, BLACK);
        cout<<"4. ";
        setColor(WHITE, BLACK);
        cout<<"Exit \n"<<endl;

        cout<<"--------------------------------------------\n"<<endl;

        cout<<"Enter your choice (1-4): ";
        cin>>choice;

        switch(choice)
        {
        case 1:
            startnewgame();
            break;
        case 2:
            instructions();
            
            break;
        case 3:
			showLeaderboard(playerName,scores,totalPlayers);
            break;
        case 4:
            clearScreen();
            cout<<"Exiting game..."<<endl;
            return;
        default:
            cout<<"\nInvalid choice! Press any key ..."<<endl;
            getch();
        }
    }
}
//=========================================================================
//START NEW GAME
void startnewgame()
{
    clearScreen();
    cout<<"--------------------------------------------"<<endl;
    cout<<"\t\tSTART NEW GAME\n";
    cout<<"--------------------------------------------\n"<<endl;

    cout<<"Enter Player Name: ";
    cin.ignore();
	getline(cin, playerName);

    cout<<"\nChoose your Battleship Color: "<<endl;
    cout<<"1. Blue \n2. Green \n3. Cyan \n4. Red \n5. Magenta \n6. Yellow"<<endl;
    
    cout<<"\nEnter choice: ";
    cin>>shipColor;
    cout<<"\nPlayer "<<playerName<<" color saved! "<<endl;
	
	
	clearScreen();
	cout<<"--------------------------------------------\n";
	cout<<"\n\t\tSelect Game Mode "<<endl;
	cout<<"--------------------------------------------\n"<<endl;
	setColor(RED, BLACK); 
	cout<<"1. "; 
	setColor(WHITE, BLACK); 
	cout<<" Player vs Computer "<<endl; 
	
	
	/*setColor(YELLOW, BLACK); 
	cout<<"2. "; 
	setColor(YELLOW, BLACK); 
	cout<<" Player vs Player \n"<<endl; */
	
	int mode;
	cout<<"\nEnter Choice : ";
	cin>>mode;
	switch(mode)
	{
		case 1:
			vsComputer(playerBoard, computerBoard);
			break;
		
		/* case 2:
			vsPlayer(playerboard1, playerboard2);
			break; */
		default:
			cout<<"Invalid Choice ! "<<endl;
	}
    cout<<"\nPress any key to return to Main Menu..."<<endl;
    getch();
}

// =====================================================
// SHOW LEADERBOARD
void showLeaderboard(const string playerName, const int scores[], int totalPlayers)
{
    clearScreen();
    cout<<"-------------------------------------------- "<<endl;
    cout<<"\t\tLEADERBOARD "<<endl;
    cout<<"--------------------------------------------\n"<<endl;
	//Reading
    string names[100];
    int scr[100];
    int count=0;

    ifstream rfile("highscores.txt");
    if(rfile.is_open())
    {
        while(rfile>>names[count]>>scr[count])
        {
            count++;
        }
        rfile.close();
	}
    if(totalPlayers>0)
    {
        names[count]=playerName;
        scr[count]=scores[totalPlayers-1];
        count++;
	}
    //Sorting
    for(int i=0;i<count-1;i++)
    {
        for(int j=i+1;j<count;j++)
        {
            if(scr[j]>scr[i])
            {
            	int stemp=scr[j];
				scr[j]=scr[i];
				scr[i]=stemp;
				string ntemp=names[j];
				names[j]=names[i];
				names[i]=ntemp;
            }
        }
    }
    //Top 10
    int limit;
	if (count>10)
    {
    	limit=10;
	}
	else
	{
		limit=count;
	}
    //Displaying
    cout<<" RANK\tNAME\tSCORE"<<endl;
    cout<<"-----------------------------------"<<endl;
    for(int i=0;i<limit;i++)
    {
        cout<<"  "<<i+1<<"\t"<<names[i]<<"\t"<<scr[i]<<endl;
    }
    ofstream wfile("highscores.txt");
    for(int i=0;i<limit;i++)
    {
        wfile<<names[i]<<" "<<scr[i]<<endl;
    }
    wfile.close();
    if(count==0) 
	{
    	cout<<"No high scores yet!"<<endl;
	}
    cout<<"Press any key to return to Main Menu..."<<endl;
    getch();
}

// =====================================================
// INSTRUCTIONS
void instructions()
{
    clearScreen();
    
    cout<<"--------------------------------------------"<<endl;
    cout<<"\t\tINSTRUCTIONS "<<endl;
    cout<<"--------------------------------------------\n"<<endl;
    
    setColor(RED, BLACK); 
	cout<<"1. "; 
	setColor(WHITE, BLACK); 
	cout<<" Place your ships on the board. "<<endl; 
	
	setColor(RED, BLACK); 
	cout<<"2. "; 
	setColor(WHITE, BLACK); 
	cout<<" You and the computer take turns firing shots. "<<endl; 
	
	setColor(RED, BLACK); 
	cout<<"3. "; 
	setColor(WHITE, BLACK); 
	cout<<" 'O' means MISS, 'X' means HIT. "<<endl; 
	
	setColor(RED, BLACK);
	cout<<"4. "; 
	setColor(WHITE, BLACK); 
	cout<<" Sink all enemy ships to win! "<<endl; 
	
	cout<<"5. Your score is based on acuracy and speed. \n"<<endl;
    
    cout<<"(Press any key to return to Main Menu...)";
    getch();
}
//===========================================================

// SET MANUAL SHIPS
void setManualShips(char board[10][10])
{	
	int shipSizes[5]={5,4,3,3,2};
		
	for(int i=0;i<5;i++) 
	{  
		clearScreen();
		int size=shipSizes[i]; 
		char shipChar='S';
		bool placed=false; 
		while(!placed)
		{
			
			cout<<"You have 1 ship of size "<<size<<" to place."<<endl;
			cout<<"Your Board:"<<endl;
			printBoard(board,false);

			int row,col;
			cout<<"Enter starting row (0-9): ";
			cin>>row;
			cout<<"Enter starting column (0-9): ";
			cin>>col;
			
			if(row<0||row>9||col<0||col>9)
			{
				clearScreen();
				cout<<"Invalid position input! Enter again."<<endl;
				continue;
			}
			
			bool valid=true;
			
			if(col+size>10) //horizontal check
			{
				clearScreen();
				cout<<"Error! ship cannot fit horizontally. "<<endl;
				valid=false;
			} 
			else //overlapping check
			{
				for(int j=0;j<size;j++)
				{
					if(board[row][col+j]!='~') 
					{
						clearScreen();
						cout<<"Error! Ships are overlapping."<<endl;
						valid=false;
						break;
					}
				}
			}
			if(valid) 
			{
				for(int j=0;j<size;j++) 
				{
					board[row][col+j]=shipChar;
				}
				clearScreen();
				cout<<"\n=== Updated Board ==="<<endl;
				printBoard(board,false);
				
				bool validchoice=false;
				while(!validchoice)
				{
				cout<<"Choose one option (1-2): "<<endl;
				cout<<"1.Rotate it to vertical."<<endl;
				cout<<"2.Move to place next ship. "<<endl;
				int choice;
				cin>>choice;
				if(choice==1)
				{
					validchoice=true;
					for(int j=0;j<size;j++) 
					{
						board[row][col+j]='~';
					}
					bool valid=true;
			
					if(row+size>10) //vertical check
					{
						clearScreen();
						cout<<"Error! ship cannot fit vertically. "<<endl;
						valid=false;
					} 
					else
					{
						for(int j=0;j<size;j++)
						{
							if(board[row+j][col]!='~') 
							{
								clearScreen();
								cout<<"Error! Ships are overlapping."<<endl;
								valid=false;
								break; 
							} 
						} 
					} 
					if(valid) 
					{
						for(int j=0;j<size;j++) 
						{
							board[row+j][col]=shipChar;
						}
						placed=true;
						if(size==2)
						{
							clearScreen();
							cout<<"\n=== Updated Board ==="<<endl;
							printBoard(board,false);
						}
					}
					else
					{
						for(int j=0;j<size;j++)
           				{
							board[row][col+j]=shipChar;
						}
						cout<<"Keeping ship horizontal.\n"<<endl;
						printBoard(board, false);
						placed=true;
						bool wrong=false;
						while(!wrong)
						{
							int again;
							cout<<"Do you want to place it again (1.Yes 2.No): ";
							cin>>again;
							if (again==1)
							{
								for(int j=0;j<size;j++)
    	        				{
									board[row][col+j]='~';
								}
								placed=false;
								wrong=true;
								continue;
							}
							else if(again==2)
							{
								placed=true;
								wrong=true;
								continue;
							}
							else 
							{
								cout<<"Invalid input! press any key..."<<endl;
								getch();
							}
						}
					}	
				}
				else if(choice==2)
				{
					validchoice=true;
					placed=true;
					printBoard(board,false);
					break;
				}
				else
				{
					cout<<"invalid input! "<<endl;
					for(int j=0;j<size;j++)
           			{
						board[row][col+j]=shipChar;
					}
					getch();
				}
				}
			}
		}	
	}
	cout<<"\n================================"<<endl;
	cout<<"Player board ready! "<<endl;
}

//=====================================================
// Randomships
void setRandomShips(char board[10][10])
{
	int shipSizes[5]={5,4,3,3,2};
	for(int i=0;i<5;i++) 
	{  
		int row; 
		int col; 
		char shipChar='S';
		int size=shipSizes[i]; 
		bool placed=false; 
		int orientation;
		while(!placed)
		{
			row=rand()%10; 
			col=rand()%10; 
			orientation=rand()%2; 
		
			bool valid=true;
			if(orientation==0) 
			{
				if(col+size>10) 
				{
					valid=false; 
				} 
				else 
				{
					for(int j=0;j<size;j++)
					{
						if(board[row][col+j]!='~') 
						{
							valid=false;
							break; 
						} 
					} 
				} 
				if(valid) 
				{
					for(int j=0;j<size;j++) 
					{
						board[row][col+j]=shipChar;
					}
					placed=true;
				}
			}
			else 
			{
				if(row+size>10) 
				{
					valid=false;
				}
				else 
				{
					for(int j=0;j<size;j++) 
					{
						if(board[row+j][col]!='~')
						{
							valid=false;
							break; 
						} 
					} 
				} 
				if (valid) 
				{
					for(int j=0;j<size;j++) 
					{
						board[row+j][col]=shipChar;
					}
					placed=true; 
				}
			} 
		}
	}
}

// ========================================================
// ========================================================
// VS COMPUTER
void vsComputer(char playerBoard[10][10],char computerBoard[10][10])
{

    clearScreen();
    cout<<"==============================="<<endl;
    cout<<"\tBATTLESHIP GAME "<<endl;
    cout<<"===============================\n"<<endl;
    cout<<"Press any key to start player vs computer...";
    getch();

	initializeBoard(playerBoard);
	initializeBoard(computerBoard);
	
	int placement;
	
	while (true)
	{
   		clearScreen();
    	cout<<"YOUR BOARD"<<endl;
    	printBoard(playerBoard,false);
	
    	cout<<"Choose placement Option: "<<endl;
    	setColor(RED,BLACK);
    	cout<<"1. ";
    	setColor(WHITE,BLACK);
    	cout<<"Manual"<<endl;

    	setColor(RED,BLACK);
    	cout<<"2. ";
	    setColor(WHITE,BLACK);
    	cout<<"Random"<<endl;

    	cin>>placement;

    	if(placement==1)
    	{
        	setManualShips(playerBoard);  
        	clearScreen();
        	printBoard(playerBoard,false);
        	cout<<"\n==PLAYER BOARD READY=="<<endl;
        	break;
    	}
    	else if(placement==2)
    	{
        	setRandomShips(playerBoard);
        	clearScreen();
        	printBoard(playerBoard,false);

        	int choice;
        	while(true)
        	{
            	cout<<"Do you want to place again ? "<<endl;
            	cout<<"1. Random "<<endl;
            	cout<<"2. Manual "<<endl;
            	cout<<"3. keep placement"<<endl;
            	cout<<"\nEnter Your Choice : ";
            	cin>>choice;

            	if(choice==1)
            	{
                	clearBoard(playerBoard);
                	setRandomShips(playerBoard);
                	clearScreen();
                	printBoard(playerBoard,false);
            	}
            	else if(choice==2)
            	{
            		clearBoard(playerBoard);
            		setManualShips(playerBoard);
            		break;
				}
            	else if(choice==3)
            	{
            		break;
            	}
            	else
            	{
                	cout<<"Invalid input! Press any key..."<<endl;
                	getch();
            	}
        	}
        	cout<<"\n === PLAYER BOARD READY ==="<<endl;
        	break;
    	}
    	else
    	{
        	cout<<"Invalid placement chosen! (Press any key...)";
        	getch();
    	}
	}

	setRandomShips(computerBoard);
	cout<<"=== COMPUTER BOARD READY ==="<<endl;
	cout<<"(Press any key to start attack...)"<<endl;
	getch();
	clearScreen();
	bool gameOver=false;
	int playerScore=0;
	int computerScore=0;
	int turn=1;

	while (!gameOver)
	{
    	clearScreen();
    	cout<<"--------------------------------------"<<endl;
    	cout<<"\t\t\t\tTURN "<<turn<<endl;
    	cout<<"--------------------------------------\n"<<endl;    
    	cout<<"=== YOUR TURN (6 shots) ==="<<endl;
    	for(int i=1;i<=6;i++)
    	{
    		clearScreen();
        	cout<<"\n=== Shot "<<i<<" of 6 ==="<<endl;
        	playerAttack(computerBoard, playerScore);
       		cout<<"Press any key..."<<endl;
        	getch();
        	
        	if(allShipsDestroyed(computerBoard))
			{
    			//cout<<"\nYOU WIN! All enemy ships destroyed!"<<endl;
    			//cout<<"Final Score: "<<playerScore<<endl;
    			gameOver = true;
    			break;
			}
    	}	
    	cout<<"\n=== COMPUTER'S TURN (6 shots) ==="<<endl;
    	for(int i=1;i<=6;i++)
    	{
        	cout<<"\n=== Computer's Shot "<<i<<" of 6 ==="<<endl;
        	computerAttack(playerBoard, computerScore);
        	if(allShipsDestroyed(playerBoard))
			{
    			//cout<<"\nYOU LOSE! All your ships are destroyed!"<<endl;
   	 			//cout<<"Final Score: "<<playerScore<<endl;
    			gameOver = true;
    			break;
			}
    	}
    	
    	cout<<"\n--------------------------------------"<<endl;
    	cout<<"END OF TURN "<<turn<<" SCORES:"<<endl;
    	cout<<"Player: "<<playerScore<<" | Computer: "<<computerScore<<endl;
    	cout<<"--------------------------------------"<<endl;
    	cout<<"\nPress any key for next turn...";
    	getch();
    	turn++;
    	if(turn>20)
    	{
        	cout<<"\nGame ended after 20 turns!"<<endl;
        	gameOver=true;
        	break;
    	}
	}
	displayResult(playerScore, computerScore);
	updateScore(playerScore);
	totalPlayers++;
}

//============================================
// COMPUTER ATTACK
void computerAttack(char playerBoard[10][10], int &computerScore)
{
	clearScreen();
	int row,col;
	
    do
    {
        row=rand()%10;
        col=rand()%10;
    }
	while (playerBoard[row][col]=='X'||playerBoard[row][col]=='O');
	
    //attack result
    if(playerBoard[row][col]=='S')
    {
        playerBoard[row][col]='X';
        computerScore+=10; 
		cout<<"\nComputer hits your ship at ("<<row<<","<<col<<")! "<<endl;
        cout<<"Computer Score = "<<computerScore;
    }
	else if(playerBoard[row][col]=='~')
    {
        playerBoard[row][col]='O';
        computerScore-=1;           //miss
        cout<<"\nComputer missed at ("<<row<<","<<col<<")."<<endl;
        cout<<"Computer Score = "<<computerScore;
    }
    else if(playerBoard[row][col]=='O'||playerBoard[row][col]=='X'||playerBoard[row][col]=='Z')
    {
	}
    else
	{
    	cout << "ERROR: Unexpected board cell at ("<<row<<","<<col<<") = "<< playerBoard[row][col] << endl;
	}	
    setColor(WHITE, BLACK);
    cout<<"\nYour Board After Computer Move: "<<endl;
    combineBoard(playerBoard, playerBoard, playerBoard,true);
    getch();
}

//=================================================================
// PLAYER ATTACK
void playerAttack(char opponentBoard[10][10], int &playerScore)
{
	int row,col;
    while(true)
    {
    	combineBoard(opponentBoard, opponentBoard, playerBoard,true);
    	cout<<"Enter the row: ";
    	cin>>row;
    	cout<<"Enter the column: ";
    	cin>>col;
    	if(row>9||row<0||col>9||col<0)
    	{
    		clearScreen();
    		cout<<"Invalid Coordinates input!"<<endl;
    		continue;
		}
    	if(opponentBoard[row][col]=='X'||opponentBoard[row][col]=='O')
    	{
    		clearScreen();
    		cout<<"Cell Already attacked! "<<endl;
    		continue;
		}
		else
		{
			clearScreen();
			break;
		}
    }
	
    //attack result
    if(opponentBoard[row][col]=='S')
    {
        opponentBoard[row][col]='X';
        playerScore+=10; 
		cout<<"You hit the enemy ship at ("<<row<<","<<col<<")! "<<endl;
        cout<<"Your Score = "<<playerScore;
    }
	else if(opponentBoard[row][col]=='~')
    {
        opponentBoard[row][col]='O';
        playerScore-=1;           //miss
        cout<<"\nYou  missed at ("<<row<<","<<col<<")."<<endl;
        cout<<"Your Score = "<<playerScore;
    }
    else if(opponentBoard[row][col]=='O'||opponentBoard[row][col]=='X'||opponentBoard[row][col]=='Z')
    {
	}
    else
	{
    	cout<<"ERROR: Unexpected board cell at ("<<row<<","<<col<<") = "<< opponentBoard[row][col] << endl;
	}
    setColor(WHITE, BLACK);
    cout<<"\nYour Board After Your Move: "<<endl;
    combineBoard(opponentBoard, opponentBoard, playerBoard,true);
}

//=============================================================
// COMBINED BOARD
void combineBoard(char enemyView[10][10], char computerBoard[10][10], char playerBoard[10][10],bool hideShips)
{
	char opponentBoard[10][10];
	char leftBoard[10][10];
	cout<<"\t\t\t\t\t\tOPPONENET BOARD"<<endl;
	cout<<"\tENEMY BOARD";
	cout<<"\t\t\t\t\t\t\t\t\t\t\tPLAYER BOARD"<<endl;
	// Print column headers
	cout<<"\t\t\t     0    1    2    3    4    5    6    7    8    9  "<<endl;
	//TOP BORDER
	cout << "    0 1 2 3 4 5 6 7 8 9 ";
    cout << "    +-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+"; //<< endl;
    cout << "\t    0 1 2 3 4 5 6 7 8 9 "<<endl;
	//rows
	char ccell;
	char pcell;
	for(int i = 0; i < 10; i++)
    {
        for(int j = 0; j < 10; j++)
        {
            if(computerBoard[i][j] == 'X' || computerBoard[i][j] == 'O')
            {
                leftBoard[i][j] = computerBoard[i][j];
            }
            else
            {
                leftBoard[i][j] = '.';
            }
        }
    }
	
    for(int i=0;i<10;i++)
    {
    	cout<<i<<"   ";
    	for(int j = 0; j < 10; j++)
        {
            // Print left board cell
            if(leftBoard[i][j] == 'X')
            {
                cout<<leftBoard[i][j]<<" ";
            }
            else if(leftBoard[i][j]=='O')
            {
                cout<<leftBoard[i][j]<<" ";
            }
            else
            {
                setColor(7, 0);
                cout<<leftBoard[i][j]<<" ";
            }
            setColor(7, 0);
        }
		cout<<" "<<i<<"   ";
        for(int j=0;j<10;j++)
        {
            char cell=enemyView[i][j];
            if(hideShips&&(cell=='S'))
			{
    			cell = '~';
			}
            //colors
            if(cell=='~')
            {
                setColor(7,1);
	        }
			else if(cell=='X')
            {
			    setColor(15,12);
            }
			else if(cell=='O')
            {
			    setColor(0,8);
            }
			else if(cell=='S')
            {
			    setColor(0,6);
			}
			else if(cell=='Z')
			{
				setColor(15,5);
			}
		
            cout<<"  "<<cell<<"  ";

            setColor(7,0);
            cout << "¦";
        }
        cout<<"\t"<<i<<"   ";
    	for(int j=0;j<10;j++)
    	{
    		opponentBoard[i][j]=playerBoard[i][j];
    		if(opponentBoard[i][j]=='~')
    		{
    			opponentBoard[i][j]='.';
    		}
			pcell=opponentBoard[i][j];
    		cout<<pcell<<" ";
		}
        cout<<endl;
        //BOTTOM BORDER
        cout<<"\t\t\t    +-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+";//<<endl;
       
		cout<<endl;
    }	
}
//======================================================
//Update score
void updateScore(int &score)
{
    scores[totalPlayers] = score;
}
//====================================================
// checking if all ships destroyed
bool allShipsDestroyed(char board[10][10])
{
    for(int i=0;i<10;i++)
    {
        for(int j=0;j<10;j++)
        {
            if(board[i][j] == 'S')
            {
                return false;
            }
        }
    }
    return true;
}

// ==========================================================
// display result
void displayResult(int player1Score, int player2Score)
{
    clearScreen();
    cout << "======================================" << endl;
    cout << "\t\tGAME RESULT" << endl;
    cout << "======================================\n" << endl;

    cout << "Player Score   : " << player1Score << endl;
    cout << "Opponent Score : " << player2Score << endl;
    cout << "--------------------------------------" << endl;

    if(player1Score > player2Score)
    {
        setColor(GREEN, BLACK);
        cout << "== YOU WIN! ==" << endl;
    }
    else if(player1Score < player2Score)
    {
        setColor(RED, BLACK);
        cout << "== YOU LOSE! ==" << endl;
    }
    else
    {
        setColor(YELLOW, BLACK);
        cout << "== IT'S A DRAW! ==" << endl;
    }

    setColor(WHITE, BLACK);
    cout << "\nPress any key to continue...";
    getch();
}


