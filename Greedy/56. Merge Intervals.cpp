/*
56. Merge Intervals
*/


//sweeping line/ sort by starting points TC:O(nlgn) SC:O(n)
class Solution {
    //sort begining points
    static bool cmp(pair<int, int>& a, pair<int, int>& b){
        if(a.first != b.first){
            return a.first < b.first;
        }

        else return a.second > b.second;//正數先做 才不會讓尾跟頭交疊的兩個區間被誤判為兩個不重疊區間
    }
public:
    vector<vector<int>> merge(vector<vector<int>>& intervals) {
        int n = intervals.size();
        vector<pair<int, int>> diff;
        for(auto interval:intervals){
            diff.push_back({interval[0], 1});
            diff.push_back({interval[1], -1});
        }

        sort(diff.begin(), diff.end(), cmp);

        //把一個重疊的區間變成無重疊 需判斷他的頭跟尾 
        //頭的時候sum  == 0 && sum+diff.first 會0
        //尾的時候 sum > 0 && sum+diff.first會等於0
        
        int sum = 0;
        vector<vector<int>> res;
        int start, end;
        for(int i = 0; i < diff.size(); i++){
            if(sum == 0 && sum+diff[i].second > 0){
                start = diff[i].first;
            }
            if(sum > 0 && sum + diff[i].second == 0){
                end = diff[i].first;
                res.push_back({start, end});
            }
            
            sum+=diff[i].second;
        }

        return res;
    }
};

//直接做 不多設一個diff數組 TC:O(nlgn) SC:O(n)
class Solution {
    static bool cmp(vector<int>& a, vector<int>& b){
        if(a[0] == b[0]){
            return a[1] > b[1];
        }
        else return a[0] < b[0];
    }
public:
    vector<vector<int>> merge(vector<vector<int>>& intervals) {
        //sort by starting points
        sort(intervals.begin(),intervals.end(),cmp);
        vector<vector<int>> res;
        int i = 0;
        while(i < intervals.size()){
            int far_temp = intervals[i][1];
            int start = intervals[i][0];
            while(i < intervals.size() && intervals[i][0] <= far_temp){
                far_temp =max(intervals[i][1],far_temp);
                i++;
            }
            res.push_back({start,far_temp});
        }

        return res;
    }
};

/*
題目要求要返回 沒有重疊的intervals 
那要如何判斷重疊的intervals並且把他merge起來 可以用greedy 裡面的sweeping line
建立一個vector 裡面裝的是pair 裡面的元素分別是 value 跟是頭or尾 如果是頭的話差分數組就會+1 是尾就是減一

*/
