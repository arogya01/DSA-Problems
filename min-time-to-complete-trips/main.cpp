#include <iostream>
#include <vector>
using namespace std;

class Solution
{
public:
    long long minimumTime(vector<int> &time, int totalTrips)
    {

        long long l = 0;
        long long r = 1LL * time[0] * totalTrips;
        while (l < r)
        {
            long long m = l + (r - l) / 2, trips = 0;
            cout << "the details are :" << l << " " << m << " " << r << endl;
            for (auto x : time)
                trips += (m / x);
            if (trips < totalTrips)
                l = m + 1;
            else
                r = m;
        }
        return l;
    }
};

int main()
{
    Solution s;
    vector<int> time = {5, 10, 10};
    cout << s.minimumTime(time, 9);
    return 0;
}