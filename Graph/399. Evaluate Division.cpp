/*
399. Evaluate Division
*/

// TC: O(E+ Q*E) E為建立的時候所需時間 看有幾個pair要建立 Q為他問你多少pair 如果每個都從頭到尾就要Q*E SC:O(E)
class Solution {
    unordered_map<string, vector<pair<string, double>> > map;
public:
    vector<double> calcEquation(vector<vector<string>>& equations, vector<double>& values, vector<vector<string>>& queries) {
        
        for(int i = 0; i < equations.size(); i++){
            string str1 = equations[i][0], str2 = equations[i][1];
            map[str1].push_back({str2,values[i]});
            map[str2].push_back({str1,1.0/values[i]});
        }

        vector<double> res;
        for(auto q : queries){
            string str1 = q[0], str2 = q[1];
            if(map.find(q[0]) == map.end() || map.find(q[1]) == map.end()){
                res.push_back(-1.0);
                continue;
            }
            unordered_set<string> visited;
            visited.insert(str1);
            res.push_back(DFS(str1,str2,visited));
            
        }

        return res;
    }
    double DFS(string& str1, string& str2, unordered_set<string>& visited){

        if(str1 == str2){
            return 1.0;
        }
        

        for(int i = 0; i < map[str1].size(); i++){
            string str3 = map[str1][i].first;
            if(visited.find(str3) != visited.end()) continue;
            visited.insert(str3);

            double val1 = map[str1][i].second;
            double val2 = DFS(str3, str2, visited);
            
            if(val2 != -1.0) return val1*val2;
        }

        return -1.0;
    }
};

/*
a = 2b
b = 3c 
a c -> ?
每個字都先去設定好 1a -> b c d / e -> x x x 等等的 根據題目給的關係就是a = 3b, 4c, 5d 之類
query某一點時就是從當下那點走到某點 並且由自己的參數1一直乘到找得到為止
*/
