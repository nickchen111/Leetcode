/*
3132. Find the Integer Added to Array II
*/

// TC:O(nlgn) SC:O(n)
class Solution {
public:
    int minimumAddedInteger(vector<int>& nums1, vector<int>& nums2) {
        sort(nums1.begin(),nums1.end());
        sort(nums2.begin(),nums2.end());
        vector<int> arr2;
        for(int i = 0; i < nums2.size(); i++){
            arr2.push_back(nums2[i] - nums2[0]);
        }
        
        int res = INT_MAX/2;
        vector<int> arr1;
        for(int i = 0; i < nums1.size(); i++){
            arr1.push_back(nums1[i] - nums1[0]);
        }
        
        if(check(arr1,arr2)) res = min(res, nums2[0]-nums1[0]);
        arr1.clear();
        
        for(int i = 1; i < nums1.size(); i++){
            arr1.push_back(nums1[i] - nums1[1]);
        }
        
        if(check(arr1,arr2)) res = min(res, nums2[0]-nums1[1]);
        arr1.clear();
        
        for(int i = 2; i < nums1.size(); i++){
            arr1.push_back(nums1[i] - nums1[2]);
        }
        
        if(check(arr1,arr2)) res = min(res, nums2[0]-nums1[2]);
        
        return res;
    }
    bool check(vector<int>& arr1, vector<int>& arr2){
        int i = 0;
        for(int j = 0; j < arr2.size(); j++){
            while(i < arr1.size() && arr1[i] != arr2[j]) i++;
            if(i == arr1.size()) return false;
            i++;
        }
        
        return true;
    }
};
