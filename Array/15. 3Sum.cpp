/*
15. 3Sum
*/

// 2025.02.20
class Solution {
public:
    vector<vector<int>> threeSum(vector<int>& nums) {
        int n = nums.size();
        ranges::sort(nums);
        vector<vector<int>> ans;
        for(int i = 0; i < n-2; i++) {
            if(i && nums[i] == nums[i-1]) continue;
            if(nums[i] + nums[i+1] + nums[i+2] > 0) break;
            int p1 = i+1, p2 = n-1;
            while(p1 < p2) {
                int sum = nums[i] + nums[p1] + nums[p2];
                if(sum > 0) {
                    p2 -= 1;
                }
                else if(sum < 0) {
                    p1 += 1;
                }
                else {
                    ans.push_back({nums[i], nums[p1], nums[p2]});
                    while(p1 < p2 && nums[p1] == nums[p1 + 1]) p1 += 1;
                    while(p2 > p1 && nums[p2] == nums[p2-1]) p2 -= 1;
                    p1 += 1, p2 -= 1;
                }
            }
        }
        return ans;
    }
};

//Brute force TC:O(n^3+nlgn) SC:O(1)
//也可以用set<vector<int>>   去重
class Solution {
public:
    vector<vector<int>> threeSum(vector<int>& nums) {
        int n = nums.size();
        vector<vector<int>> res;
        sort(nums.begin(), nums.end());
        for(int i = 0; i<n; i++){
            if(i > 0 && nums[i] == nums[i-1]) continue;
            for(int j = i+1; j<n; j++){
                if(j-1 != i && nums[j] == nums[j-1]) continue;
                for(int k = j+1; k<n; k++){
                    if(k-1 != j && nums[k] == nums[k-1]) continue;
                    if(nums[i]+nums[j]+nums[k] == 0){
                        res.push_back({nums[i],nums[j],nums[k]});
                    }
                }
            }
        }

        return res;

    }
};


//hash map TC:O(nlgn+n^2) SC:O(n)
class Solution {
public:
    vector<vector<int>> threeSum(vector<int>& nums) {
        int n = nums.size();
        vector<vector<int>> res; 
        sort(nums.begin(),nums.end());//方便去重
        unordered_map<int,int> map;
        //計算數組中每個不同的數字有多少數量
        for(int x:nums){
            map[x]++;
        }

        for(int i = 0; i<n; i++){
            if(i > 0 && nums[i] == nums[i-1]) continue;
            for(int j = i+1; j<n; j++){
                if(j-1 != i && nums[j] == nums[j-1]) continue;
                int cur = 0 - nums[i] - nums[j];
                // nums[i] <= nums[j] <=nums[k]
                if(cur < nums[j]) continue;//也是一個去重
                if(map.count(cur)){
                    if(map[cur] >= 1 + (nums[i] == cur) + (nums[j] == cur)){
                        res.push_back({nums[i],nums[j],cur});
                    }
                }
            }
        }

        return res;

    }
};


//two pointer TC:O(nlgn + n^2) SC:O(1)
class Solution {
public:
    vector<vector<int>> threeSum(vector<int>& nums) {
        int n = nums.size();
        vector<vector<int>> res; 
        sort(nums.begin(),nums.end());
        for(int i = 0; i<n; i++){
            if(i > 0 && nums[i] == nums[i-1]) continue;//去重
            int j = i+1, k = n-1;
            while(j < k){
                if(nums[i]+nums[j]+nums[k] > 0){
                    --k;
                }
                else if(nums[i]+nums[j]+nums[k] < 0){
                    ++j;
                }
                else if (nums[i]+nums[j]+nums[k] == 0){
                    res.push_back({nums[i],nums[j],nums[k]});
                    //去重
                    while(j < k && nums[j] == nums[j+1]) ++j;
                    while(j < k && nums[k] == nums[k-1]) --k;
                    ++j; --k; 
                }
            }
        }

        return res;

    }
};
