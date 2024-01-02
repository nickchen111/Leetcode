/*
2462. Total Cost to Hire K Workers
*/

// TC:O(k*lgk) SC:O(2*k)
class Solution {
    using LL = long long;
public: 
    long long totalCost(vector<int>& costs, int k, int candidates) {
        int n = costs.size();
        int i = 0;
        int j = n-1;
        priority_queue<LL, vector<LL>, greater<LL>> left;
        priority_queue<LL, vector<LL>, greater<LL>> right;

        int idx1 = -1;
        int idx2 = -1;
        for(int i = 0; i < candidates; i++){
            left.push(costs[i]);
            idx1 = i;
        }
        idx1 += 1; // 下一個能選取的對象

        // 設立第二個heap不能拿超過idx1 以防重複選取的狀況
        for(int i = n-1; i >= (n-candidates) && i >= idx1; i--){
            right.push(costs[i]);
            idx2 = i;
        }
        idx2 -= 1; // 下一個能選取的對象
        

        int step = 0;
        LL res = 0;
        while(step < k){
            int x,y;

            if(!left.empty()) x = left.top();
            else x = INT_MAX;

            if(!right.empty()) y = right.top();
            else y = INT_MAX;

            // 數字一樣index前面的先取
            if(x <= y){
                res += x;
                left.pop();
                
                //等於的狀況就是看誰先取到
                if(idx1 <= idx2){
                    left.push(costs[idx1]);
                    idx1++;
                }
            }
            else {
                res += y;
                right.pop();

                if(idx2 >= idx1){ 
                    right.push(costs[idx2]);
                    idx2--;
                }
            }
            step++;
        }

        return res;

    }
};

/*
每次從頭尾選 各candidates個工人 找 cost最低的
如果相同取 index小的 按照這個程序選k個
每次選完index會改變 最少需要花費多少cost
我的想法是兩邊都維護一個固定長度的PQ 並且比較大小 如果相等選左邊
*/
