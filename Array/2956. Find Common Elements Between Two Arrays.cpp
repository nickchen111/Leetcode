/*
2956. Find Common Elements Between Two Arrays
*/

// TC:O(n) SC:O(n)
class Solution {
public:
    vector<int> findIntersectionValues(vector<int>& nums1, vector<int>& nums2) {
        vector<int> res; // 回傳 nums2中跟nums1 一樣的數字數量以及 nums1中跟nums1一樣的數量
        multiset<int> set1; 
        multiset<int> set2;
        int count1 = 0; int count2 = 0;
        
        for(auto num:nums2){
            set2.insert(num);
        } 
        
        for(auto num : nums1){
            if(set2.find(num) != set2.end()) count2++;
            set1.insert(num);
        }
        
        for(auto p:set2){
            if(set1.find(p) != set1.end()){
                count1++;
            }
        }
      
        res.push_back(count2);
        res.push_back(count1);
        
        return res;
    }
};
