/*
1452. People Whose List of Favorite Companies Is Not a Subset of Another List
*/

// TC:O(n^2*m) SC:O(n*m)
class Solution {
public:
    vector<int> peopleIndexes(vector<vector<string>>& arr) {
        map<int, unordered_set<string>> map;
        for(int i = 0; i < arr.size(); i++){
            map[i].insert(arr[i].begin(), arr[i].end());   
        }

        vector<int> res;
        for(int i = 0; i < arr.size(); i++){
            bool flag = 1;
            for(int j = 0; j < arr.size(); j++){
               if(i == j) continue;
               int count = 0;
               for(string str: map[i]){
                   if(map[j].find(str) != map[j].end()){
                       count++;
                   }
                   else break;
               }
               if(count == map[i].size()){
                    flag = false;
                    break;
               }
            }
            
            if(flag) res.push_back(i);
        }

        return res;
    }
};
