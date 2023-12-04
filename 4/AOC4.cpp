#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <map>
#include <set>
#include <sstream>
#include <regex>
#include <numeric>
#include <cmath>

using namespace std;

int main()
{
    ifstream file("input");
    string line;
    vector<string> lines;
    while (getline(file, line))
    {
        lines.push_back(line);
    }
    file.close();

    int points = 0;

    // Vector of tuples with a string for the card, two int vectors for the numbers,
    // the number of winning numbers and an int marking the number of copies received
    // for the next iteration
    vector<tuple<string, vector<int>, vector<int>, int, int>> cards;

    // Loop through lines
    for (int i = 0; i < lines.size(); i++)
    {
        // Split the line at ':' into two strings
        string card = lines[i].substr(0, lines[i].find(':'));
        string numbers = lines[i].substr(lines[i].find(':') + 1);

        // Remove all extra whitespaces
        card = std::regex_replace(card, std::regex("^ +| +$|( ) +"), "$1");
        numbers = std::regex_replace(numbers, std::regex("^ +| +$|( ) +"), "$1");

        // Split the numbers string at '|' into two strings
        string winning = numbers.substr(0, numbers.find('|'));
        string youhave = numbers.substr(numbers.find('|') + 1);

        // Remove all extra whitespaces
        winning = std::regex_replace(winning, std::regex("^ +| +$|( ) +"), "$1");
        youhave = std::regex_replace(youhave, std::regex("^ +| +$|( ) +"), "$1");

        // Split winning at ' ' into an arbitrary number of strings
        vector<int> winning_split;
        stringstream winning_stream(winning);
        string temp;
        while (winning_stream >> temp)
        {
            winning_split.push_back(stoi(temp));
        }

        // Split youhave at ' ' into an arbitrary number of strings
        vector<int> youhave_split;
        stringstream youhave_stream(youhave);
        while (youhave_stream >> temp)
        {
            youhave_split.push_back(stoi(temp));
        }

        // Print the card and the two numbers
        cout << card << "; " << winning << "; " << youhave << endl;

        // For each number in youhave compare it to the numbers in winning and count
        // the number of matches
        int matches = 0;
        for (int j = 0; j < youhave_split.size(); j++)
        {
            for (int k = 0; k < winning_split.size(); k++)
            {
                if (youhave_split[j] == winning_split[k])
                {
                    matches++;
                }
            }
        }

        // Add card to vector
        cards.push_back(make_tuple(card, winning_split, youhave_split, matches, 1));

        points += matches == 0 ? 0 : 1 << (matches - 1);
    }

    cout << "Points: " << points << endl;

    // Loop through cards again
    for (int i = 0; i < cards.size(); i++)
    {
        // If number of matches is 0, continue
        if (get<3>(cards[i]) == 0)
        {
            continue;
        }

        // Set the number of copies received to 0

        // Loop through cards below the current card for the number of matches
        for (int j = i + 1; j < min(i + 1 + get<3>(cards[i]), (int) cards.size()); j++)
        {
            // Increment the number of copies by the number of copies of the current card
            get<4>(cards[j]) += get<4>(cards[i]);
        }
    }

    // Sum the number of copies received for each card
    int copies = 0;
    for (int i = 0; i < cards.size(); i++)
    {
        copies += get<4>(cards[i]);
    }

    cout << "Copies: " << copies << endl;

    return 0;
}