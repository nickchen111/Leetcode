/*
3152. Special Array II
*/

// TC:O(n+m) SC:O(n)
class Solution {
public:
    vector<bool> isArraySpecial(vector<int>& nums, vector<vector<int>>& queries) {
        int n = nums.size();
        vector<int> arr(n,1);
        for(int i = 0; i < n-1; i++){
            if(nums[i]%2 == nums[i+1]%2) arr[i] = 0;
        }
        
        vector<int> presum(n+1);
        for(int i = 1; i <= n; i++){
            presum[i] = presum[i-1] + arr[i-1];
        }
        
        int m = queries.size();
        vector<bool> res(m);
        for(int i = 0; i < m; i++){
            int from = queries[i][0], to = queries[i][1];
           
            int target = to - from;
            int sum = presum[to] - presum[from];
            if(sum == target) res[i] = true;
        }
        
        return res;
        
    }
};

/*
換成確認一段區間是否合法
創建一個數組都先設為1代表是合法數字
將每一個元素都去跟他後一個做比較 如果他會讓後一個無法組成parity 前一個數字就設為0
然後去對更新後的數組做presum 之後query就可以在O(1)時間求出每個區間合法性 也可以用差分or 二分解這題
需要注意的是每次區間涵蓋的都不用涵蓋最後一個元素 因為他是否合法取決於他後面的數字而不是當下區間
*/
