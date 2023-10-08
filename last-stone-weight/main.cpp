#include <iostream>

using namespace std;

class Solution
{
public:
    int lastStoneWeight(vector<int> &stones)
    {

        priority_queue<int> stonesPq;

        for (auto i : stones)
        {
            stonesPq.push(i);
        }

        if (stones.size() == 1)
            return stones[0];

        while (!stonesPq.empty())
        {
            int e1 = stonesPq.top();
            stonesPq.pop();
            int e2 = stonesPq.top();
            stonesPq.pop();

            if (stonesPq.empty())
            {
                return e1 - e2;
            }

            stonesPq.push(e1 - e2);
        }

        return 0;
    }
};

int main()
{
    vector<int> stones{2, 7, 4, 1, 8, 1};

    Solution s;
    s.lastStoneWeight(stones);
}