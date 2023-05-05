#include <iostream>
#include <vector>
#include <unordered_map>
#include <utility>
using namespace std;

class TimeMap
{
public:
    vector<int> timestamps;
    unordered_map<int, pair<string, string>> mp;

    TimeMap()
    {
    }

    int searchTimestamp(int timestamp)
    {
        int lo = 0;
        int hi = timestamps.size() - 1;
        while (lo <= hi)
        {
            int mid = lo + (hi - lo) / 2;
            if (timestamps[mid] == timestamp)
            {
                return timestamp;
            }

            if (timestamps[mid] < timestamp)
            {
                lo = mid + 1;
            }
            else
            {
                hi = mid - 1;
            }
        }

        return timestamps[lo - 1];
    }

    void set(string key, string value, int timestamp)
    {
        timestamps.push_back(timestamp);
        mp[timestamp] = {key, value};

        cout << key << value << timestamp << endl;
    }

    string get(string key, int timestamp)
    {
        if (timestamps.size() == 0)
            return "";
        else if (timestamp < timestamps[0])
        {
            return "";
        }

        int stamp = searchTimestamp(timestamp);
        return mp[stamp].second;
    }
};

/**
 * Your TimeMap object will be instantiated and called as such:
 * TimeMap* obj = new TimeMap();
 * obj->set(key,value,timestamp);
 * string param_2 = obj->get(key,timestamp);
 */

int main()
{
    TimeMap *obj = new TimeMap();
    obj->set("love", "high", 10);
    obj->set("love", "low", 20);
    string test1 = obj->get("love", 5);
    string test2 = obj->get("love", 10);
    string test3 = obj->get("love", 15);
    string test4 = obj->get("love", 20);
    string test5 = obj->get("love", 25);
}