#include <stdint.h>
#include <stdio.h>


// Write a function that extracts a substring from a start index to an end index
// out of a char[] argument (hint: this will use a result argument)
// start is inclusive and end is exclusive

void substring(char str[], int32_t start, int32_t end, char result[]) {
	// Copy index start from str to index 0 in result (and start + 1 to 1, etc)
	for(int i = start; i < end; i += 1) {
		result[i - start] = str[i];
	}
	result[end - start] = 0; // important in string processing! Who puts in the \0?
}


int main() {

	// Now, give me a test case! An example of calling substring
	char result1[5];
	substring("Hello world", 1, 5, result1);

	char result2[4] = { 'X', 'Y', 'Z', 'Q' };
	substring("dinosaur", 2, 5, result2);

	char result3[1];
	substring("abcdef", 5, 5, result3);

	char result4[4];
	substring("abcdef", 3, 15, result4);

	printf("Should be ello: %s\n", result1);
	printf("Should be nos: %s\n", result2);
	printf("Should be (empty string): %s\n", result3);
	printf("Should be def: %s\n", result4);

	printf("%p %p %p %p\n", result1, result2, result3, result4);

}
