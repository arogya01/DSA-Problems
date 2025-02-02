#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Solution
{
public:
    int ansTime(int eventTime, int k, vector<int> &st, vector<int> &et)
    {
        int n = st.size();
        vector<int> gaps(n + 1);

        // Compute gaps
        gaps[0] = st[0];
        gaps[n] = eventTime - et[n - 1];
        for (int i = 1; i < n; i++)
        {
            gaps[i] = st[i] - et[i - 1];
        }

        // Sliding window of size k + 1
        int window = 0;
        for (int i = 0; i <= k; i++)
        {
            window += gaps[i];
        }

        int ans = window;
        for (int i = k + 1; i <= n; i++)
        {
            window += gaps[i] - gaps[i - (k + 1)];
            ans = max(ans, window);
        }

        return ans;
    }
};

int main()
{
    Solution sol;
    int eventTime = 5;
    int k = 1;
    vector<int> st = {1, 3};
    vector<int> et = {2, 5};
    int result = sol.ansTime(eventTime, k, st, et);
    cout << "Maximum free time: " << result << endl;
    return 0;
}