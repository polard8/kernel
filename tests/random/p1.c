#include <stdio.h>
#include <string.h>

void interpret(char program[]) {

    //Declare variables
    int index = 0;
    int state = 0;
    int digCount = 0;
    char var;
    char full[32];
    char digit[30];
    char table[26][32];

    //Iterates through the table 2D array to make sure all elements
    //are null instead of random values.
    for (int row = 0; row < 26; row++) {
	for (int col = 0; col < 32; col++) {
	    table[row][col] = 0;
	}
    }

    //Iterates through the command line input.
    while (program[index] != 0) {
	//Assigns the char c the next character in the input.
	char c = program[index];

	//Switch statement for multiple states.
	switch(state) {
	    //State 0
	    case 0 :
		//c is a lowercase letter
		if (c >= 97 && c <= 122) {
		    var = c;
		    state++;
		}
		else {
		
		}
		index++;
		break;

	    //State 1
	    case 1 :
		//c is an equal sign
		if (c == 61) {
		    state++;
		}
		else {
		
		}
		index++;
		break;

	    //State 2
	    case 2 :
		//c is a digit from 1 to 9
		if (c >= 49 && c <= 57) {
		    //Add digit to digit array
		    digit[digCount] = c;
		    digCount++;
		    state++;
		}
		//If c is a semicolon reset state
		else if (c == 59) {
		    state = 0;
		    for (int i = 0; i < 30; i++) {
			digit[i] = 0;
		    }
		}
		else {
		
		}
		index++;
		break;

	    //State 3
	    case 3 :
		//c is a semicolon
		if (c == 59) {
		    full[0] = var;
		    full[1] = ':';
		    //Fill up full array with digits
		    for (int i = 2; i < digCount + 2; i++) {
		    	full[i] = digit[i - 2];
		    }
		    int a = 0;
		    //Clears current element
		    if (table[var - 97][0] != 0) {
			for (int i = 0; i < 32; i++) {
			    table[var - 97][i] = 0;
			}
		    }
		    //Fills up current element
		    while (full[a] != 0) {
		        table[var - 97][a] = full[a];
			a++;
		    }
		    //Reset state
		    state = 0;
		    //Clear full array
		    for (int i = 0; i < a; i++) {
			full[i] = 0;
		    }
		    //Clear digit array
		    for (int i = 0; i < 30; i++) {
		        digit[i] = 0;
		    }
		    a = 0;
		    digCount = 0;
		}
		//Account for multiple digits
		else if (c >= 48 && c <= 57) {
		    digit[digCount] = c;
		    digCount++;
		}
		else {
		
		}
		index++;
		break;
	}
    }

    //Iterate through 2D table array and print out nonempty elements.
    for (int row = 0; row < 26; row++) {
	for (int col = 0; col < 32; col++) {
	    if (table[row][col] != 0) {
		printf("%c", table[row][col]);
	    }
	    else {
		if (col != 0) {
		    printf("\n");
		}
		col = 32;
	    }
	}
    }
}

int main(int argc, char* argv[]) {

    interpret(argv[1]);

    return 0;
}
