/*
2053. Kth Distinct String in an Array
*/

// TC:O(n) SC:O(n)
class Solution {
public:
    string kthDistinct(vector<string>& arr, int k) {
        int n = arr.size();
        
        int count = 0;
        unordered_map<string, int> map;
        for(auto str : arr){
            map[str] += 1;
        }
        for(auto str : arr){
            if(map[str] == 1) count += 1;
            if(count == k) return str;
        }

        return "";
    }
};
