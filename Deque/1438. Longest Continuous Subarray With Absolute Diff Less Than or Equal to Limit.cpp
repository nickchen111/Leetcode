/*
1438. Longest Continuous Subarray With Absolute Diff Less Than or Equal to Limit
*/


// Multiset TC:O(nlgn) SC:O(n)
class Solution {
public:
    int longestSubarray(vector<int>& nums, int limit) {
        int res = 1;
        multiset<int> set({nums[0]});
        int n = nums.size();
        int j = 0;
        for(int i = 0; i<n; i++){
            while(j<n && *set.rbegin()-*set.begin() <= limit){
                res = max(res, j-i+1);
                j++;
                if(j==n) break;
                set.insert(nums[j]);
            }
            if(j==n) break;
            set.erase(set.find(nums[i]));
        }

        return res;
    }
};

// Deque  TC:O(n) SC:O(n)
class Solution {
public:
    int longestSubarray(vector<int>& nums, int limit) {
        //在一個window中的最大最小值不可以超過limit
        //分別做最大最小值的deque
        int res = 1;
        int n = nums.size();
        deque<int> qmax({0});
        deque<int> qmin({0});
        int mx =nums[0]; int mn = nums[0];
        int j = 0;
        for(int i = 0; i<n; i++){
            while(mx-mn <= limit){
                res = max(res, j-i+1);
                j++;
                if(j == n) break;

                while(!qmax.empty() && nums[qmax.back()] <= nums[j]){
                    qmax.pop_back();
                }
                qmax.push_back(j);
                mx = nums[qmax.front()];

                while(!qmin.empty() && nums[qmin.back()] >= nums[j]){
                    qmin.pop_back();
                }
                qmin.push_back(j);
                mn = nums[qmin.front()];
            }
            
            //跳出limit範圍的可能是 雙指針j走到盡頭 或是最大減調最小值超過上限
            if(j == n) break;
            if(!qmax.empty() && qmax.front() == i){
                qmax.pop_front();
                mx = nums[qmax.front()];
            }
            if(!qmin.empty() && qmin.front() == i) {
                qmin.pop_front();
                mn = nums[qmin.front()];
            }
        }

        return res;
    }
};
