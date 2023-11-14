/*
349. Intersection of Two Arrays
*/


//用unordered_set的解答 time: o(n) space: o(m)  
class Solution {
public:
    vector<int> intersection(vector<int>& nums1, vector<int>& nums2) {
        int n = nums1.size();
        int m = nums2.size();
        vector<int> ans;
        unordered_set<int> set(nums1.begin(), nums1.end()); //不會有重複項！

        for(auto x:nums2){
            if(set.find(x) != set.end()){ //也可以寫 set.count(a)
                ans.push_back(x);
                set.erase(x);
            }
        }

        return ans;
    }
};

//binary search  但會run time error== nums1 nums2角色對調免強過關... 24.39%
// time: o(nlgn + mlgm) nlgn是排序, space:o(m)
class Solution1 {
public:
    vector<int> intersection(vector<int>& nums1, vector<int>& nums2) {
        sort(nums1.begin(), nums1.end());
        sort(nums2.begin(), nums2.end());
        vector<int> ans;
        for(int i = 0; i < nums2.size(); i++){
        int left = 0; 
        int right = nums1.size();
        int mid = 0;
        while(left <= right){
            mid = (left+right)/2;
            if(nums1[mid] == nums2[i]){
                if(find(ans.begin(),ans.end(), nums2[i]) != ans.end() ) break; //這裡可以改成使用unordered_set 就不用確認是否重複惹
                ans.push_back(nums1[mid]);
                break;//這個break 可以直接跳出ｗｈｉｌｅ迴圈
            }
            if(nums1[mid] > nums2[i]){
                right = mid-1;
            }
            else left = mid + 1;
        }

        return ans;
    }
};
