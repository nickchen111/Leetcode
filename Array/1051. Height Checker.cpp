/*
1051. Height Checker
*/

// TC:O(nlgn) SC:O(n)
class Solution {
public:
    int heightChecker(vector<int>& heights) {
        vector<int> arr = heights;
        sort(arr.begin(), arr.end());
        int count = 0;
        for(int i = 0; i < arr.size(); i++){
            if(arr[i] != heights[i]) count += 1;
        }

        return count;
        
    }
};
