#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>

int score_word(string word, char letters[], int scores[]);
void print_result(int score_1, int score_2);

int main(void)
{
    // Letters of the alphabet and their corresponding scores
    char letters[] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm',
                      'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'};
    int scores[] = {1, 3, 3, 2, 1, 4, 2, 4, 1, 8, 5, 1, 3, 1, 1, 3, 10, 1, 1, 1, 1, 4, 4, 8, 4, 10};

    // Prompt the user for two words
    string word_1 = get_string("Player 1: ");
    string word_2 = get_string("Player 2: ");

    // Compute the score of each word
    int score_1 = score_word(word_1, letters, scores);
    int score_2 = score_word(word_2, letters, scores);

    // Print the winner
    print_result(score_1, score_2);
}

int score_word(string word, char letters[], int scores[])
{
    int score = 0;

    // Compute score for each character in the word
    for (int i = 0, n = strlen(word); i < n; i++)
    {
        for (int j = 0; j < 26; j++)
        {
            if (tolower(word[i]) == letters[j])
            {
                score += scores[j];
                continue;
            }
        }
    }
    return score;
}

void print_result(int score_1, int score_2)
{
    if (score_1 > score_2)
    {
        printf("Player 1 wins!\n");
    }
    else if (score_1 < score_2)
    {
        printf("Player 2 wins!\n");
    }
    else
    {
        printf("Tie!\n");
    }
}
