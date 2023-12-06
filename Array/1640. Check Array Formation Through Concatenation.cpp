/*
1640. Check Array Formation Through Concatenation
*/

// TC: O(m*n) SC:O(n)
class Solution {
public:
    bool canFormArray(vector<int>& arr, vector<vector<int>>& pieces) {
        unordered_map<int,int> map; // val -> idx
        for(int i = 0; i < arr.size(); i++){
            map[arr[i]] = i;
        }
        
        int count = 0;
        for(int i = 0; i < pieces.size(); i++){
            for(int j = 0; j < pieces[i].size(); j++){
                if(map.find(pieces[i][j]) != map.end()){
                    if(j == 0) count++;
                    else if(j > 0 && map[pieces[i][j]]-1 == map[pieces[i][j-1]]) count++;
                    else {
                        return false;
                    }
                }
            }
         
        }

        if(count == map.size()) return true;
        else return false;
    }
};

// TC:O(n) SC:O(n)
class Solution {
public:
    bool canFormArray(vector<int>& arr, vector<vector<int>>& pieces) {
        set<vector<int>> set;
        for(auto p:pieces){
            set.insert(p);
        }

        vector<int> temp;//因為不會包含重複的數字 所以如果對上了那就要全對上    
        for(int i = 0; i < arr.size(); i++){
            temp.push_back(arr[i]);
            if(set.find(temp) != set.end()){
                temp.clear();
            }
        }
        return temp.size() == 0;
    }
};


