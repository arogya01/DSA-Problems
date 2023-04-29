#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;

class Solution
{
public:
    vector<int> findThePrefixCommonArray(vector<int> &A, vector<int> &B)
    {
        unordered_map<int, int> tracker1;
        unordered_map<int, int> tracker2;

        for (int i = 0; i < A.size(); i++)
        {

            tracker1[A[i]] = i;
        }

        for (int i = 0; i < B.size(); i++)
        {
            tracker2[B[i]] = i;
        }

        int n = A.size();
        int common = 0;
        vector<int> ans;
        for (int i = 0; i < n; i++)
        {
            if (A[i] == B[i])
                common++;
            else
            {
                if (tracker2[A[i]] <= i)
                {
                    common++;
                }
                if (tracker1[B[i]] <= i)
                {
                    common++;
                }
            }

            ans.push_back(common);
        }

        return ans;
    }
};

int main()
{
    Solution s;
    vector<int> A{1, 3, 2, 4};
    vector<int> B{3, 1, 2, 4};
    s.findThePrefixCommonArray(A, B);
}