/*
*****************************************************************************
The following functions are all toolbox functions, they can be used to do
         tasks like clearing the input buffer, validation, etc.
*****************************************************************************
*/

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <string.h>
#include "core.h"



//////////////////////////////////////
// USER INTERFACE FUNCTIONS
//////////////////////////////////////

// Clear the standard input buffer
void clearInputBuffer(void)
{
    // Discard all remaining char's from the standard input buffer:
    while (getchar() != '\n')
    {
        ; // do nothing!
    }
};

// Wait for user to input the "enter" key to continue
void suspend(void)
{
    printf("<ENTER> to continue...");
    clearInputBuffer();
    putchar('\n');
};

// Makes sure phone number is 10 chars and only number chars
void displayFormattedPhone (const char *stringPTR)
{
    const int first3 = 3;
    const int phoneLen = 10;
    int allIntegers = 0;
    int i = 0;

    // Check if string pointer is null
    if (stringPTR != NULL)
    {
        while (stringPTR[i] != '\0')
        {
            // If the index meets the condition, then update allIntegers.
            if (stringPTR[i] >= '0' && stringPTR[i] <= '9')
            {
                // Update allIntegers if the condition is met.
                allIntegers++;
            }
            i++;
        };

        // If the string length is 10 and all the chars are between ASCII 0 and 9, then it will print those chars.
        if (strlen(stringPTR) == 10 && allIntegers == 10)
        {
            for (i = 0; i < first3; i++)
            {
                if (i == 0)
                {
                    printf("(");
                }
                printf("%c", stringPTR[i]);
                if (i == 2)
                {
                    printf(")");
                }
            }

            for (i = first3; i < phoneLen; i++)
            {
                printf("%c", stringPTR[i]);
                // If the iterator is equal to 5 then print the dash.
                if (i == 5)
                {
                    printf("-");
                }
            }
        }
        else
        {
            printf("(___)___-____");
        }
    }
    else
    {
        printf("(___)___-____");
    }
};

//////////////////////////////////////
// USER INPUT FUNCTIONS
//////////////////////////////////////

int inputInt (void)
{
    char newline = '\0'; // null terminator
    int value = 0;
    int flag = 0;

    do {
        scanf("%d%c", &value, &newline);

        if (newline != '\n')
        {
            clearInputBuffer();
            printf("Error! Input a whole number: ");
        }
        else
        {
            flag = 1;
        }

    } while (flag == 0);

    return value;
};

// Checks if input is positive
int inputIntPositive (void)
{
    int value = 0;
    int flag = 0;

    do
    {
        value = inputInt();

        if (value < 0)
        {
            printf("ERROR! Value must be > 0: ");
        }
        else
        {
            flag = 1;
        }

    } while (flag == 0);

    return value;
};

// Checks if integer is in range of lowerBound and upperBound
int inputIntRange (int lowerBound, int upperBound)
{
    int flag = 0;
    int value = 0;

    do
    {

        value = inputInt();

        if (value < lowerBound || value > upperBound)
        {
            printf("ERROR! Value must be between %d and %d inclusive: ", lowerBound, upperBound);
        }
        else
        {
            flag = 1;
        }


    } while (flag == 0);

    return value;

};

// Checks if entered char is one of the valid chars
char inputCharOption (const char validChars[])
{
    char enteredChar[5]; // Allocating 5 spaces to the string
    int flag = 0;
    int i = 0;

    do
    {
        scanf(" %5s", enteredChar); // Accepts up till 5 chars
        clearInputBuffer();

        i = 0;

        while(validChars[i]!='\0')
        {
            if (strlen(enteredChar) == 1 && enteredChar[0] == validChars[i])    // If the string length is 1 and the character entered at position 0 is
            {                                                                       // one of the valid chars
                flag = 1;
            }
            i++;
        }

        if (flag == 0)
        {
            printf("ERROR: Character must be one of [%s]: ", validChars);
        }

    } while (flag == 0);

    return enteredChar[0]; // Returns the first character in the string
};

// Checks if inputted string is between the two bounds
void inputCString (char *stringPTR, int minChars, int maxChars, int mode)
{
    char enteredString[100];
    int flag = 0;

    do {

        // takes up till 100 characters as a string till a \n
        scanf(" %99[^\n]", enteredString);
        clearInputBuffer();

        if (strlen(enteredString) >= minChars && strlen(enteredString) <= maxChars)
        {
            // Assigning entered string to stringPTR
            strcpy(stringPTR, enteredString);

            // Exits Loop
            flag = 1;
        }
        else if (mode == 1)
        {
            printf("Invalid 10-digit number! Number: ");
        }
        else if (minChars == maxChars)
        {
            printf("ERROR: String length must be exactly %d chars: ", maxChars);
        }
        else if (strlen(enteredString) > maxChars)
        {
            printf("ERROR: String length must be no more than %d chars: ", maxChars);
        }
        else
        {
            printf("ERROR: String length must be between %d and %d chars: ", minChars, maxChars);
        }

    } while (flag == 0);
};

void inputPhoneNumber (char *stringPTR, int maxLength)
{
    char enteredString[15];
    int flag = 0;

    do {

        // takes up till 100 characters as a string till a \n
        scanf(" %15[^\n]", enteredString);
        clearInputBuffer();

        if (strlen(enteredString) != maxLength)
        {
            printf("Invalid 10-digit number! Number: ");
        }
        else
        {
            // Assigning entered string to stringPTR
            strcpy(stringPTR, enteredString);

            // Exits Loop
            flag = 1;
        }

    } while (flag == 0);
};