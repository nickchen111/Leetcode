/*
1346. Check If N and Its Double Exist
*/

// TC:O(n) SC:O(n)
class Solution {
public:
    bool checkIfExist(vector<int>& arr) {
        unordered_map<int,int> map;
        for(auto &x:arr) {
            if(x%2 == 0) {
                if(map[x/2] != 0) return true;
            }
            if(map[2*x] != 0) return true;
            map[x] += 1;
        }

        return false;
    }
};
