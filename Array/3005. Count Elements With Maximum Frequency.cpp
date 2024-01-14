/*
3005. Count Elements With Maximum Frequency
*/

// TC:O(n) SC:O(n)
class Solution {
public:
    int maxFrequencyElements(vector<int>& nums) {
        int n = nums.size();
        unordered_map<int,int> map;
        unordered_set<int> set;
        int maxVal = 1;
        for(int i = 0; i < n; i++){
            map[nums[i]] += 1;
            if(map[nums[i]] > maxVal){
                maxVal = map[nums[i]];
                set.clear();
                set.insert(nums[i]);
            }
            else if(map[nums[i]] == maxVal){
                set.insert(nums[i]);
            }
        }
        
        int res = set.size()*maxVal;
        
        return res;
        
    }
};

/*
這題就是要問你出現頻率最高次數的數字他們的頻率加總是多少
*/
