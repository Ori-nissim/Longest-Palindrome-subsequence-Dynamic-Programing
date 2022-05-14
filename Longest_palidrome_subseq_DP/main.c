// The following program finds the longest subsequnce palidrome in a given string
// constructed out of 0 - 9 digits
// By Ori nissim


#include <stdio.h>
#include <stdlib.h>


#define checkAllocation(object) ((object == NULL) ? printf("memory allocation failed\n") : printf("") );

int getLongestPalindrome(char* array, int size, int* table);
void printTable(int* array, int size, char* comment);
void printPalindrome(int* table,int size,char* array);
char* scanArray(int* size);

int main()
{
	// enter size and digits by user
	int size;
	char* array = scanArray(&size);


	// init table 
	int* table = (int*)calloc(size * size, sizeof(int));
	checkAllocation(table);


	getLongestPalindrome(array, size, table);

	return 0;
}

int getLongestPalindrome(char* array, int size, int* table)	// this function gets and array and its size and returns its longest palindrom sub sequence and its matching DP table
{
	
	for (int k = 0; k < size; k++) 
	{
		for (int p = 0; p < size; p++)
		{
			if ( k == p )  table[k*size + p] = 1;		// palindrome from index  1 to 1 is at the length of 1

		}
	}

	// fill the rest
	int count = 1;

	for (int i = 0; i < size;)
	{
		
		for (int j = count; j < size && i < size; j++, i++)
		{
			if (i > j) table[i*size + j] = 0;

			else if (array[i] == array[j] && i != j)
			{
				table[i*size + j] = 2 + table[(i + 1)*size + j - 1];		//   matching character! add their len (2) to the previous solution
			} 
			else if (i !=j )
			{
				table[i*size + j] = max(table[(i + 1)*size +j], table[i*size + j - 1]);  // no matching characters so we get the maximum out of the previous solutions
			}
			
		}
		i = 0;
		count++;
		if (count == size) break;
	}



	printTable(table, size, "\nThe cell [i,j] in this table represents the longest palindrome from index i to j\n");

	// print longest palindrome
	printf("longest palindrome is: ");
	
	// print result to user
	printPalindrome(table, size,array);
	
	printf(" with the length of %d\n", table[size-1]);

	return table[size-1];
}

void printTable(int * table, int size, char * comment)
{

	for (int n = 0;  n < size ; n++)
		printf("\t(%d)", n);

	printf("\n\n");
 
	for (int i = 0; i < size; i++)
	{
		printf("(%d)", i);
		for (int j = 0; j < size; j++)
		{
			if (i ==0 && j == size-1) 
				printf("\t|%d|", table[i* size + j]);
			else
				printf("\t %d", table[i* size + j]);
		}
		printf("\n");
	}

	puts(comment);
}

void printPalindrome(int * table,int size, char* array)
{
	for (int i = size-1; i >= 0; i--)
	{
		if (i > 0 & table[i] == (table[i - 1] + 1) )
			printf("%c", array[i-1]);
		else if (i > 0 & table[i] == (table[i - 1] + 2))
		{
			printf("%c%c", array[i], array[i - 1]);
			
		}
		else if (table[i] == 1 & table[i-1] == 1 || table[i] == 1 & i == 0 )
		{
			printf("%c", array[i]);
			break;
		}
	}
}

char* scanArray(int * size)
{
	printf("Please enter array size: ");
	scanf("%d", size);

	char* array = (char*)malloc(*size);
	checkAllocation(array);

	printf("Enter %d numbers:\n", *size);
	for (int i = 0; i < *size; i++)
	{
		scanf("%s", (array+i));
	}
	return array;
}
