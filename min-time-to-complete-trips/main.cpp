#include <bits/stdc++.h>
using namespace std;

class Solution
{
public:
    long long minimumTime(vector<int> &time, int totalTrips)
    {

        sort(time.begin(), time.end());
        if (totalTrips == 1)
            return time[0];
        long long total = 0, minTime = time[0];
        long long cur = time[0];
        while (total < totalTrips)
        {
            for (int i = 0; i < time.size(); i++)
            {
                if (cur % time[i] == 0)
                {
                    cout << cur << " " << time[i] << endl;
                    total++;
                }
            }

            cur++;
            minTime++;
        }
        cout << cur << endl;
        cout << "total is : " << total << endl;

        return minTime - 1;
    }
};

int main()
{
    Solution s;
    vector<int> time = {5, 10, 10};
    cout << s.minimumTime(time, 9);
    return 0;
}