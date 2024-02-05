#include <cs50.h>
#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

// prototypes
string get_text(void);
int get_letter_count(string t);
int get_word_count(string t);
int get_sentence_count(string t);
int compute_coleman_liau(float lc, float wc, float sc);
void print_grade(int cl);

int main(void)
{
    // prompt the user for some text
    string text = get_text();

    // count the number of uppercase and lowercase letters in text
    int letter_count = get_letter_count(text);

    // count the number of words in a text
    int word_count = get_word_count(text);

    // count the number of sentences in the text
    int sentence_count = get_sentence_count(text);

    // compute the Coleman-Liau index
    int coleman_liau = compute_coleman_liau(letter_count, word_count, sentence_count);

    // print the grade level
    print_grade(coleman_liau);
}

// prompt user to enter text
string get_text(void)
{
    string text;
    text = get_string("Text: ");
    return text;
}

// return letter count in user-entered text
int get_letter_count(string t)
{
    int letter_count = 0;
    for (int i = 0, l = strlen(t); i < l; i++) // loop through all chars in text to find letters
    {
        if (isalpha(t[i]))
        {
            letter_count += 1; // add 1 to letter count if letter
        }
    }
    return letter_count;
}

// return word count in user-entered text
int get_word_count(string t)
{
    int spaces = 0;
    for (int i = 0, l = strlen(t); i < l; i++) // loop through all chars in text to find number of spaces
    {
        if (isspace(t[i]))
        {
            spaces += 1; // add 1 to number of spaces
        }
    }
    int word_count = spaces + 1; // to get word count, add 1 to number of spaces
    return word_count;
}

// return sentence count in text
int get_sentence_count(string t)
{
    int sentences = 0;
    for (int i = 0, l = strlen(t); i < l;
         i++) // loop through all chars in text to find period, exclaimation marks, or question marks
    {
        if (t[i] == 46 || t[i] == 33 || t[i] == 63) // ascii values for . ! ?
        {
            sentences += 1;
        }
    }
    return sentences;
}

// Coleman-Liau index = 0.0588 * L - 0.296 * S - 15.8
// L is the average number of letters per 100 words in the text,
// S is the average number of sentences per 100 words in the text.
int compute_coleman_liau(float lc, float wc, float sc) // letter count, word count, sentence count
{
    float coleman_liau;
    float l;
    float s;
    float times_100_words = wc / 100;             // calculate how many times 100 words appears in text
    l = lc / times_100_words;                     // calculate L of coleman-liau
    s = sc / times_100_words;                     // calculate S of coleman-liau
    coleman_liau = 0.0588 * l - 0.296 * s - 15.8; // plug numbers intoo coleman-liau formula
    return round(coleman_liau);                   // round up coleman-liau result
}

// print the grade level
void print_grade(int cl)
{
    if (cl > 0 && cl < 16) // print grade if between 1 - 15
    {
        printf("Grade %i\n", cl);
    }
    else if (cl < 1)
    {
        printf("Before Grade 1\n"); // print if grade is under 1
    }
    else
    {
        printf("Grade 16+\n"); // print if grade is above 16
    }
}
