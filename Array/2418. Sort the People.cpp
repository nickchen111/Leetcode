/*
2418. Sort the People
*/

// TC:O(nlgn) SC:O(n)
class Solution {
public:
    vector<string> sortPeople(vector<string>& names, vector<int>& heights) {
        
        vector<pair<int,string>> arr;
        for(int i  = 0; i < heights.size(); i++){
            arr.push_back({heights[i], names[i]});
        }

        sort(arr.rbegin(), arr.rend());
        for(int i = 0; i < arr.size(); i++){
            names[i] = arr[i].second;
        }

        return names;
    }
}; 
