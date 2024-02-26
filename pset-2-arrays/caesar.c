#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// prototypes
bool digits_only(string s);
string get_plaintext(void);
char encipher(char p, int k);

// take user input at command line
int main(int argc, string argv[])
{
    if (argc != 2) // return error and reprompt if user inputs more than one string at the command line
    {
        printf("Enter one string (ex: ./caesar 8)\n");
        return 1;
    }

    // check if command line input is a digit
    if (!digits_only(argv[1]))
    {
        printf("Usage: ./caesar key\n"); // print error if command line input is not a digit
        return 1;
    }

    int key = atoi(argv[1]); // convert input from string to int

    string plaintext = get_plaintext(); // prompt user for plaintext

    // print ciphertext
    printf("ciphertext: ");
    for (int i = 0, l = strlen(plaintext); i < l; i++) // loop through all chars in plaintext
    {
        char cipher = encipher(plaintext[i], key); // encipher character
        printf("%c", cipher);                      // print enciphered character
    }
    printf("\n");
}

// return true if command line input is a digit
bool digits_only(string s)
{
    bool is_digits_only;
    int i = 0;
    int l = strlen(s);
    do
    {
        if (isdigit(s[i])) // loop through all chars in command line input to check if a digit
        {
            i++;
            is_digits_only = true;
        }
        else
        {
            is_digits_only = false;
            break;
        }
    }
    while (i < l);
    return is_digits_only;
}

// return user-inputted plain text
string get_plaintext(void)
{
    string plaintext = get_string("plaintext:  ");
    return plaintext;
}

// encipher character
char encipher(char p, int k)
{
    char c;         // initalize char to return
    if (isalpha(p)) // check if char is a letter in the alphabet
    {
        if (isupper(p)) // check if char is an uppercase letter
        {
            int ul = p - 'A';          // convert ascii to alphabetical index (ex: A = 0, B = 1, etc)
            int shift = (ul + k) % 26; // shift alphabetical index position using formula: ciphertext[i] = (plaintext[i] + key) % 26;
            c = shift + 'A';           // convert result back to ascii
        }
        else // if (islower(p)) // check if char is an lowercase letter
        {
            int ll = p - 'a';          // convert ascii to alphabetical index (ex: a = 0, b = 1, etc)
            int shift = (ll + k) % 26; // shift alphabetical index position using formula: ciphertext[i] = (plaintext[i] + key) % 26;
            c = shift + 'a';           // convert result back to ascii
        }
    }
    else
    {
        c = p; // if not alphabetical, remains the same
    }
    return c;
}