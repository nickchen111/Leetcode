/*
1658. Minimum Operations to Reduce X to Zero
*/


// Slide Window TC:O(n) SC:O(1)
class Solution {
    using LL = long long;
public:
    int minOperations(vector<int>& nums, int x) {
        int n = nums.size();
        vector<LL> presum(n+1);
        for(int i = 1; i <= n; i++){
            presum[i] = presum[i-1] + (LL)nums[i-1];
        }
        LL target = presum[n] - x;
        if(target < 0) return -1;
        //中間某段加總起來最大會到taget的數字
        int j = 0;
        LL sum = 0;
        int res = INT_MAX;
        for(int i = 0; i < n; i++){
            while(j < n && sum < target){
                sum += nums[j];
                j++;
            }
            if(sum == target) {
                res = min(res, n-(j-i));
            }
            sum -= nums[i];
        }

        return res == INT_MAX ? -1 : res; 
    }
};
//hash+presum TC:O(2*n) SC:O(n)
class Solution {
public:
    int minOperations(vector<int>& nums, int x) {
        //前後綴和
        int presum = 0;
        unordered_map<int,int> map; //val -> index;
        map[0] = -1;
        for(int i = 0; i<nums.size(); i++){
            presum+=nums[i];
            //只列越前面的越好
            if(map.find(presum) == map.end()){
                map[presum] = i;
            }
        }
        int res  = INT_MAX;
        //只有包含前綴的狀況 後綴可以不包括任何元素
        if(map.find(x) != map.end()){
            res = map[x]+1;
        }

        int suf = 0;
        int n = nums.size();
        //b則是越後面越好
        for(int b = n-1; b>=0; b--){
            suf+=nums[b];
            int pre = x-suf;
            if(map.find(pre) != map.end()){
                int a = map[pre];
                if(a < b){
                    res = min(res, a+1+(n-b));
                }
            }
        }

        return res == INT_MAX ? -1:res;
    }
};

/*
此題跟2516的思考邏輯相同
有點類似 左邊兩個邊界操作 看哪個加起來可以是x 如果沒辦法救回傳-1
跟2516從左邊右邊拿數字 看中間最長可以多長有點像  差別在一個算頻率一個算總和
[x x [i x x x] j x x x x x ]

如果用前綴後綴和的概念的話就會事先run一遍確定好前綴和及其位置 在run後綴 判斷一下目標減後綴之前是否有存在 有的話就更新答案 找最少的
*/
