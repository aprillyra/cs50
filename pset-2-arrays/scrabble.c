#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>

// array of points that maps to letters in alphabetical order (ex: a = 1pt, b = 3pts, c = 3pts)
const int POINTS[] = {1, 3, 3, 2, 1, 4, 2, 4, 1, 8, 5, 1, 3, 1, 1, 3, 10, 1, 1, 1, 1, 4, 4, 8, 4, 10};

// prototype for finding the score of a word
int get_score(string w);

// prototype for determining winner
void winner(int s1, int s2);

int main(void)
{
    // prompt user for two words for players 1 & 2
    string words[2];

    words[0] = get_string("Player 1: ");
    words[1] = get_string("Player 2: ");

    // call the score of each word
    int score1 = get_score(words[0]);
    int score2 = get_score(words[1]);

    // call function that prints winner
    winner(score1, score2);
}

// calculate and return score
int get_score(string w)
{
    int score = 0;                       // initalize score
    for (int i = 0; (w[i]) != '\0'; i++) // loop through each char of the word
    {
        // find score for uppercase char
        if (isupper(w[i]))
        {
            int a = (w[i]);             // convert the char to int
            int s = a - 65;             // subtract 65 to find the index of POINT to use in next step
            score += POINTS[s];         // score is score + sth index of POINT
        }
        // find score for lowercase char
        else if (islower(w[i]))
        {
            int a = (w[i]);             // convert the char to int
            int s = a - 97;             // substract 97 (ASCII value of "a") to find which index of POINTS to use in next step
            score += POINTS[s];         // specify the score is score + sth index of POINT
        }
        // anything that isn't an upper or lowercase char scores nothing
        else
        {
            score += 0;
        }
    }
    return score; // return final score
}

// calculate and return winner
void winner(int s1, int s2)
{
    // print player1 as winner
    if (s1 > s2)
    {
        printf("Player 1 wins!\n");
    }
    // print player2 as winner
    else if (s1 < s2)
    {
        printf("Player 2 wins!\n");
    }
    // print tie
    else
    {
        printf("Tie!\n");
    }
}
