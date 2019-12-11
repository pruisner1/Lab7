/*
Lane Pruisner
C++ Fall 2019
Due Decemeber 11, 2019
Lab #7 Battleship
Description: Create a program where the user is able to plot where they want their ships to be on a 10x10 grid, whil being able o see 
where they have guessed against the computer. The computers ships should be laid out randomly without overlapping. The computers guesses are
random as well.
*/
//Libraries neede3d for the program
#include <iostream>
#include <iomanip>
#include <string>

using namespace std;

//Preconditions: The player will need to have placed all their ships as well as the computer has placed all of its ships,
// as well as the boards are being displayed and recorded, then the game will procede with the actual game
//Postconditions: Either the player or the computer has won the game therefore the game will end
void TheGame();

//Pre Conditions: All ships are placed onto the players board with a location
//Post Conditions: there are no post conditions
void Loadingships();

//Pre Conditions: Character values for each char so the board will be able to set up the 10x10 grid
//Post Conditions there are no post conditions
void Boardsetup(int player);

//Preconditions: there is a structure that allows the user to input the boats how they like (Direction, x, y)
//Postconditions: the user has inputted all ships in correctly so the program is able to keep running
PlacingShips Userinput();

//PreConditions: The user has inputted coordinates to attack an enemy ships
//POstconditions: No matter the outcome of the attack the board is recreated to display the hit ot miss
void Boardreset();

//Preconditions: all ships have been placed and the game is ready to go 
//Post conditions: the user has inputted the attack coordinates in correctly and now has attacked the enmy ships
bool UserinputAttack(int& x, int& y, int Player);

//Preconditions: Game is running
//Postconditions: Checks after every turn if the game has been completed or not
bool checkgame(int Computer);

// constant integers that are used for the grid and the amount of ships in the gmame
const int WidthBoard = 10;
const int HeightBoard = 10;
const int shiptypes = 5;

//character values for every aspect of the game that is being diplayed
char Water = 247;
char Hit = 'H';
char Miss = 'M';
char SHIP = '#';

int main()
{
	//void functions inside the main
	TheGame();
	Boardsetup();
	PlacingShips Userinput;
	UserinputAttack();
	checkgame();
}
//Struct for positioning of the ships when being inputted
struct positioning
{
	int X;//horizontal position
	int Y; //vertical position
};
//Struct for ships which include the name of the ship, its location/length, the max length of any of the ships
// and lastly max hits on any of the ships
struct ships
{
	string shipname;//ship name

	int location;//coodinates of the ships location

	positioning Gridpos[5]; // max length of ships

	bool hits[5]; //max hits on a ship
}ship[shiptypes];
// Struct for the grid including the width of the board and the heigth of the board
struct playergrid
{
	char grid[WidthBoard][HeightBoard];
}player[2];
//enumeration types including the two types of directions a board can go
enum ShipDirection
{
	Horizontal, Vertical
};
// Struct for the description of ship when placing it, what kind of ship is it and what direction it is going
struct PlacingShips
{
	ShipDirection direction;
	ships shiptype;
};
//bool value so the game does not run until it reaches the actual game
bool Gameisgoing = false;


void TheGame()
{
	//Preconditions for the actual game
	Loadingships();
	Boardreset();

	for (int controllers = 1; controllers < 2; ++controllers)//For loop that lopps through the player and the computer
	{

		for (int theships = 0; theships < shiptypes; ++theships) //For loop that loops through the ships as the user is placing them
		{

			system("class"); //Gives control back to the program after the ships have been placed
			Boardsetup(controllers); //sets up boards
			//instructions for the game here
			cout << "\n";
			cout << "These are the instructions to play, read caredully\n\n";
			cout << "Facing (0 is Horizontal, 1 is vertical), X (Top row) coordinate, Y (left side) coordinate \n";
			cout << "Example: 1 5 3		This would place a ship beginning at X:5 Y: 3 going vertically \n"; // gives a description of how the user needs to input the coordinates to allow the function to run properly
			cout << "Ship to place: " << ship[theships].shipname << " which has a length of " << ship[theships].location << "\n";
			cout << "Where would you like to place it? ";


			PlacingShips aShip;// calls to the function placingships 
			aShip.shiptype.Gridpos[0].X = -1;

				while (aShip.shiptype.Gridpos[0].X == -1)//While loop for the users control while placing ships until good data is returned
				{
					aShip = Userinput();
				}

				//Combining user data with the ships data
				aShip.shiptype.location = aShip.[theships].location; 
				aShip.shiptype.shipname = aShip.[theships].shipname;

				//Adds first grid point to players grid
				player[controllers].grid[aShip.shiptype.Gridpos[0].X][aShip.shiptype.Gridpos[0].Y] = SHIP;

				//Determine all grid points based on the length of the ship and direction
				for (int i = 1; i < aShip.shiptype.location; ++i)
				{
					if (aShip.direction == Horizontal)
					{
						aShip.shiptype.Gridpos[i].X = aShip.shiptype.Gridpos[i - 1].X + 1;
						aShip.shiptype.Gridpos[i].Y = aShip.shiptype.Gridpos[i - 1].Y;

					}
					if (aShip.direction == Vertical)
					{
						aShip.shiptype.Gridpos[i].Y = aShip.shiptype.Gridpos[i - 1].Y + 1;
						aShip.shiptype.Gridpos[i].X = aShip.shiptype.Gridpos[i - 1].X;
						
					}

					// Add the remaining gridpoints to the players board
					player[controllers].grid[aShip.shiptype.Gridpos[i].X][aShip.shiptype.Gridpos[i].Y] = SHIP;
				}
				//Then will loop back through each ship type
		}
		//Should loop through the player and the comuter
	}
	// Finished with placing ships now the attacking begins
	Gameisgoing = true;
	int Player1 = 1;
	do
	{
		int enemyplayer;
		if (Player1 == 1)//The opposite board is the computers board so therefore it is the enemy player
		{
			enemyplayer = 2;
		}
		if (Player1 == 2)
		{
			enemyplayer = 1;
		}

		system("Class");//gives control back to the program
		Boardsetup(enemyplayer);


		//Attacking coordinates from the computer
		bool goodinput = false;

		srand(unsigned int(time(NULL)));

		int x = rand() % 11;
		int y = rand() % 11;

		while (goodinput == false)
		{
			goodinput = UserinputAttack(x, y, Player1);
		}
		//Checks if a ship got hit or that the attacking coodinates missed
		if (player[enemyplayer].grid[x][y] == SHIP)
		{
			player[enemyplayer].grid[x][y] = Hit;
		}

		if (player[enemyplayer].grid[x][y] == Water)
		{
			player[enemyplayer].grid[x][y] = Miss;
		}
		//Checks to see if the game is over
		//if 0 is returned that means no one has one yet
		int Won = checkgame(enemyplayer);
		if (Won != 0)
		{
			Gameisgoing = false;
			break;
		}



	} while (Gameisgoing); 
		system("class");//Gives cntrol back to the program

		cout << "\n\n CONGRATULATIONS you have won!\n\n\n\n\n";//Someone has won the game
}
void Boardsetup(int Player)
{
	//Draws a board for a player
	cout << "Player's Game Board\n";
	cout << "-----------------------\n";
	
	//loops through the board width and the number of columns
	cout << "   ";
	for (int w = 0; w < WidthBoard; ++w)
	{
		if (w < 10)//layout for the board between 1 character long and the end of the board
			cout << w << "  ";
		else if (w >= 10)
			cout << w << " ";
	}
	cout << '\n';
	//loops through each gridpoint and displays what is suppose to be there
	for (int h = 0; h < HeightBoard; ++h)
	{
		for (int w = 0; w, WidthBoard; ++w)
		{
			if (w == 0)
				cout << h << " ";//loops that display the numbers and displays the ships

			if (w < 10 && w == 0)
				cout << " ";

			if (Gameisgoing == false)
				cout << player[Player].grid[w][h] << "  ";

			if (Gameisgoing == true && player[Player].grid[w][h] != SHIP)
			{
				cout << player[Player].grid[w][h] << "  ";
			}
			else if (Gameisgoing == true && player[Player].grid[w][h] == SHIP)
			{
				cout << Water << "  ";
			}
			if (w == WidthBoard - 1)
				cout << "\n";

		}
	}

}

PlacingShips Userinput()
{	//Userinput for where they want the their ships to be 
	int d;
	int x;
	int y;
	PlacingShips baddig; //for a bad return

	cin >> d >> x >> y;// the input
	if (d != 0 && d != 1) 
		return baddig;
	if (x< 0 || x >= WidthBoard)
		return baddig;
	if (y < 0 || y >= HeightBoard)
		return baddig;
	//makes sure that all the data are good values
	baddig.direction = (ShipDirection)d; 
	baddig.shiptype.Gridpos[0].X = x;
	baddig.shiptype.Gridpos[0].Y = y;
	return baddig;
}
void Loadingships()
{
	//sets the data up for the ships and all their characteristics
	ship[0].shipname = "CRUISER"; ship[0].location = 3;
	ship[1].shipname = "CARRIER"; ship[1].location = 5;
	ship[2].shipname = "BATTLESHIP"; ship[2].location = 4;
	ship[3].shipname = "SUBMARINE"; ship[3].location = 3;
	ship[4].shipname = "DESTROYER"; ship[4].location = 2;

}
void Boardreset()
{
	//loops through the players board and the computers board
	for (int user = 1; user < 2; ++user)
	{
		//sets all spots without a ships to water
		for (int w = 0; w < WidthBoard; ++w)
		{
			for (int h = 0; h < HeightBoard; ++h)
			{
				player[user].grid[w][h] = Water;
			}
		}
		//loops through both the players
	}
}
bool UserinputAttack(int& x, int& y, int Player)
{
	cout << "\nPLayer" << Player << " Enter coordinates to attack the enemy: ";
	bool correctinput = false;
	cin >> x >> y; //user input for coordinates and where they want to attack
	if (x < 0 || x >= WidthBoard)
	{
		return correctinput;		//limitations of where they can attack has to be inside the board
	}
	if (y < 0 || y >= HeightBoard)
	{
		return correctinput;
	}
	correctinput = true;
	return correctinput;
}
bool checkgame(int Computer)
{
	bool win = true;
	//loops through the enemy board
	for (int w = 0; w < WidthBoard; ++w)
	{
		for (int h = 0; h < HeightBoard; ++h)
		{
			//if any of the ships remain the game is not over
			if (player[Computer].grid[w][h] = SHIP)
			{
				win = false;
				return win;
			}
		}
	}
	//if we return win that mean someone has won the game
	return win;
}