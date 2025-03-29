#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>

using namespace std;

// Function to preprocess the pattern and create a bad character table
unordered_map<char, int> createBadCharTable(const string &pattern)
{
    unordered_map<char, int> badChar;
    int m = pattern.length();

    // Initialize all characters to -1 (not found)
    for (int i = 0; i < m; i++)
    {
        // Store the rightmost occurrence of each character
        badChar[pattern[i]] = i;
    }

    return badChar;
}

// Boyer-Moore algorithm with bad character rule
vector<int> boyerMoore(const string &text, const string &pattern)
{
    vector<int> positions;
    int n = text.length();
    int m = pattern.length();

    if (m > n)
        return positions;

    // Preprocess the pattern for bad character rule
    unordered_map<char, int> badChar = createBadCharTable(pattern);

    int s = 0; // s is the shift of the pattern relative to text

    while (s <= (n - m))
    {
        int j = m - 1;

        // Start matching from the rightmost character
        while (j >= 0 && pattern[j] == text[s + j])
        {
            j--;
        }

        if (j < 0)
        {
            // Pattern found at position s
            positions.push_back(s);

            // Shift the pattern to the right by 1
            s += 1;
        }
        else
        {
            // Mismatch occurred, apply bad character rule

            // Get the shift based on the bad character
            char badCharacter = text[s + j];

            // If the bad character is in the pattern, align it
            // Otherwise, shift the pattern past this character
            int shift = j - (badChar.count(badCharacter) ? badChar[badCharacter] : -1);

            // We need to shift at least by 1 to avoid infinite loops
            s += max(1, shift);
        }
    }

    return positions;
}

// Function to visualize the search process
void visualizeSearch(const string &text, const string &pattern, int position)
{
    cout << "Text:    " << text << endl;

    // Print spaces before the pattern to align it
    cout << "Pattern: ";
    for (int i = 0; i < position; i++)
    {
        cout << " ";
    }
    cout << pattern << endl;
}

int main()
{
    string text = "MY EXAMPLE";
    string pattern = "EXAMPLE";

    cout << "Searching for '" << pattern << "' in text:" << endl;
    cout << text << endl
         << endl;

    vector<int> positions = boyerMoore(text, pattern);

    cout << "Pattern found at positions: ";
    for (int pos : positions)
    {
        cout << pos << " ";
    }
    cout << endl
         << endl;

    // Visualize each occurrence
    for (int pos : positions)
    {
        visualizeSearch(text, pattern, pos);
        cout << endl;
    }

    return 0;
}