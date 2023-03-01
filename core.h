/*
*****************************************************************************
The following functions are all toolbox functions, they can be used to do
         tasks like clearing the input buffer, validation, etc.
*****************************************************************************
*/

#ifndef CORE_H
#define CORE_H

//////////////////////////////////////
// USER INTERFACE FUNCTIONS
//////////////////////////////////////

// Clear the standard input buffer
void clearInputBuffer(void);

// Wait for user to input the "enter" key to continue
void suspend(void);

// Makes sure phone number is 10 chars and only number chars
void displayFormattedPhone (const char *stringPTR);


//////////////////////////////////////
// USER INPUT FUNCTIONS
//////////////////////////////////////
int inputInt (void);

// Checks if input is positive
int inputIntPositive (void);

// Checks if integer is in range of lowerBound and upperBound
int inputIntRange (int lowerBound, int upperBound);

// Checks if entered char is one of the valid chars
char inputCharOption (const char validChars[]);

// Checks if inputted string is between the two bounds
void inputCString (char *stringPTR, int minChars, int maxChars, int mode);

void inputPhoneNumber (char *stringPTR, int maxLength);

#endif // !CORE_H
