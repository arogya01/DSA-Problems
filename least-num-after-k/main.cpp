#include <iostream>
#include <vector>
#include <unordered_map>
#include <map>
#include <algorithm>
using namespace std;

class Solution
{
public:
    int findLeastNumOfUniqueInts(vector<int> &arr, int k)
    {

        // Step 1: Store frequencies in a map
        std::map<int, int> frequencyMap;
        for (int num : arr)
        {
            frequencyMap[num]++;
        }

        // Step 2: Transfer to a vector of pairs
        std::vector<std::pair<int, int>> freqVec(frequencyMap.begin(), frequencyMap.end());

        // Step 3: Sort the vector by frequency
        std::sort(freqVec.begin(), freqVec.end(),
                  [](const std::pair<int, int> &a, const std::pair<int, int> &b)
                  {
                      return a.second < b.second; // Sort in descending order of frequency
                  });

        // Print the sorted frequencies
        for (auto &p : freqVec)
        {

            k = k - p.second;
            p.second = 0;
            if (k <= 0)
            {
                p.second = p.second - k;
                break;
            }
        }

        int ans = 0;
        for (const auto &p : freqVec)
        {
            if (p.second != 0)
            {
                ans++;
            }
        }

        return ans;
    }
};

int main()
{
    Solution s;
    vector<int> sample{5, 5, 4};
    s.findLeastNumOfUniqueInts(sample, 1);
}