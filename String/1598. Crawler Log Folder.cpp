/*
1598. Crawler Log Folder
*/

// TC:O(n) SC:O(2)
class Solution {
public:
    int minOperations(vector<string>& logs) {
        unordered_set<string> set;
        set.insert("../");
        set.insert("./");
        int count = 0;
        int n = logs.size();
        for(int i = 0; i < n; i++){
            if(set.find(logs[i]) == set.end()){
                count ++;
            }
            else {
                if(logs[i] == "../" && count > 0) count -= 1;
            }
        }

        return count;
    }
};
