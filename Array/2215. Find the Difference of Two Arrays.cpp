/*
2215. Find the Difference of Two Arrays
*/

/*
此題想找出兩個數組 對方互相沒有的元素 用兩個HashSet 互相查找 其中unordered_set 查找速度平均為O(1) 但最壞情況哈希碰撞的話會是O(n)
如果用 Set 紅黑樹底層結構 最壞跟平均都是O(lgn)
*/

//TC:O(m+n) SC:O(m+n) 
class Solution {
public:
    vector<vector<int>> findDifference(vector<int>& nums1, vector<int>& nums2) {
        unordered_set<int> set1;
        unordered_set<int> set2;
        for(auto num:nums1){
            set1.insert(num);
        }
        for(auto num:nums2){
            set2.insert(num);
        }
        vector<vector<int>> res(2);
        for(auto x:set1){
            if(set2.find(x) == set2.end()){
                res[0].push_back(x);
            }
        }
        for(auto x:set2){
            if(set1.find(x) == set1.end()){
                res[1].push_back(x);
            }
        }

        return res;
    }
};
