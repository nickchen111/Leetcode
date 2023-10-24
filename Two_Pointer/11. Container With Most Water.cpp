/*
11. Container With Most Water
*/

// TC:O(n) SC:O(1)
class Solution {
public:
    int maxArea(vector<int>& height) {
        int n = height.size();
        int l = 0;
        int r = n-1;

        int res = 0;
        while(l < r){
            res = max(res,(r-l)*min(height[l],height[r]));

            if(height[l] < height[r]){
                l++;
            }
 
            else r--;
        }

        return res;
    }
};

/*
此題如果想得到最大的承接雨水的量
符合其中之一的條件都可能是最大的量
1.寬度最大
2.木板高度高->代表要捨棄當前最低的那塊木板 有點貪心的感覺
兩邊等高的狀況下 移動哪個都可以 因為後面的如果有兩個超級高 那麼移動哪都可以走到該超高的柱子
*/
