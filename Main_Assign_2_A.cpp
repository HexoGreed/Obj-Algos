/*
* Hamza Shah
* 
* 
* 9/5/2025 (Had to create a new file bc lnk2019 error, i <3 visual stoudio sooooo much)
* 
* notes: I kinda maybe, did an oopsie by doing the padding function after the main functions
* also i shouldve seperated it into a different file but im lazy
* and didnt know it would be this much code
* 
* 
* 
* 
* 
* QA
* 
1. The runtime complexity of binaryNumOfOnesRec is O(log2N)
This is because the function makes a single recursive call where the input value, N, is divided by 2. 
This process continues until N becomes 0, which takes a number of steps proportional to the number of bits in N.


 2.The runtime complexity of binaryNumOfOnesIter is also O(log2N)
 The while loop repeatedly divides the number by 2, and the loop terminates when the number reaches 0. 




*/


//Code needs to be redone


#include <iostream>
#include <string>
#include <vector>
#include <utility> // For std::pair (lets us return 2 values)
// A helper function to pad a binary string with leading zeros.
// The padding ensures the string's length is a multiple of 4.
std::string padBinaryString(const std::string& binaryStr) {


    int length = binaryStr.length();

    int remainder = length % 4;
	//if remaineer does not equal 0 we need to pad it
    if (remainder != 0) {
        int paddingNeeded = 4 - remainder;
        // The number of zeros needed is 4 minus the remainder.

        return std::string(paddingNeeded, '0') + binaryStr;
		//creates a string of 0's and appends the original string
    }

    return binaryStr;
}

//Recursively calculates the number of 1's and the binary representation of N.


std::pair<std::string, int> binaryNumOfOnesRec(long long N) {
   


    if (N == 0) {
        return { "", 0 };
    }

    //Call the function with N divided by 2 (integer division, like a right bit shift).
    // This breaks the problem down into a smaller piece.
    std::pair<std::string, int> result = binaryNumOfOnesRec(N / 2);


    // The current bit is the remainder of N divided by 2 (1 if N is odd, 0 if even).
    int currentBit = N % 2;




    // Build the binary string by appending the current bit.
    std::string newStr = result.first + std::to_string(currentBit);

    // Add the current bit to the count of 1's.
    int newCount = result.second + currentBit;


    return { newStr, newCount };
}






// Iteratively calculates the number of 1's and the binary representation of N.


std::pair<std::string, int> binaryNumOfOnesIter(long long N) {

    int count = 0;
    std::string binaryStr = "";
    long long tempN = N;



    while (tempN > 0) {
        // Check if the last bit is 1 (tempN is odd).
            
        if (tempN % 2 == 1) { //if odd
            count++;
            binaryStr = "1" + binaryStr; // Prepend "1" 
        } else {
            binaryStr = "0" + binaryStr; // Prepend "0"
        }

        // Right-shift the number by 1 bit
        tempN /= 2;
    }


    return { binaryStr, count };
}





// Helper function to test and print the results for a given function and value.
void testFunction(const std::string& funcName, std::pair<std::string, int>(*func)(long long), long long value) { // i hated this part the most :D
    std::cout << "  Function: " << funcName << std::endl;


    std::string binaryStr;
    int count;

    // Handle N=0 as a special case for the recursive function's output format.
    if (value == 0 && funcName == "Recursive") { // mandatory 0 chck
        binaryStr = "0";
        count = 0;
    }
    else {
        std::pair<std::string, int> result = func(value);
        binaryStr = result.first;
        count = result.second;
    }

    std::cout << "    Binary representation: " << padBinaryString(binaryStr) << std::endl;
    std::cout << "    Number of 1's: " << count << std::endl;
}

// Driver program to test the functions 
int main() {
	// using long long bc (1 << 31) is out of range for int


    std::vector<long long> testValues = { 0, 1, 17, 123, 2048, (1LL << 31), (1LL << 31) - 1 };
    //1LL is treated as a long long
	//essentially 2^31 and 2^31 - 1


    std::cout << "Testing Recursive & Iterative Functions" << std::endl;

    for (long long val : testValues) {
        std::cout << "\nInput Value: " << val << std::endl;

        // For the recursive function, a separate call is needed because of the base case.
        // The core recursive logic returns an unpadded string.
        std::pair<std::string, int> recResult = binaryNumOfOnesRec(val);
        std::cout << "Recursive: " << std::endl;
        std::cout << "Binary: " << padBinaryString(recResult.first) << std::endl;
        std::cout << "# of 1's: " << recResult.second << std::endl;

        // For the iterative function, we get the result and pad it.
        std::pair<std::string, int> iterResult = binaryNumOfOnesIter(val);
        std::cout << "Iterative:" << std::endl;
        std::cout << "Binary: " << padBinaryString(iterResult.first) << std::endl;
        std::cout << "# of 1's: " << iterResult.second << std::endl;
    }

    std::cout << "\nTest complete " << std::endl;

    return 0;
}