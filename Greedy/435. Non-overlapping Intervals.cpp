/*
435. Non-overlapping Intervals
*/


//greedy: sort by ending points  TC:O(n) SC:O(1)
class Solution {
    static bool comp(vector<int>& a, vector<int>& b){
        return a[1] < b[1];
    }
public:
    int eraseOverlapIntervals(vector<vector<int>>& intervals) {
        sort(intervals.begin(), intervals.end(), comp);

        int i = 0;
        int count = 0; //計算最多有幾個區間沒重疊
        while(i < intervals.size()){
            int j = i+1;
            count++;
            while(j < intervals.size() && intervals[j][0] < intervals[i][1]){
                j++;
            }
            i = j;
        }

        return intervals.size()-count;
    }
};

/*
此題為經典的貪心算法 求無重疊的區間最多有幾個 
題目問要刪除幾個區間 那就將總共區間數-最多可以有幾個無重疊區間
*/
