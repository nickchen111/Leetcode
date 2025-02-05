/*
1887. Reduction Operations to Make the Array Elements Equal
*/

// 2025.02.05 分組循環 TC:O(nlgn) SC:O(1)
class Solution {
public:
    int reductionOperations(vector<int>& nums) {
        ranges::sort(nums);
        int n = nums.size(), i = 0, k = 0, ans = 0;
        while(i < n) {
            int start = i;
            while(i + 1 < n && nums[i] == nums[i+1]) i += 1;
            ans += (i - start + 1) * k;
            k += 1;
            i += 1;
        }
        return ans;
    }
};

// TC:O(nlgn) SC:O(k)
class Solution {
public:
    int reductionOperations(vector<int>& nums) {
        map<int,int> map;
        for(auto num:nums){
            map[num]+=1;
        }
        vector<int> freq;
        for(auto x:map){
            freq.push_back(x.second);
        }
        int res = 0;
        int count=0;
        //最後一個不算
        for(int i = freq.size()-1; i>=1; i--){
            count+=freq[i];
            res+=count;
        }

        return res;
    }
};
/*
1 1 1 2 2 2 3 3 3
      s     e
1 1 1 2 2 2 2 3 3 3 4 4 4 5 5 5 
2->4 
3->3
4->3
*/
