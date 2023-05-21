#include <iostream>
#include <vector>

using namespace std;

class Solution
{
public:
    bool isValidSudoku(vector<vector<char>> &board)
    {
        vector<int> n(10, 0);

        for (int i = 0; i < 9; i++)
        {
            std::fill(n.begin(), n.end(), 0);
            for (int j = 0; j < 9; j++)
            {
                if (board[i][j] == '.')
                    continue;
                int index = board[i][j] - '0';
                if (n[index] == 1)
                    return false;
                else
                    n[index] = 1;
            }
        }

        for (int i = 0; i < 9; i++)
        {
            std::fill(n.begin(), n.end(), 0);
            for (int j = 0; j < 9; j++)
            {
                if (board[j][i] == '.')
                    continue;

                int index = board[j][i] - '0';
                if (n[index] == 1)
                    return false;
                else
                    n[index] = 1;
            }
        }

        return true;
    }
};

int main()
{
    Solution s;
    vector<vector<char>> board{
        {'5', '3', '.', '.', '7', '.', '.', '.', '.'}, {'6', '.', '.', '1', '9', '5', '.', '.', '.'}, {'.', '9', '8', '.', '.', '.', '.', '6', '.'}, {'8', '.', '.', '.', '6', '.', '.', '.', '3'}, {'4', '.', '.', '8', '.', '3', '.', '.', '1'}, {'7', '.', '.', '.', '2', '.', '.', '.', '6'}, {'.', '6', '.', '.', '.', '.', '2', '8', '.'}, {'.', '.', '.', '4', '1', '9', '.', '.', '5'}, {'.', '.', '.', '.', '8', '.', '.', '7', '9'}

    };

    cout << s.isValidSudoku(board);
}