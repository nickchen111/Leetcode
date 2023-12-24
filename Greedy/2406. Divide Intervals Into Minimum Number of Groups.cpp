/*
2406. Divide Intervals Into Minimum Number of Groups
*/


// Sweeping line Vector TC:O(nlgn) SC:O(n)
class Solution {
public:
    int minGroups(vector<vector<int>>& intervals) {
        vector<pair<int,int>> diff; // time -> +1 -1
        for(auto &interval : intervals){
            diff.push_back({interval[0], +1});
            diff.push_back({interval[1], -1});
        }
        auto cmp = [](const pair<int,int>& a, const pair<int,int>& b){
            if(a.first != b.first){
                return a.first < b.first;
            }
            else return a.second > b.second; // +1先做
        };
        sort(diff.begin(), diff.end(), cmp);
        int sum = 0;
        int res = 0;
        for(int i = 0; i < diff.size(); i++){
            sum += diff[i].second;
            res = max(res, sum);
        }

        return res;
    }
};

// Sweeping line Map TC:O(nlgn) SC:O(n)
class Solution {
public:
    int minGroups(vector<vector<int>>& intervals) {
        //用map很明顯地對重疊狀況沒辦法處理 
        map<int,int> map;
        for(auto &interval : intervals){
            map[interval[0]] += 1;
            map[interval[1]+1] -= 1;
        }
        int res = 0;
        int sum = 0;
        for(auto p : map){
            sum += p.second;
            res = max(res, sum);
        }

        return res;
    }
};


/*
此題考區間 將一段一段區間如果不重疊可以合併成一個大區間 問說最少可以合併成幾個不重疊的區間
這樣就是說在某個時間段最多有多少個區間是重疊的 -> diff

*/
