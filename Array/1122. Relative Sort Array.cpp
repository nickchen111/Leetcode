/*
1122. Relative Sort Array
*/

// TC:O(nlgn) SC:O(n)
class Solution {
public:
    vector<int> relativeSortArray(vector<int>& arr1, vector<int>& arr2) {
        
        map<int,int> map;
       
        for(auto num : arr1){
            map[num] += 1;
        }
        vector<int> res;
        for(int i = 0; i < arr2.size(); i++){
            if(map.find(arr2[i]) != map.end()){
                for(int j = 0; j < map[arr2[i]]; j++){
                    res.push_back(arr2[i]);
                }
                map.erase(arr2[i]);
            }
        }

        for(auto p : map){
            for(int i = 0; i < p.second; i++){
                res.push_back(p.first);
            }
        }

        return res;
    }
};
