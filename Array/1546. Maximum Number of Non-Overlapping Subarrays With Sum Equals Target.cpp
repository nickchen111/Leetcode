/*
1546. Maximum Number of Non-Overlapping Subarrays With Sum Equals Target
*/

// TC:O(n) SC:O(n)
class Solution {
public:
    int maxNonOverlapping(vector<int>& nums, int target) {
        int n = nums.size();
        int res = 0;
        //[0, -1,-2,8,-3,8,-5,5,-4,5,4,1] target = 5
        vector<int> presum(n);
        for(int i = 0; i < n; i++){
            presum[i] = (i-1 < 0 ? 0 : presum[i-1]) + nums[i];
        }

        unordered_map<int, int> map; // 可能有很多的presum都有一樣的結果 那麼只要紀錄最多的那項
        map[0] = -1;
        vector<int> pos(n,0);
        for(int i = 0; i < n; i++){
            pos[i] = (i-1 < 0 ? 0 : pos[i-1]);
            int cur = presum[i];
            // 當目前sum = target && 找到前面也有符合的條件
            if(map.find(cur-target) != map.end()){
                int lastPos = map[cur-target];

                pos[i] = max(pos[i], (lastPos == -1 ?  0 : pos[lastPos]) + 1);
            }
            res = max(res, pos[i]);
            map[cur] = i;
        }

        

        return res;
    }

};

/*
這題跟 1477 有點像都是要求non-overlapping interval並且每個區間總和要是target
但這題問的是最多的這種non-overlapping區間可以有多少個
我的想法是同樣用presum記錄總和 然後搭配hash table 快速定位到符合target的位置
看那個位置之前最長有多少個區間符合條件動態更新res
*/
