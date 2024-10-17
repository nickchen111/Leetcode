/*
456. 132 Pattern
*/

// Stack:  TC:O(n) SC:O(n)
class Solution {
public:
    bool find132pattern(vector<int>& nums) {
        stack<int> stac;
        int n = nums.size();
        int s3 = INT_MIN;

        for(int i=n-1;i>=0;i--){
            
            if(nums[i] < s3) return true;
            else {
                while(!stac.empty() && stac.top() < nums[i]) 
                {
                    s3 = stac.top();
                    stac.pop();
                }
            }
            stac.push(nums[i]);
        }
        
        return false;
        
    }
};


// 二分 TC:O(nlgn) SC:O(n)
class Solution {
public:
    bool find132pattern(vector<int>& nums) {
        int n = nums.size();
        if(n < 3) return false;

        map<int,int> map;
        for(int i = 1; i < n; i++) {
            map[nums[i]] += 1;
        }

        int minVal = nums[0];
        for(int i = 1; i < n; i++) {
            if(nums[i] > minVal) {
                auto iter = map.upper_bound(minVal);
                if(iter->first < nums[i]) return true;
            }
            minVal = min(minVal, nums[i]);
            map[nums[i]] -= 1;
            if(map[nums[i]] == 0) map.erase(nums[i]);
        }

        return false;
        
    }
};


/*
i j k
vi vk vj
找一比vi大 但比vj小
*/
