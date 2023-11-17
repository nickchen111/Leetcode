/*
962. Maximum Width Ramp
*/


// TC:O(n) SC:O(n)
class Solution {
public:
    int maxWidthRamp(vector<int>& nums) {
        int n = nums.size();
        stack<int> s;
        for(int i = 0; i<n; i++){
            if(s.empty() || nums[s.top()] > nums[i]){
                s.push(i);
            }
        }
        int res=0;
        for(int i =n-1; i>=0; i--){
            while(!s.empty() && nums[s.top()] <= nums[i]){
                res = max(res, i-s.top());
                s.pop();
            }
        }

        return res;
    }
};

// TC:O(nlgn) SC:O(n)
class Solution {
public:
    int maxWidthRamp(vector<int>& nums) {
        vector<int> q;
        vector<int> idx;
        int res = 0;
        for(int i = 0; i<nums.size(); i++){
            if(q.empty() || q.size() > 0 && q.back() > nums[i]){
                q.push_back(nums[i]);
                idx.push_back(i);
            }
            else{
                //因為是降序排序的所以需要反向查找 
                auto it = upper_bound(q.rbegin(),q.rend(), nums[i]);
                //得到逆序數過來的第幾個元素
                int k = it-q.rbegin();
                k = (q.size()-k+1)-1; // 要求倒數第二個元素這種 假設總共六個 6-2+1就是正著數第幾個 -1 求idx
                res = max(res,i-idx[k]);
            }
        }
        return res;
    }
};
