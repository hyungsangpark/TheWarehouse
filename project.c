/* ENGGEN131 Project - C Project - 2019 */
/* The Warehouse */

/* Hyung Park, hpar461, 974217963 */

#include "project.h"

/*
TimeWorked function receives time a worker checked in and out in a minute & second form
(regardless of whichever order they put in) and returns absolute time difference by checking
whether the difference is negative or positive then convert any negative time differences
to positive by changing its sign before returning.
(Minutes for each timing is converted to seconds then added into the corresponding seconds.)
*/
int TimeWorked(int minuteA, int secondA, int minuteB, int secondB)
{
	// Finds an absolute time difference between two time values.
	int timeDiff = (secondA + minuteA * 60) - (secondB + minuteB * 60);
	// Return absolute time difference
	return (timeDiff < 0) ? -timeDiff : timeDiff;
}

/*
WarehouseAddress receives upper bound value from the user and returns
a largest prime number that is lower than the received value.
*/
int WarehouseAddress(int maximum)
{
	// While maximum is bigger than 2:
	while (maximum > 2)
	{
		// Decrement maximum by one.
		maximum--;

		// Define variables to be used.
		int notPrime = 0;
		int n = 2;

		// While a 'notPrime' flag is not raised and n is less than maximum
		while (!notPrime && n < maximum)
		{
			// If it is divisible by a number without a remainder:
			if (maximum % n == 0 && maximum != n)
			{
				// Raise notPrime flag.
				notPrime = 1;
			}
			// Increment n by 1.
			n++;
		}

		// If notPrime flag has not been raised:
		if (!notPrime)
		{
			// Return a current, prime number.
			return maximum;
		}
	}

	// Return 2 if maximum is less than or equal to 2.
	// (Mathematically, 2 is the smallest prime number.)
	return 2;
}

/*
Advertise receives a character pointer variable and moves each character
1 space to the left with the first character being moved to the last.
*/
void Advertise(char *words)
{
	// Stores the first character in a separate variable.
	int start = words[0];

	// Repeat the code following for the length of the word.
	for (int i = 0; i < strlen(words); i++)
	{
		// The next character is copied to the current one.
		words[i] = words[i + 1];
	}

	/* Change the last character of the array to 
	what was originally the first character. */
	words[strlen(words)] = start;
}

/*
WinningBid goes through each bid in the array of values,
then checks whether the current value is a unique value,
which if it is, then checks whether the value is the lowest
bid in the array.

It contains a helper function FindMax, which, fairly logically, finds
the maximum value in the array. A maximum value from values were set
as the initial lowest value of the bid since this will allow any unique
value after this to be considered as lower than 'current lowest bid' while
maintaining the functionality of only keeping the lowest unique value.
*/

int FindMax(int array[], int length)
{
	// Initial maximum value is set to be the first value in the array.
	int max = array[0];

	for (int i = 0; i < length; i++)
	{
		// If the value is greater than the current maximum value:
		if (array[i] > max)
		{
			// The maximum value is changed to the current value.
			max = array[i];
		}
	}

	// Return maximum value
	return max;
}

int WinningBid(int *values, int length)
{
	// Initializing and defining variables to use.
	int duplicate;
	int numDuplicate = 0;

	/* Defining the lowest bid to be the maximum value in the array. 
	Reasoning behind this is written above in the comments section. */
	int lowestBid = FindMax(values, length);

	for (int i = 0; i < length; i++)
	{
		// Lower the duplicate flag
		duplicate = 0;

		// Loop through the values array
		for (int j = 0; j < length; j++)
		{
			// If duplicate numbers are found while not being from a same location
			if (i != j && values[i] == values[j])
			{
				// Raise the duplicate flag.
				duplicate = 1;
			}
		}

		// If duplicate flag was not raised
		if (!duplicate)
		{
			// If currently found unique number is lower than the current lowest bid
			if (values[i] < lowestBid)
			{
				// Set the lowestBid
				lowestBid = values[i];
			}
		}
		// If duplicate flag was raised
		else if (duplicate)
		{
			// Increment the counter of duplicate numbers found
			numDuplicate++;
		}
	}

	/* Return -1 if number of duplicates found equals the number of elements in the array.
	Otherwise, return the lowest unique bid. */
	return (numDuplicate == length) ? -1 : lowestBid;
}

/*
BoxDesign receives a pointer value to an empty string and the width and height of the box
it should make in the given pointer. It uses a nested loop to check which character out of
"*", "X", " " they should allocate and everytime it loops horizontally, it adds an extra
"\n" to show that it should move on to a next line.

For the part where the program checks whether it should add "X", it also checks whether the
box dimension has even widths or heights, so that on even dimensions, it would add another 
"X" after the center part of the box. 
*/

void BoxDesign(char *design, int width, int height)
{
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			// If i or j is on the border of a box,
			if ((i == 0 || i == height - 1) || (j == 0 || j == width - 1))
			{
				// Allocate "*"
				strcat(design, "*");
			}
			// If i and j is on the center of the box,
			else if (((i == (height - 1) / 2) || (i == ((height - 1) / 2 + 1) && height % 2 == 0)) && ((j == (width - 1) / 2) || (j == ((width - 1) / 2 + 1) && width % 2 == 0)))
			{
				// Allocate "X"
				strcat(design, "X");
			}
			else
			{
				// Allocate " "
				strcat(design, " ");
			}
		}

		// Allocate "\n" to indicate end of line.
		strcat(design, "\n");
	}
}

/*
WorkerRoute receives a 10x10 2D array and detects a start and end location indicated by 1 and 2
respectively. It then checks whether the two points are on the same horizontal line, vertical line,
or not in the same line. 

If they are on the same line, it changes values between two points into 3 and if they are not on the
same line, it changes horizontal values between the start and end, which after then it fills up the
vertical values between them. 

Because a helper function that fills in values between the start and end point only fills up "between"
two points, a point that is on the intersection of horizontal and vertical line is manually replaced by 3.
*/

// Defining a new type which contains an i and j coordinate.
typedef struct
{
	int i;
	int j;
} coordinates;

/* 
Route is a helper function used to fill in a value of 3 between two points based on
whether the required route is on i direction or j direction.

It receives a 2D array, starting coordinate, ending coordinate, and two flags indicating
whether the direction of the route drawn is in i-direction (I) or j-direction (J) and
whether the starting coordinate is higher than the ending coordinate in desired coordinate
values.

For example, if a j-directional route with a starting point that has higher j values than
the ending point, the code will be as followed:

Route(warehouse, start, end, 'J', 'H');
*/

void Route(int array[][10], coordinates start, coordinates end, char IorJ, char LorH)
{
	// If it's an i-direction route with lower starting i value
	if (IorJ == 'I' && LorH == 'L')
	{
		// for the points that are between and in the same j-direction with the two points
		for (int i = start.i + 1; i < end.i; i++)
		{
			// Set them to 3
			array[i][start.j] = 3;
		}
	}
	// If it's an i-direction route with higher starting i value
	else if (IorJ == 'I' && LorH == 'H')
	{
		// for the points that are between and in the same j-direction with the two points
		for (int i = start.i - 1; i > end.i; i--)
		{
			// Set them to 3
			array[i][start.j] = 3;
		}
	}
	// If it's a j-direction route with lower starting j value
	else if (IorJ == 'J' && LorH == 'L')
	{
		// for the points that are between and in the same i-direction with the two points
		for (int j = start.j + 1; j < end.j; j++)
		{
			// Set them to 3
			array[start.i][j] = 3;
		}
	}
	// If it's a j-direction route with higher starting j value
	else if (IorJ == 'J' && LorH == 'H')
	{
		// for the points that are between and in the same i-direction with the two points
		for (int j = start.j - 1; j > end.j; j--)
		{
			// Set them to 3
			array[start.i][j] = 3;
		}
	}
}

coordinates find(int array[][10], int toFind)
{
	// Initialize variables found with a coordinates type.
	coordinates found;

	/* 
	Nested Loop below finds the start and end point in the existing warehouse array,
	then stores their location in corresponding variables.
	*/
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			// If start point is found
			if (array[i][j] == toFind)
			{
				// Store current i and j values to the coordinates of start variable.
				found.i = i;
				found.j = j;
			}
		}
	}

	// Return found coordinate
	return found;
}

void WorkerRoute(int warehouse[10][10])
{
	// Define variable type of start and end point as 'coordinates'
	coordinates start, end;

	start = find(warehouse, 1);
	end = find(warehouse, 2);

	// If they are both in horizontal direction
	if (start.i == end.i)
	{
		// If starting point has lower j values than ending point
		(start.j > end.j) ? Route(warehouse, start, end, 'J', 'H') : Route(warehouse, start, end, 'J', 'L');
	}
	// If they are both in vertical direction
	else if (start.j == end.j)
	{
		// If starting point has lower i values than ending point
		(start.i > end.i) ? Route(warehouse, start, end, 'I', 'H') : Route(warehouse, start, end, 'I', 'L');
	}
	else
	{
		// If starting point has higher i values than ending point
		if (start.i > end.i)
		{
			// Recall Route function
			Route(warehouse, end, start, 'I', 'L');
			(start.j > end.j) ? Route(warehouse, start, end, 'J', 'H') : Route(warehouse, start, end, 'J', 'L');
		}
		// If starting point has lower i values than ending point
		else if (start.i < end.i)
		{
			// Recall Route function
			Route(warehouse, end, start, 'I', 'H');
			(start.j > end.j) ? Route(warehouse, start, end, 'J', 'H') : Route(warehouse, start, end, 'J', 'L');
		}

		// Manually change value of the intersection point as 3
		warehouse[start.i][end.j] = 3;
	}
}

/*
MakeMove function receives an array and a character representing the direction the WORKER should go
(w, a, s, d would be up, left, down, right respectively) then uses two helper function to "move" the
WORKER piece in the actual array.

It first finds a current location of a worker piece in the board using FindWorker function. After that,
it decides whether the piece should move in y direction or x direction by changing moveX or moveY values
which are used to manipulate a "forward" spot in the board.

Then it checks whether a block in front of current worker is an [empty space / target] or 
[box with empty space after box] which, if it's an [empty space/target], it runs a helper function
"MoveForward" once and moves the worker. Otherwise if it's [box with empty space after box], it first 
moves the box then moves the worker.

After everything has been moved, it then loops through the entire array to check whether there are any
targets left or a worker that is not on the target. If it's found, return 0 to show that the game isn't
over and if they are not found, return 1 to show that the game is over.
*/

void MoveForward(int array[][10], coordinates toMove, int moveX, int moveY)
{
	// printf("Running Move Forward...\n");
	int oneAhead = array[toMove.i + moveY][toMove.j + moveX];
	int currentPos = array[toMove.i][toMove.j];

	// if ((currentPos == BOX) || (currentPos == WORKER))
	if (currentPos % 2 == 1)
	{
		// printf("Current Position is Worker or Box without target!\n");
		if (oneAhead == TARGET)
		{
			// printf("oneAhead is Target!\n");
			array[toMove.i + moveY][toMove.j + moveX] = currentPos + 1;
			array[toMove.i][toMove.j] = SPACE;
		}
		else if (oneAhead == SPACE)
		{
			// printf("oneAhead is Space!\n");
			array[toMove.i + moveY][toMove.j + moveX] = currentPos;
			array[toMove.i][toMove.j] = oneAhead;
		}
	}
	// else if ((currentPos == BOX_ON_TARGET) || (currentPos == WORKER_ON_TARGET))
	else if (currentPos % 2 == 0)
	{
		// printf("Current Position is Worker or box with target!\n");
		array[toMove.i][toMove.j] = TARGET;
		(oneAhead == TARGET) ? (array[toMove.i + moveY][toMove.j + moveX] = currentPos) : (array[toMove.i + moveY][toMove.j + moveX] = currentPos - 1);
	}
}

// FindWorker specifically finds a worker and this is adapted from "find" function used in earlier tasks.
coordinates FindWorker(int array[][10])
{
	// Initialize coordinate variable that will be returned.
	coordinates found;

	/* 
	Nested Loop below finds the start and end point in the existing warehouse array,
	then stores their location in corresponding variables.
	*/
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			// If start point is found
			if ((array[i][j] == WORKER) || (array[i][j] == WORKER_ON_TARGET))
			{
				// Store current i and j values to the coordinates of start variable.
				found.i = i;
				found.j = j;
			}
		}
	}

	// return the found coordinate
	return found;
}

int MakeMove(int warehouse[10][10], char move)
{
	// Define current location of a worker
	coordinates worker = FindWorker(warehouse);

	// Initialize movements
	int moveX, moveY;

	// Defines specific movement value according to the user input.
	(move == 'w') ? (moveY = -1) : ((move == 's') ? (moveY = 1) : (moveY = 0));
	(move == 'a') ? (moveX = -1) : ((move == 'd') ? (moveX = 1) : (moveX = 0));

	// Define current position and positions that are one and two blocks ahead of worker block
	int oneAhead = warehouse[worker.i + moveY][worker.j + moveX];
	int twoAhead = warehouse[worker.i + moveY * 2][worker.j + moveX * 2];
	int workerPos = warehouse[worker.i][worker.j];

	// There is either a target or space oneAhead.
	if ((oneAhead == SPACE) || (oneAhead == TARGET))
	{
		// Move the worker
		MoveForward(warehouse, worker, moveX, moveY);
	}
	// There is a box (or box on target) ahead while the one in front of the box is not a box.
	else if (((oneAhead == BOX) || (oneAhead == BOX_ON_TARGET)) && !((twoAhead == WALL) || (twoAhead == BOX) || (twoAhead == BOX_ON_TARGET)))
	{
		// Initialize and define a new coordinate point of a box that's in front of the worker
		coordinates box;
		box.i = worker.i + moveY;
		box.j = worker.j + moveX;

		// Move a box that is in front of worker first
		MoveForward(warehouse, box, moveX, moveY);
		// Move the worker
		MoveForward(warehouse, worker, moveX, moveY);
	}

	// Check whether there's any targets left or workers who are not on target.
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			if ((warehouse[i][j] == TARGET) || (warehouse[i][j] == WORKER))
			{
				// If found, return 0;
				return 0;
			}
		}
	}

	// Return 1 if there is no remaining targets and the worker is on a target
	return 1;
}
