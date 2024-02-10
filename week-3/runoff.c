#include <cs50.h>
#include <stdio.h>
#include <strings.h>

// Max voters and candidates
#define MAX_VOTERS 100
#define MAX_CANDIDATES 9

// preferences[i][j] is jth preference for voter i
int preferences[MAX_VOTERS][MAX_CANDIDATES];

// Candidates have name, vote count, eliminated status
typedef struct
{
    string name;
    int votes;
    bool eliminated;
} candidate;

// Array of candidates
candidate candidates[MAX_CANDIDATES];

// Numbers of voters and candidates
int voter_count;
int candidate_count;

// Function prototypes
bool vote(int voter, int rank, string name);
void tabulate(void);
bool print_winner(void);
int find_min(void);
bool is_tie(int min);
void eliminate(int min);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: runoff [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
    candidate_count = argc - 1;
    if (candidate_count > MAX_CANDIDATES)
    {
        printf("Maximum number of candidates is %i\n", MAX_CANDIDATES);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i].name = argv[i + 1];
        candidates[i].votes = 0;
        candidates[i].eliminated = false;
    }

    voter_count = get_int("Number of voters: ");
    if (voter_count > MAX_VOTERS)
    {
        printf("Maximum number of voters is %i\n", MAX_VOTERS);
        return 3;
    }

    // Keep querying for votes per voter
    for (int i = 0; i < voter_count; i++)
    {

        // Query for each voter's rank
        for (int j = 0; j < candidate_count; j++)
        {
            string name = get_string("Rank %i: ", j + 1);

            // Record vote, unless it's invalid
            if (!vote(i, j, name))
            {
                printf("Invalid vote.\n");
                return 4;
            }
        }

        printf("\n");
    }

    // Keep holding runoffs until winner exists
    while (true)
    {
        // Calculate votes given remaining candidates
        tabulate();

        // Check if election has been won
        bool won = print_winner();
        if (won)
        {
            break;
        }

        // Eliminate last-place candidates
        int min = find_min();
        bool tie = is_tie(min);

        // If tie, everyone wins
        if (tie)
        {
            for (int i = 0; i < candidate_count; i++)
            {
                if (!candidates[i].eliminated)
                {
                    printf("%s\n", candidates[i].name);
                }
            }
            break;
        }

        // Eliminate anyone with minimum number of votes
        eliminate(min);

        // Reset vote counts back to zero
        for (int i = 0; i < candidate_count; i++)
        {
            candidates[i].votes = 0;
        }
    }
    return 0;
}

// Record preference if vote is valid
bool vote(int voter, int rank, string name)
{
    // Loop through each candidate
    for (int c = 0; c < candidate_count; c++)
    {
        if (strcasecmp(name, candidates[c].name) == 0)
        {
            preferences[voter][rank] = c; // Record rank
            return true;
            break;
        }
    }
    return false;
}

void tabulate(void)
{
    // loop through each voter
    for (int v = 0; v < voter_count; v++)
    {
        // loop through each candidate to determine if rth choice for voter
        for (int c = 0, r = 0; c < candidate_count; c++)
        {
            if (preferences[v][r] == c) // check if candidate's name matches
            {
                if (!candidates[c].eliminated) // if name matches, check if candidate is eliminated
                {
                    candidates[c].votes++; // add votes to candidate if not eliminated
                    break;
                }
                else
                {
                    r++;    // if eliminated, go to next voter's next rank choice
                    c = -1; // reset candidate loop for next rank
                }
            }
        }
    }
    return;
}

// Print the winner of the election, if there is one
bool print_winner(void)
{
    // Loop through each candidate to check if they have majority of votes
    for (int c = 0; c < candidate_count; c++)
    {
        // If candidate has majority of votes, return true
        if (candidates[c].votes > voter_count / 2)
        {
            printf("%s\n", candidates[c].name); // Print candidate's name as winner
            return true;
            break;
        }
    }
    return false;
}

// Return the minimum number of votes any remaining candidate has
int find_min(void)
{
    int least_votes = voter_count;
    // Loop through each candidate
    for (int c = 0; c < candidate_count; c++)
    {
        if (!candidates[c].eliminated)
        {
            // Determine lowest votes
            if (candidates[c].votes < least_votes)
            {
                least_votes = candidates[c].votes;
            }
        }
    }
    return least_votes;
}

// Return true if the election is tied between all candidates, false otherwise
bool is_tie(int min)
{
    int num_candidates = 0;   // Number of candidates with the least votes
    int eliminated_count = 0; // Number of candidates who are eliminated
    // Loop through each candidate to find candidate(s) with least votes
    for (int c = 0; c < candidate_count; c++)
    {
        if (candidates[c].eliminated) // Tally number of eliminated candidates
        {
            eliminated_count++;
        }
        if (candidates[c].votes == min) // Tally number of candidates with minimum votes
        {
            num_candidates++;
        }
    }
    // Calculate if number of candidates with minimum votes is the same as number of remaining candidates
    if (num_candidates == candidate_count - eliminated_count)
    {
        return true; // If yes, then tie
    }
    else
    {
        return false; // If not, no tie
    }
}

// Eliminate the candidate (or candidates) in last place
void eliminate(int min)
{
    // Loop through candidates to see if they have the least votes
    for (int c = 0; c < candidate_count; c++)
    {
        if (candidates[c].votes == min)
        {
            candidates[c].eliminated = true; // Eliminate candidates with least votes
        }
    }
    return;
}
