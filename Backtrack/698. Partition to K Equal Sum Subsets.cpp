/*
698. Partition to K Equal Sum Subsets
*/

//backtrack TC:O(2^n) SC:O(n)
class Solution {
    bool used[16];
    int k;
    int total;
public:
    bool canPartitionKSubsets(vector<int>& nums, int k) {
        total = accumulate(nums.begin(), nums.end(), 0);
        if(total %k != 0) return false;
        this->k = k;
        //DFS 
    
        return DFS(nums, 0, 0, 0);
    }

    bool DFS(vector<int>& nums, int count, int cur, int track){
       
        if(count == k){
            return true;
        }

        if(track == total/k){
            return DFS(nums, count+1, 0, 0);
        }

        if(track > total/k) return false;

        int n = nums.size();
        for(int i = cur; i<n; i++){
            if(used[i] == 1) continue;
            used[i] = 1;
            if(DFS(nums,count,i+1,track+nums[i])) return true;
            used[i] = 0;
        }

        return false;
    }
};


//優化剪枝 
class Solution {
    bool used[16];
    int k;
    int total;
public:
    bool canPartitionKSubsets(vector<int>& nums, int k) {
        sort(nums.begin(), nums.end());
        total = accumulate(nums.begin(), nums.end(), 0);
        if(total %k != 0) return false;
        this->k = k;
        //DFS 
    
        return DFS(nums, 0, 0, 0);
    }

    bool DFS(vector<int>& nums, int count, int cur, int track){
       
        if(count == k){
            return true;
        }

        if(track > total/k) return false;


        if(track == total/k){
            return DFS(nums, count+1, 0, 0);
        }

        int n = nums.size();
        for(int i = cur; i<n; i++){
            if(used[i] == 1) continue;
            if(i > cur && used[i-1] == 0 && nums[i] == nums[i-1]) continue;
            used[i] = 1;
            if(DFS(nums,count,i+1,track+nums[i])) return true;
            used[i] = 0;
        }

        return false;
    }
};


/*
"此題想將數組分成k個相同sum的subsets 沒辦法像之前背包問題416一樣解
只能藉由回溯算法 加上剪枝來儘量減少時間複雜度"
*/
