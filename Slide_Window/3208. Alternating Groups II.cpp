/*
3208. Alternating Groups II
*/

// TC:O(n) SC:O(1)
class Solution {
public:
    int numberOfAlternatingGroups(vector<int>& nums, int k) {
       
        for(int i = 0; i < k-1; i++){
            nums.push_back(nums[i]);
        }
        
        int n = nums.size();
        int res = 0;
        int i = 0;
        bool flag = 1;
        for(int j = 1; j < n; j++){
            if(i == j) continue;
            if(nums[j] == nums[j-1]){
                i = j;
                continue;
            }
            
            if(j-i+1 == k){
                res += 1;
                i++;
            }
        }
        
        return res;
        
    }
};

/*
每k個就判斷一下是否可以組成
頭尾相連再多給他k-1個 如何快速判斷某區是合法的 如果不合法直接從該點往前走
*/
