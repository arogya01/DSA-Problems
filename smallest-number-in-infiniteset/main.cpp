#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class SmallestInfiniteSet
{
public:
    vector<int> els;
    int currSmallest;
    SmallestInfiniteSet() : els(1000, 1), currSmallest{1}
    {
    }

    int popSmallest()
    {
        searchSmallest();
        setSmallest();
        return currSmallest;
    }

    void addBack(int num)
    {
        if (els[num - 1] == 0)
        {
            els[num - 1] = 1;
            searchSmallest();
        }
    }

    void setSmallest()
    {
        for (int i = 0; i < els.size(); i++)
        {
            if (els[i] == 1)
            {
                els[i] = 0;
                break;
            }
        }
    }

    void searchSmallest()
    {
        for (int i = 0; i < els.size(); i++)
        {
            if (els[i] == 1)
            {
                currSmallest = i + 1;
                break;
            }
        }
    }
};

/**
 * Your SmallestInfiniteSet object will be instantiated and called as such:
 * SmallestInfiniteSet* obj = new SmallestInfiniteSet();
 * int param_1 = obj->popSmallest();
 * obj->addBack(num);
 */

int main()
{
    SmallestInfiniteSet s;
    s.addBack(2);
    cout << s.popSmallest();
    cout << s.popSmallest();
    s.addBack(1);
    cout << s.popSmallest();
    cout << s.popSmallest();
    cout << s.popSmallest();
}