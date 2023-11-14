/*
454. 4Sum II
*/

// TC:O(n^2) SC:O(n)
class Solution {
public:
    int fourSumCount(vector<int>& nums1, vector<int>& nums2, vector<int>& nums3, vector<int>& nums4) {
        int res = 0;
    
        //此題不需考慮去重的狀況
        unordered_map<int,int> map1;
        unordered_map<int,int> map2;
    
        for(int i = 0; i<nums1.size(); i++){
            for(int j = 0; j<nums2.size(); j++){
                int sum = nums1[i]+nums2[j];
                map1[sum]+=1;
            }
        }

        for(int i = 0; i<nums3.size(); i++){
            for(int j = 0; j<nums4.size(); j++){
                int sum = nums3[i]+nums4[j];
                map2[sum]+=1;
            }
        }

        for(auto p:map1){
            int count = p.second;
            int target = p.first*(-1);
            if(map2.find(target) != map2.end()){
                res+=count*map2[target];
            }
        }

        return res;
    }
};
