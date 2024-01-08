/*
2948. Make Lexicographically Smallest Array by Swapping Elements
*/

// TC:O(nlgn + n) SC:O(n)
class Solution {
public:
    vector<int> lexicographicallySmallestArray(vector<int>& nums, int limit) {
        int n = nums.size();
        vector<pair<int,int>> arr;
        for(int i = 0; i < n; i++){
            arr.push_back({nums[i],i});
        }

        sort(arr.begin(), arr.end());
        vector<vector<pair<int,int>>> helper = {{arr[0]}};
        for(int i = 1; i < n; i++){
            if(arr[i].first - arr[i-1].first <= limit){
                helper.back().push_back(arr[i]);
            }
            else helper.push_back({arr[i]});
        }

        for(const auto &t : helper){
            vector<int> idx;
            //將 有可能交換的index取出
            for(auto &p : t){
                idx.push_back(p.second);
            }
            sort(idx.begin(), idx.end());
            for(int i = 0; i < idx.size(); i++){
                nums[idx[i]] = t[i].first;
            }
        }
        
        return nums;
    }
};

/*
此題說要求字母序最小的排列方式 但是如果想將兩個數字換位置他們必須相減小於limit
[1,7,6,18,2,1] [1,6,7,18,1,2]
[1 1 2 6 7 18]
這題的解法是先將所有數字紀錄他的數值跟index 然後按照數值做由小到大的排序
之後再開始將可以換位置的數字湊成一組 最佳解的狀況是在答案數組內這些數字的順序要是對的
類似index sorting的思想
*/
