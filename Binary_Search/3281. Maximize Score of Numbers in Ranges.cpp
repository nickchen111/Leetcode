/*
3281. Maximize Score of Numbers in Ranges
*/

// TC:O(32*n) SC:O(1)
class Solution {
    vector<int> start;
    int d;
public:
    int maxPossibleScore(vector<int>& start, int d) {
        int n = start.size();
        sort(start.begin(), start.end());
        this -> d = d;
        this -> start = start;
        if(n == 2) return start[1]+d - start[0];
        
        int left = 0, right = INT_MAX/2;
        while(left < right){
            int mid = left + (right-left+1)/2;
            if(check(mid)) left = mid;
            else right = mid - 1;
        }
        
        return left;
    }
    bool check(int mid){
        int minVal = start[0];
        int maxVal = start.back() + d;
        if(maxVal - minVal < mid) return false;
        int n = start.size();
        int prev = minVal;
        for(int i = 1; i < n; i++){
            int curStart = start[i], curEnd = start[i] + d;
            if(prev + mid > curEnd) return false;
            if(prev + mid < curStart) prev = curStart;
            else prev = prev + mid;
        }
        
        return true;
    }
};
