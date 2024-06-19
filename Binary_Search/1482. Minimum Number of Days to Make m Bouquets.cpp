/*
1482. Minimum Number of Days to Make m Bouquets
*/

// TC:O(n*lg(maxVal)) SC:O(1)
class Solution {
public:
    int minDays(vector<int>& bloomDay, int m, int k) {
        int left = 1;
        int right = *max_element(bloomDay.begin(), bloomDay.end());
        
        while(left < right){
            int mid = left + (right - left)/2;
            if(check(mid, bloomDay, m, k)) {
                right = mid;
            }
            else left = mid + 1;
        }

        if(check(left, bloomDay, m, k) == false) return -1;
        else return left;
    }

    bool check(int mid, vector<int>& bloomDay, int m, int k){
        int total = 0;
        int count = 0;
        for(int i = 0; i < bloomDay.size(); i++){
            if(bloomDay[i] <= mid){
                count += 1;
                if(count == k){
                    total += 1;
                    count = 0;
                }
            }
            else {
                count = 0;
            }

            if(total >= m) return true;
        }

        return false;
    }
};


/*
要做出m個花束 最少需要幾天 每個花開花日期紀錄在數組
k代表 做一個花束需要多少個花並且需要是連續的
每k個區間 我需要知道最久要幾天
*/
