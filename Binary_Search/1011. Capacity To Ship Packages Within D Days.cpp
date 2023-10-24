/*
1011. Capacity To Ship Packages Within D Days
*/

// TC:O(n) SC:O(1)
class Solution {
public:
    int shipWithinDays(vector<int>& weights, int days) {
        int left = INT_MAX;
        int right = 0;
        for(int i = 0; i<weights.size(); i++){
            left = min(left, weights[i]);
            right+=weights[i];
        }

        while(left < right){
            int cap = left + (right - left)/2;
            if(checkOk(weights, days, cap)){
                right = cap;
            }
            else{
                left = cap+1;
            }
        }

        return left; //不會有無解的狀況 因此不需多做判斷
    }

    bool checkOk(vector<int>& weights, int days, int cap){
        int n = weights.size();
        int count = 0;
        for(int i = 0; i<n; i++){
            int sum = 0;
            int j = i;// i代表開始 ｊ為結束
            while(j < n && sum+weights[j] <= cap){
                sum+=weights[j];
                j++;
            }
            count++;
            if(count > days) return false;
            i = j-1;
        }

        return true;
    }
};
/*
此題可用DP 但會是n^3解
用二分較快 時間複雜度可以是 O(n+32) 還是屬於O(n)
*/
