#include <iostream>
#include <string>
#include <vector>
using namespace std;

long getMaxCost(string fileBlocks)
{
    int n = fileBlocks.size();
    int k = 0;
    int positions[1000];
    for (int i = 0, j = 0; i < n; i++)
    {
        if (fileBlocks[i] == '1')
        {
            positions[j++] = i;
            k++;
        }
    }

    // Count groups of consecutive 1s
    int groups = 0;
    for (int i = 0; i < n; i++)
    {
        if (fileBlocks[i] == '1' && (i == 0 || fileBlocks[i - 1] == '0'))
        {
            groups++;
        }
    }

    long total_cost = 0;
    // Cost for moving each '1' to its final position
    for (int i = 0; i < k; i++)
    {
        int finalPos = n - k + i;
        total_cost += 1 + (finalPos - positions[i]);
    }

    // Add cost for connections between groups
    // Each group of consecutive 1s needs an additional connection
    total_cost += groups;

    return total_cost;
}

long long getMaxRearrangementCost(const string &fileBlocks)
{
    int n = (int)fileBlocks.size();

    // Gather positions of 0s and 1s
    vector<int> zPos; // positions of '0'
    vector<int> oPos; // positions of '1'

    for (int i = 0; i < n; i++)
    {
        if (fileBlocks[i] == '0')
        {
            zPos.push_back(i);
        }
        else
        {
            oPos.push_back(i);
        }
    }

    int Z = (int)zPos.size(); // number of zeros
    int O = (int)oPos.size(); // number of ones

    // Final indices for zeros: 0..Z-1
    // Final indices for ones:  Z..(Z+O-1) == Z..(n-1)

    // We'll pair in a way that yields max sum of |i - j|:
    // Sort original positions ascending, final positions ascending,
    // then match largest with smallest, etc.

    // 1) Sort the original positions of zeros ascending
    sort(zPos.begin(), zPos.end());
    //   final zero positions (ascending) are [0, 1, 2, ..., Z-1]

    // 2) Sort the original positions of ones ascending
    sort(oPos.begin(), oPos.end());
    //   final one positions (ascending) are [Z, Z+1, ..., n-1]

    long long cost = 0;

    // --- Compute cost contribution for zeros ---
    // Pair zPos[i] with the final index "i" in reversed order or direct?
    // Let's do a neat trick: If you want largest-with-smallest, you can
    // either reverse zPos or "reverse" the final index. E.g.:
    // cost += abs( zPos[i] - (Z-1 - i) )  for i in [0..Z-1]
    //   That effectively pairs the largest zPos with 0, next largest with 1, etc.

    for (int i = 0; i < Z; i++)
    {
        int originalIndex = zPos[i];
        int finalIndex = (Z - 1) - i; // reversed final slot
        cost += llabs((long long)originalIndex - finalIndex);
    }

    // --- Compute cost contribution for ones ---
    // final one slots are [Z..n-1]. We'll do the same idea: pair largest oPos with smallest final slot.
    // so if i runs from 0..O-1 in ascending, final slot in ascending is Z+i,
    // to do largest-with-smallest, use finalIndex = ( (Z + O - 1) - i ).

    for (int i = 0; i < O; i++)
    {
        int originalIndex = oPos[i];
        int finalIndex = ((Z + O - 1) - i); // reversed
        cost += llabs((long long)originalIndex - finalIndex);
    }

    return cost;
}

int main()
{
    cout << getMaxRearrangementCost("110100") << endl; // current output - 12, expected -  13
    cout << getMaxRearrangementCost("01110") << endl;  // current output - 6, expected -  6
    cout << getMaxRearrangementCost("10100") << endl;  // current output - 8, expected -  8
    return 0;
}