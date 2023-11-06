/*
169. Majority Element
*/

// Hash map TC:O(n) SC:O(n)
class Solution {
public:
    int majorityElement(vector<int>& nums) {
        unordered_map<int,int> map;
        int n = nums.size();
        for(int i = 0; i<n; i++){
            map[nums[i]]+=1;
            if(map[nums[i]] > n/2) return nums[i];
        }

        return -1;
    }
};

// randomization TC:O(2*n) SC:O(1)
class Solution {
public:
    int majorityElement(vector<int>& nums) {
        srand(time(NULL));
        int n = nums.size();
        while(true){
            int idx = rand()%n;
            int maj = nums[idx];
            int count = 0;
            for(int i = 0; i<n; i++){
                if(nums[i] == maj && ++count > n/2) return maj;
            }
        }

        return -1;
    }
};


// Divide and Conquer 優化 不全部搜索  TC:O(n)~O(nlgn) SC:O(lgn)
class Solution {
public:
    int majorityElement(vector<int>& nums) {
        return majorityElement(nums, 0, nums.size() - 1).first;
    }
private:
    pair<int, int> majorityElement(const vector<int>& nums, int l, int r) {
        if (l == r) return {nums[l], 1};
        int mid = l + (r - l) / 2;
        auto ml = majorityElement(nums, l, mid);
        auto mr = majorityElement(nums, mid + 1, r);
        if (ml.first == mr.first) return { ml.first, ml.second + mr.second };
        if (ml.second > mr.second)
            return { ml.first, ml.second + count(nums.begin() + mid + 1, nums.begin() + r + 1, ml.first) };
        else
            return { mr.first, mr.second + count(nums.begin() + l, nums.begin() + mid + 1, mr.first) };
    }
};
