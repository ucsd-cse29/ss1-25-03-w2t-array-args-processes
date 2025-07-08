#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

// encode2 that takes a integer representing a UTF8 2-byte code point, and
// produces the encoding as 2 bytes
// Puts the result in the first 2 bytes of the result argument (which is
// assumed to have the first 2 bytes free)
// CANNOT write this function signature: char[] encode2(uint16_t code_point)
// code_point looks like 0b00000YYYYYxxxxxx
// trying to put 0b110YYYYY into result[0] and 0b10xxxxxx into result[1]
void encode2(uint16_t code_point, char result[]) {
	printf("result is at %p\n", result);
	char byte1 = (char)((code_point & 0b000011111000000) >> 6);
	byte1 = byte1 | 0b11000000;
	char byte2 = ((char)(code_point & 0b000000000111111)) | 0b10000000;
	result[0] = byte1;
  result[1] = byte2;	
}

int main() {
	char alpha_result[3] = { 0, 0, 0 };
	printf("alpha_result is at %p\n", alpha_result);
	encode2(945, alpha_result);
	printf("Should be α: %s\n", alpha_result);

	char e_result[3] = { 0, 0, 0 };
	printf("e_result is at %p\n", e_result);
	encode2(233, e_result);
	printf("Should be é: %s\n", e_result);

	char input[10];
	char result[3] = { 0, 0, 0 };
	// Goal: write a loop that reads input expected to be a integer
	// and prints out the 2 byte UTF8 encoding of that code point
	while(1) {
		// fgets: read up to 10 bytes or the first newline character and put the
		// result in input (with a null terminator)
		fgets(input, 10, stdin);
		uint16_t code_point = (uint16_t)(atoi(input));
		encode2(code_point, result); // What's wrong with this line?
		printf("The user typed: %u, as UTF8 it is %s\n", code_point, result);
	}










	/*
  for(uint16_t i = 945; i < 955; i += 1) {
		char greek_letter[] = { 0, 0, 0 };
		encode2(i, greek_letter);
		printf("%u: %s\n", i, greek_letter);
	}
	char e_with_accent[] = "é";
	printf("Should be 233: %u\n", decode2(e_with_accent));

	char alpha[] = "α";
	printf("Should be 945: %u\n", decode2(alpha));
	char beta[] = "β";
	printf("Should be 946: %u\n", decode2(beta));











*/
	// char crab[] = "🦀";
	// printf("%hhu\n", crab[0]);
	// Crab is not a good test case because it is 11110000 – not a 2 byte encoding!
}

// decode2 that takes a 2-byte char array of a UTF8 encoding, and produces the
// integer for that code point
uint16_t decode2(char encoding[]) {
	// ASSUME encoding is 2 bytes long (or equivalently the first 2 bytes of
	// encoding are a 2-byte UTF character)
	// Format of encoding: 0b110YYYYY 0b10xxxxxx
	// Want to construct an integer out of the 11 bits of the actual code point: YYYYYxxxxxx
	uint16_t result = 0b0000000000000000;
	result += (encoding[1] & 0b00111111);
	result += (((uint16_t)(encoding[0] & 0b00011111)) << 6);
	return result;	
}

