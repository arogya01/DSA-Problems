#include <iostream>
#include <string>
using namespace std;

class Solution
{
public:
    std::string largestGoodInteger(std::string num)
    {
        int similarNumCount = 0;
        int threeDigitBro = -1;
        for (int i = 0; i < num.size() - 1; i++)
        { // Change the loop condition to avoid accessing out-of-bounds elements
            if (similarNumCount == 2)
            {
                int currentNum = num[i] - '0'; // Convert the char to int using subtraction
                if (currentNum > threeDigitBro)
                {
                    threeDigitBro = currentNum;
                }
                similarNumCount = 0;
            }

            if (num[i] == num[i + 1])
            {
                similarNumCount++;
            }
            else
            {
                similarNumCount = 0;
            }
        }

        if (threeDigitBro == -1)
            return "";

        std::string result = std::to_string(threeDigitBro);
        return result + result + result;
    }
};

int main()
{
    std::string sample;
    sample = "222";
    cout << "what's next bro" << endl;
    Solution s;
    cout << s.largestGoodInteger(sample);
}