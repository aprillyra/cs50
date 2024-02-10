#include <cs50.h>
#include <stdio.h>

// prototypes
int get_change(void);
int get_quarter_amount(int cents_owed);
int get_change_after_quarters(int cents_owed, int amount_of_quarters);
int get_nickles_amount(int remaining_after_quarters);
int get_change_after_nickles(int remaining_after_quarters, int amount_of_nickles);
int get_dime_amount(int remaining_after_dimes);
int get_change_after_dimes(int remaining_after_nickles, int amount_of_dimes);
int add_coins(int amount_of_quarters, int amount_of_nickles, int amount_of_dimes, int pennies);

int main(void)
{
    // prompt the user for the change owed (reprompt if not >0)
    int cents_owed = get_change();
    // calculate number of quarters to give to customer
    int amount_of_quarters = get_quarter_amount(cents_owed);
    // calculate how much change is remaining after quarters are given to customer
    int remaining_after_quarters = get_change_after_quarters(cents_owed, amount_of_quarters);
    // calculate number of nickles to give to customer
    int amount_of_nickles = get_nickles_amount(remaining_after_quarters);
    // calculate how much change is remaining after nickles are given to customer
    int remaining_after_nickles = get_change_after_nickles(remaining_after_quarters, amount_of_nickles);
    // calculate number of dimes to give to customer
    int amount_of_dimes = get_dime_amount(remaining_after_nickles);
    // calculate how much change is remaining after dimes are given to customer
    int pennies = get_change_after_dimes(remaining_after_nickles, amount_of_dimes);
    // add number of quarters, nickles, dimes, pennies
    int number_of_coins = add_coins(amount_of_quarters, amount_of_nickles, amount_of_dimes, pennies);
    // print number of coins to give customer
    printf("%i\n", number_of_coins);
}

// ask customer how much change in cents they're owed and return value
int get_change(void)
{
    int cents_owed;
    do
    {
        cents_owed = get_int("How many cents are you owed? ");
    }
    while (cents_owed < 0);
    return cents_owed;
}

// return the number of quarters given to customer
int get_quarter_amount(int cents_owed)
{
    // calculate number of quarters given to customer
    int number_of_quarters = cents_owed / 25;
    return number_of_quarters;
}

// return remaining amount of change owed after quarters are givenn
int get_change_after_quarters(int cents_owed, int amount_of_quarters)
{
    // find out the value of quarters
    int value_of_quarters = amount_of_quarters * 25;
    // subtract value of quarters from changed owed
    int remaining_after_quarters = cents_owed - value_of_quarters;
    return remaining_after_quarters;
}

// return number of nickles given to customer
int get_nickles_amount(int remaining_after_quarters)
{
    int number_of_nickles = remaining_after_quarters / 10;
    return number_of_nickles;
}

// return remaining amount of change owed after nickles are givenn
int get_change_after_nickles(int remaining_after_quarters, int amount_of_nickles)
{
    // find out the value of nickles
    int value_of_nickles = amount_of_nickles * 10;
    // subtract value of nickles from changed owed
    int remaining_after_nickles = remaining_after_quarters - value_of_nickles;
    return remaining_after_nickles;
}

// return number of dimes given to customer
int get_dime_amount(int remaining_after_dimes)
{
    int amount_of_dimes = remaining_after_dimes / 5;
    return amount_of_dimes;
}

// return pennies (amount and value the same)
int get_change_after_dimes(int remaining_after_nickles, int amount_of_dimes)
{
    int value_of_dimes = amount_of_dimes * 5;
    int pennies = remaining_after_nickles - value_of_dimes;
    return pennies;
}

// return number of coins
int add_coins(int amount_of_quarters, int amount_of_nickles, int amount_of_dimes, int pennies)
{
    int number_of_coins = amount_of_quarters + amount_of_nickles + amount_of_dimes + pennies;
    return number_of_coins;
}
