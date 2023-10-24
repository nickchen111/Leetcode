/*
1288. Remove Covered Intervals
*/

//sort by starting point TC:O(n+nlgn) SC:O(1)
class Solution {
    static bool cmp(vector<int>& a, vector<int>& b){
        if(a[0] != b[0]){
            return a[0] < b[0];
        }
        else return a[1] > b[1];
    }
public:
    int removeCoveredIntervals(vector<vector<int>>& intervals) {
        //此題想將所有完全被重疊的區間消掉 返回沒有完全重疊的區間 
        sort(intervals.begin(), intervals.end(), cmp);//按照starting points排序

        int count = 0;
        int i = 0;
        while(i < intervals.size()){
            count++;
            int j = i+1;
            while(j < intervals.size() && intervals[j][1] <= intervals[i][1])
                j++;
            i = j;
        }

        return count;

    }
};
