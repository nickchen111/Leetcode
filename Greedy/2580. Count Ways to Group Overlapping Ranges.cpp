/*
2580. Count Ways to Group Overlapping Ranges
*/

// Diff  TC:O(n) SC:O(n)
class Solution {
public:
    int countWays(vector<vector<int>>& ranges) {
        // diff
        map<int,int> map;
        for(auto range : ranges){
            int a = range[0],  b = range[1];
            map[a] += 1;
            map[b] -= 1;
        }
        int count = 0;
        int sum = 0;
        for(auto p:map){
            sum += p.second;
            if(sum == 0) count++;
        }
        long long M = 1e9+7;
        long long res = 1;
        for(int i = 0; i < count; i++){
            res = res*2 % M;
        }

        return res;
        
    }
};

// Sort by Staring Point TC:O(nlgn) SC:O(1)
class Solution {
public:
    int countWays(vector<vector<int>>& ranges) {
        // sort by starting points
        sort(ranges.begin(), ranges.end());
        int count = 0;
        int i = 0;
        while(i < ranges.size()){
            int end = ranges[i][1];
            count++;
            int j = i + 1;
            while(j < ranges.size() && ranges[j][0] <= end){
                end = max(end, ranges[j][1]);
                j++;
            }
            i = j;
        }

        long long res = 1;
        long long  M = 1e9 + 7;
        for(int i = 0; i < count; i++){
            res = res * 2 % M;
        }

        return res;
        
    }
};
