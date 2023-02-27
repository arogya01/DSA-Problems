#include <bits/stdc++.h>

using namespace std;

class Solution
{
public:
    int maxFrequency(vector<int> &A, int k)
    {

        sort(begin(A), end(A));
        long i = 0, N = A.size(), ans = 1, sum = 0;
        for (int j = 0; j < N; ++j)
        {
            sum += A[j];
            while ((j - i + 1) * A[j] - sum > k)
                sum -= A[i++];
            ans = max(ans, j - i + 1);
        }
        return ans;

        // sort(nums.begin(), nums.end());
        // long freq = 1;
        // long sum = 0;
        // long i = 0;
        // for (int j = 0; j < nums.size(); ++j)
        // {
        //     sum += nums[j];
        //     while ((j - i + 1) * nums[j] - sum > k)
        //     {
        //         sum -= nums[i];
        //         i++;
        //     }
        //     freq = max(freq, j - i + 1);
        // }

        // return freq;
    }
};

int main()
{
    vector<int> numbers = {9930, 9923, 9983, 9997, 9934, 9952, 9945, 9914, 9985, 9982, 9970, 9932, 9985, 9902, 9975, 9990, 9922, 9990, 9994, 9937, 9996, 9964, 9943, 9963, 9911, 9925, 9935, 9945, 9933, 9916, 9930, 9938, 10000, 9916, 9911, 9959, 9957, 9907, 9913, 9916, 9993, 9930, 9975, 9924, 9988, 9923, 9910, 9925, 9977, 9981, 9927, 9930, 9927, 9925, 9923, 9904, 9928, 9928, 9986, 9903, 9985, 9954, 9938, 9911, 9952, 9974, 9926, 9920, 9972, 9983, 9973, 9917, 9995, 9973, 9977, 9947, 9936, 9975, 9954, 9932, 9964, 9972, 9935, 9946, 9966};
    vector<int> vec{1, 2, 4};

    Solution s1;
    cout << s1.maxFrequency(vec, 5);
}