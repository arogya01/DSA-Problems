#include <bits/stdc++.h>
using namespace std;

class SnapshotArray
{
    int id = 0;
    vector<map<int, int>> id_v;

public:
    SnapshotArray(int length)
    {
        id_v.assign(length, {{0, 0}});
    }

    void set(int index, int val)
    {
        id_v[index][id] = val;
    }

    int snap()
    {
        return id++;
    }

    int get(int index, int snap_id)
    {
        if (id_v[index].count(snap_id) == 0)
        {
            cout << "whatthefk";
            auto it = prev(id_v[index].lower_bound(snap_id));
            return it->second;
        }
        return id_v[index][snap_id];
    }
};

/**
 * Your SnapshotArray object will be instantiated and called as such:
 * SnapshotArray* obj = new SnapshotArray(length);
 * obj->set(index,val);
 * int param_2 = obj->snap();
 * int param_3 = obj->get(index,snap_id);
 */

int main()
{
    vector<vector<int>> arr2d;
    vector<int> arr1d{1, 2, 3, 4, 5};
    arr2d.push_back(arr1d);
    SnapshotArray *obj = new SnapshotArray(3);
    obj->set(0, 5);
    int param_2 = obj->snap();
    obj->set(0, 6);
    int param_3 = obj->get(0, 0);
    int newParam = obj->get(1, 1);
    cout << "param_3 is: " << newParam << endl;
    obj->set(1, 7);
    obj->set(2, 8);
    cout << param_2;
}