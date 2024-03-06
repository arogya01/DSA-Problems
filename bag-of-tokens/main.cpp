#include <iostream>

using namespace std;

class Solution
{
public:
    int bagOfTokensScore(vector<int> &tokens, int power)
    {
        int score = 0;
        sort(tokens.begin(), tokens.end());

        if (power < tokens[0])
            return 0;

        if (tokens.size() == 2)
        {
            return power - tokens[0] > tokens[1] ? 2 : 1;
        }

        int left = 0;
        int right = tokens.size() - 1;

        while (left <= right)
        {
            cout << "score is: " << score << endl;
            if (power >= tokens[left])
            {
                score++;
                left++;
                power = power - tokens[left];
            }
            else if (score >= 1)
            {
                power += tokens[right];
                right--;
                score--;
            }
        }

        return score;
    }
};

int main()
{
    vector<int> tokens{100, 200, 300, 400};
    int power = 200;

    Solution s;

    s.bagOfTokensScore(tokens, power);
}