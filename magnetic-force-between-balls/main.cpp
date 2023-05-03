#include <iostream>
#include <vector>

using namespace std;

class Solution
{
public:
    int n, c;
    vector<int> a;

    // check function is to check if we can place cows at a distance of k, it's doing that by checking if the distance between the cows is greater than or equal to k, if it is then we can place cows at a distance of k, if not then we can't place cows at a distance of k.
    bool check(int k)
    {
        int cows = 1;
        int lt = 0;
        for (int i = 1; i < n; i++)
        {
            if (a[i] - a[lt] >= k)
            {
                lt = i;
                cows++;
                if (cows == c)
                    return true;
            }
        }
        return false;
    }

    int maxDistance(vector<int> &position, int m)
    {

        a = position;
        n = a.size();
        c = m;
        sort(a.begin(), a.end());
        int l = 0;
        int r = a[n - 1] - a[0];
        while (l <= r)
        {
            int mid = (l + r) / 2;
            if (check(mid))
                l = mid + 1;
            else
                r = mid - 1;
        }

        return l - 1;
    }
};

int main()
{
    vector<int> position = {1, 2, 3, 4, 7};
    int m = 3;
    Solution sol;
    cout << sol.maxDistance(position, m) << endl;
}