/*
1331. Rank Transform of an Array
*/

// TC:O(nlgn) SC:O(n)
class Solution {
public:
    vector<int> arrayRankTransform(vector<int>& arr) {
        int n = arr.size();
        map<int, vector<int>> map;
        
        for(int i = 0; i < n; i++){
            map[arr[i]].push_back(i);
            
        }

       
        vector<int>res(n);
        int count = 1;
        for(auto &p : map){
            for(int i = 0; i < p.second.size(); i++){
                res[p.second[i]] = count;
            }
            count += 1;
        }

        return res;
    }
};
