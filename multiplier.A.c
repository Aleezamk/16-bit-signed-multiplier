#include <stdio.h>
#include <stdint.h>

// Function to add two integers using bitwise operators
int adder(int x, int y) {
    int sum, carry;
    while (y != 0) {
        carry = x & y;     // Calculate carry
        sum = x ^ y;       // Calculate sum without carry
        y = carry << 1;    // Shift carry to the left for the next addition
        x = sum;           // Update x to the current sum
    }
    return x;
}

// Function to compute the two's complement of a number
int two_complement(int a) {
    a = adder(~a, 1);      // Take bitwise NOT and add 1
    return a;
}

// Function to multiply two 16-bit integers
int32_t multiplier(int16_t num1, int16_t num2) {
    int neg = 0;           // Flag to indicate if the result should be negative
    int32_t answer = 0;

    // Handle cases where either or both numbers are negative
    if ((num1 < 0) && (num2 < 0)) {
        num1 = two_complement(num1);
        num2 = two_complement(num2);
    } else if ((num1 < 0) || (num2 < 0)) {
        neg = 1;
        if (num1 < 0) {
            num1 = two_complement(num1);
        }
        if (num2 < 0) {
            num2 = two_complement(num2);
        }
    }

    // Perform multiplication using bit-shifting and addition
    for (int i = 0; i < 16; i++) {
        if (num2 & 1) {             // Check if the least significant bit of num2 is 1
            answer = adder(answer, num1);
        }
        num1 <<= 1;                 // Left shift num1
        num2 >>= 1;                 // Right shift num2
    }

    // If the result should be negative, take the two's complement
    if (neg) {
        answer = two_complement(answer);
    }

    return answer;
}

// Main function
int main(void) {
    int16_t num1, num2;
    int32_t product;

    // Input numbers from the user
    printf("Enter num1: ");
    scanf("%hd", &num1);
    printf("Enter num2: ");
    scanf("%hd", &num2);

    // Compute the product
    product = multiplier(num1, num2);

    // Output the result
    printf("Product is %d\n", product);

    return 0; // Indicate successful execution
}
