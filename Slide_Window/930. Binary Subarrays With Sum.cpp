/*
930. Binary Subarrays With Sum
*/

// Hash + Presum TC:O(n) SC:O(n)
class Solution {
public:
    int numSubarraysWithSum(vector<int>& nums, int goal) {
        unordered_map<int,int> map; // prefix -> count of index 
        map[0] = 1;
        int presum = 0;
        int res = 0;
        for(int i = 0; i<nums.size(); i++){
            presum+=nums[i];
            if(map.find(presum-goal) != map.end()){
                res+=map[presum-goal];
                map[presum]+=1;
            }
            else map[presum]+=1;
        }

        return res;
    }
};


// Slide Window  TC:O(n) SC:O(n)
class Solution {
public:
    int numSubarraysWithSum(vector<int>& nums, int goal) {
        // 預處理
        int n = nums.size();
        vector<int> postZero(n);
        int count = 0;
        for(int i = n-1; i>=0; i--){
            postZero[i] = count;
            if(nums[i] == 0) count++;
            else count = 0;
        }

        int j = 0;//滑動點
        int sum = 0;
        int res= 0;
        for(int i =0; i<n; i++){
            //只有到i追上j or sum太小
            while(j == i || (j < n && sum < goal)){
                sum+=nums[j];
                j++;
            }
            if(sum == goal){
                res+=postZero[j-1]+1; //自己不是零也達到目標也要加進去
            }
            sum-=nums[i];
        }

        return res;
    }
};

/*
1 0 1 0 1
1 1 2 2 3
-1 -1 0 0 1  -goal    
*/
