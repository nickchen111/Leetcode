/*
3354. Make Array Elements Equal to Zero
*/

// TC:O(n) SC:O(1)
class Solution {
public:
    int countValidSelections(vector<int>& nums) {
        int n = nums.size();
        int suf = reduce(nums.begin(), nums.end(), 0);
        int pre = 0;
        int res = 0;
        for (int i = 0; i < n; i++) {
            if (nums[i] == 0) {
                if(pre == suf) res += 2;
                else if(abs(pre-suf) == 1) res += 1;
            }
            pre += nums[i];
            suf -= nums[i];
        }

        return res;
    }
};

// 模擬 TC:O(n^3) SC:O(1)
class Solution {
public:
    int countValidSelections(vector<int>& nums) {
        int n = nums.size();
        int validCount = 0;

        auto simulate = [&](int start, int direction) -> bool {
            vector<int> temp = nums; 
            int curr = start;
            
            while (curr >= 0 && curr < n) {
                if (temp[curr] == 0) {
                    curr += direction; 
                } else {
                    temp[curr]--;
                    direction = -direction; 
                    curr += direction;
                }
            }
            
           
            for (int x : temp) {
                if (x != 0) return false;
            }
            return true;
        };

        
        for (int i = 0; i < n; i++) {
            if (nums[i] == 0) {
               
                if (simulate(i, 1)) validCount++;  
                if (simulate(i, -1)) validCount++; 
            }
        }

        return validCount;
    }
};
