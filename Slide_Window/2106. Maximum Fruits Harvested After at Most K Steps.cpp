/*
2106. Maximum Fruits Harvested After at Most K Steps
*/

// TC:O(n) SC:O(n)
class Solution {
public:
    int maxTotalFruits(vector<vector<int>>& fruits, int startPos, int k) {
        int n = fruits.size();
        vector<int> pos(n);
        vector<int> presum(n);
        int res = 0;
        for(int i = 0; i<n; i++){
            pos[i] = fruits[i][0];
            presum[i] = (i == 0 ? 0:presum[i-1])+fruits[i][1];
        }

        //先找到以目前位置來說下一個水果點
        int mid = lower_bound(pos.begin(),pos.end(),startPos) - pos.begin();
        int j = 0;
        for(int i = mid; i<n; i++){
            while(pos[j] <= startPos &&  pos[i]-startPos+2*(startPos-pos[j]) > k){
                j++;
            }
            if(pos[j] <= startPos){
                res = max(res,presum[i]-(j == 0 ? 0:presum[j-1]));
            }
            //當他左邊沒有可以接觸到的水果而跑到我當前位置的大於或等於的有水果位置上
            else if(pos[i]-startPos <= k){
                res = max(res,presum[i]-(j == 0 ? 0:presum[j-1]));
            }
        }
        //比我所在位置還要小於or等於的水果位置
        mid = upper_bound(pos.begin(),pos.end(),startPos)-pos.begin()-1;
        j = n-1;
        for(int i = mid; i>=0; i--){
            while(pos[j]>=startPos && startPos-pos[i]+2*(pos[j]-startPos) > k){
                j--;
            }
            if(pos[j] >= startPos){
                res = max(res, presum[j]-(i== 0 ? 0:presum[i-1]));
            }
           else if(startPos-pos[i] <= k){
                res = max(res, presum[j]-(i== 0 ? 0:presum[i-1]));
            }
        }

        return res;
    }
};


/*
[o o o x o o pos y]
2x+y <= k
[o o o y o o pos x]
2x+y <= k
*/
