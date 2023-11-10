/*
1764. Form Array by Concatenating Subarrays of Another Array
*/

// KMP TC:O((m+n)*k) SC:O((m+n)*k)
class Solution {
    int dp[1000];
public:
    bool canChoose(vector<vector<int>>& groups, vector<int>& nums) {
        //在大區間找小區間 且要找很多次 順序還不能變 是否可以達成
        vector<vector<int>> lsps = preprocessor(groups);
        int cur=0;
        for(int i = 0; i<groups.size(); i++){
            if(cur >= nums.size()) return false;
            cur = find(nums,groups[i],lsps[i],cur);
            if(cur == -1) return false;
            cur+=groups[i].size();
        }

        return true;

    }

    vector<vector<int>> preprocessor(vector<vector<int>>& groups){
        
        vector<vector<int>> res;
        for(auto &g:groups){
            int n = g.size();
            vector<int> dp(n,0);
            for(int i = 1; i<n; i++){
                int j = dp[i-1];
                while(j > 0 && g[i] != g[j]){
                    j = dp[j-1];
                }
                dp[i] = j + (g[i] == g[j]);
            }
            res.push_back(dp);
        }
        return res;
    }

    int find(vector<int>& nums, vector<int>& group, vector<int>& lsp, int cur){
        int n = nums.size();
        dp[cur] = (group[0] == nums[cur]);
        if(lsp.size() == 1 && dp[cur] == 1) return cur;
        
        for(int i = cur+1; i<n; i++){
            int j = dp[i-1];
            while(j > 0 && group[j] != nums[i]){
                j = lsp[j-1];
            }
            dp[i] = j + (group[j] == nums[i]);
            if(dp[i] == group.size()) return i-group.size()+1;
        }

        return -1;
    }
};

// Brute force: TC:O(m*n*k) SC:O(1)
class Solution {
public:
    bool canChoose(vector<vector<int>>& groups, vector<int>& nums) {
        // Brute force 
        int cur = 0;
        for(int i= 0; i<groups.size(); i++){
            cur = find(groups[i],nums,cur);
            if(cur >= nums.size()) return false;
            if(cur == -1) return false;
            cur+= groups[i].size();
        }

        return true;
    }

    int find(vector<int>& group, vector<int>& nums, int cur){
        int n =nums.size();
        for(int i=cur;i<n; i++){
            int flag = 1;
            for(int j = 0; j<group.size(); j++){
                if(cur+j >= n || nums[i+j] != group[j]){
                    flag = 0;
                    break;
                }
            }
            if(flag) return i;
        }

        return -1;
    }
};
