/*
2933. High-Access Employees
*/

// TC:O(m*n^2) SC:O(mn) Hash table
class Solution {
public:
    vector<string> findHighAccessEmployees(vector<vector<string>>& access_times) {
        unordered_set<string> ret;
        vector<string> res;
        unordered_map<string,multiset<string>> map1;
        for(int i = 0; i<access_times.size(); i++){
            map1[access_times[i][0]].insert(access_times[i][1]);
        }
        unordered_map<string, vector<string>> map;
        for(auto p:map1){
            for(auto x:p.second)
                map[p.first].push_back(x);
        }
        // 0758 0848 0901
        
        for(auto p:map){
            for(int i = 0; i<p.second.size(); i++){
                int count = 1;
                int time1 = stoi(p.second[i]);
                for(int j = i+1; j<p.second.size(); j++){
                    int time2 = stoi(p.second[j]);
                    if(abs(time2-time1) < 100) count+=1;
                    else break;
                    if(count == 3){
                        ret.insert(p.first);
                        break;
                    }
                    
                }
            }
        }
        
        for(auto s:ret){
            res.push_back(s);
        }
        
        return res;
    }
};
