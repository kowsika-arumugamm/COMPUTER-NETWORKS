#include <stdio.h>
#include <string.h>

// Function for bit stuffing
void bitStuffing(int N, int arr[])
{
	// Stores the stuffed array
	int brr[100]; // Increase size to accommodate stuffed bits

	// Variables to traverse arrays
	int i, j, k;
	i = 0;
	j = 0;

	// Loop to traverse in the range [0, N)
	while (i < N) {

		// If the current bit is a set bit
		if (arr[i] == 1) {
		
			// Stores the count of consecutive ones
			int count = 1;

			// Insert into array brr[]
			brr[j] = arr[i];

			// Loop to check for
			// next 5 bits
			for (k = i + 1;
				arr[k] == 1 && k < N && count < 5; k++) {
				j++;
				brr[j] = arr[k];
				count++;

				// If 5 consecutive set bits
				// are found, insert a 0 bit
				if (count == 5) {
					j++;
					brr[j] = 0;
				}
				i = k;
			}
		}

		// Otherwise insert arr[i] into
		// the array brr[]
		else {
			brr[j] = arr[i];
		}
		i++;
		j++;
	}

	// Print the stuffed bit stream
	printf("Stuffed bit sequence: ");
	for (i = 0; i < j; i++)
		printf("%d", brr[i]);
	printf("\n");
}

// Driver Code
int main()
{
	int N, i;

	// Get the number of bits
	printf("Enter the number of bits: ");
	scanf("%d", &N);

	int arr[N]; // Create an array to store the bits

	// Get the bit stream from the user
	printf("Enter the bit sequence (0s and 1s only):\n");
	for (i = 0; i < N; i++) {
		scanf("%d", &arr[i]);
		if (arr[i] != 0 && arr[i] != 1) {
			printf("Invalid input! Please enter only 0 or 1.\n");
			return -1; // Exit if invalid input is provided
		}
	}

	// Perform bit stuffing
	bitStuffing(N, arr);

	return 0;
}
