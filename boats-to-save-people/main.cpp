#include <iostream>
#include <vector>

using namespace std;

class Solution
{
public:
    int numRescueBoats(vector<int> &people, int limit)
    {
        sort(people.begin(), people.end());
        int count = 0;
        int i = 0;
        int j = people.size() - 1;

        while (i <= j)
        {
            if (i == j && people[i] == limit)
            {
                count++;
                break;
            }

            if (people[i] + people[j] <= limit)
            {
                i++;
                j--;
            }
            else
            {
                j--;
            }

            count++;
        }

        return count;
    }
};

int main()
{

    vector<int> sample{1, 2, 4, 5};
    // will going from start to end, and then from end to start solve this problem for all the
    // cases??

    // {1,2,2,3}

    Solution s;
    cout << s.numRescueBoats(sample, 6);
}