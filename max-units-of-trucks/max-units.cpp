#include <bits/stdc++.h>

using namespace std;

bool sortcol(const vector<int> &v1, const vector<int> &v2)
{
    return v1[1] > v2[1];
}

int maximumUnits(vector<vector<int>> &boxTypes, int truckSize)
{

    int sum = 0;
    sort(boxTypes.begin(), boxTypes.end(), sortcol);

    // for(int i=0 ; i < boxTypes.size() ; i++){

    //               if(truckSize != 1){
    //               if(truckSize - boxTypes[i][0] >= 0){
    //                 truckSize = truckSize - boxTypes[i][0];
    //                sum += ( boxTypes[i][1] * boxTypes[i][0] ) ;

    //               }else{
    //                   cout<<boxTypes[i][1]<<" "<<boxTypes[i][0];
    //                   sum += boxTypes[i][1] * (boxTypes[i][0] - truckSize);
    //                   truckSize = 0;
    //                     break;
    //               }

    //               }else{
    //                   truckSize = truckSize - 1;
    //                   sum = sum + boxTypes[i][1];
    //               }

    //             if(truckSize  == 0){
    //                     break;
    //             }
    //               }

    for (auto box : boxTypes)
    {
        int x = min(box[0], truckSize); // choose minimum boxes from available boxes and capacity left
        sum += (x * box[1]);            // adding units in ans
        truckSize -= x;                 // reduce the capacity
        if (!truckSize)
            break; // capacity full
    }

    return sum;
}

int main()
{
    vector<vector<int>> vec{{1, 3}, {2, 2}, {3, 1}};

    int truckSize = 4;

    maximumUnits(vec, 4);
}