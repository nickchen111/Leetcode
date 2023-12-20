/*
2233. Maximum Product After K Increments
*/

// Presum + Diff + Binary Search TC:O(n + nlgn + lgn) SC:O(n) 
class Solution {
    using LL = long long;
    LL M = 1e9 + 7;
public:
    int maximumProduct(vector<int>& nums, int k) {
       
        int n = nums.size();
        sort(nums.begin(), nums.end());
        vector<LL> presum(n);
        vector<LL> diff(n);
        for(int i = 0; i < n; i++){
            presum[i] = ( i == 0 ? 0: presum[i-1]) + (LL)nums[i];
        }
        for(int i = 0; i < n; i++){
            diff[i] = (LL)(i+1)*nums[i] - presum[i];
        }

        auto iter = upper_bound(diff.begin(), diff.end(), k);
        int p = prev(iter) - diff.begin();//從這個idx之後就沒辦法繼續加後面數字了
        LL total = presum[p] + k;
        LL each = total/(p+1);
        LL extra = total % (p+1);
        LL res = 1;
        for(int i = 0; i < extra; i++){
            res = res * (each+1) % M;
        }
        
        for(int i = 0; i < p+1-extra; i++){
            res = res * (each) % M;
        }

        for(int i = p+1; i < n; i++){
            res = res * (nums[i]) % M;
        }

        return res % M;
    }
};



// PQ TC:O(nlgn + k) SC:O(n)
class Solution {
    using LL = long long;
    LL M = 1e9 + 7;
public:
    int maximumProduct(vector<int>& nums, int k) {
       
        int n = nums.size();
        priority_queue<int, vector<int>, greater<int>> pq;
        for(int i = 0; i < n; i++){
            pq.push(nums[i]);
        }

        while(k){
            int cur = pq.top();
            pq.pop();
            cur += 1;
            k -= 1;
            pq.push(cur);
        }

        LL res = 1;
        while(!pq.empty()){
            res = res * pq.top() %M;
            pq.pop();
        }

        return res % M;
    }
};

/*
此題想讓 數組內的數字乘法越大越好 有限定加法扣打k 按照乘法定理 需讓最小與最大值越近越好
初步想法是先將 最小的勁量跟最大的靠在一起 如果靠完有剩繼續讓第二小的變大 但這樣會需要考慮數字重複問題  分配上會需要考慮太多細節
並且也不曉得最小數字最多能加到多大 他在加法的過程會超過一些數字 不知該是否繼續加入
比較無腦的直接放入PQ每次都對最小值加一
另外一個方法更好一些 利用diff數組去計算說 如果前面的數字想加到跟我一樣大會需要加多少 找到最後一個diff[p] <= k到那項
他前面的項目數字就會是 (presum[i] + k)/p 有些可能加一 看他的餘數
這個知識點的話就會需要用到presum diff
*/
