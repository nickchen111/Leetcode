/*
2115. Find All Possible Recipes from Given Supplies
*/

// Topolgical Sort TC:O(n^2) SC:O(n^2)
class Solution {
public:
    vector<string> findAllRecipes(vector<string>& recipes, vector<vector<string>>& ingredients, vector<string>& supplies) {
        int n = recipes.size();
        unordered_map<string, vector<string>> next;
        unordered_map<string, int> indegree;
        for(int i = 0; i < n; i++){
            for(int j = 0; j < ingredients[i].size(); j++){
                next[ingredients[i][j]].push_back(recipes[i]);
                indegree[recipes[i]] += 1;
            }
        }

        unordered_set<string> wanted(recipes.begin(), recipes.end());
        queue<string> q;
        for(auto s : supplies){
            q.push(s);
        }

        vector<string> res;
        while(!q.empty()){
            string cur = q.front();
            q.pop();
            if(wanted.find(cur) != wanted.end()) res.push_back(cur);
            for(const auto& x : next[cur]){
                indegree[x] -= 1;
                if(indegree[x] == 0) q.push(x);
            }
        }

        return res;

    }
};


//Brute force with Hash set  TC:O(10^6 -> n^2*n^2) SC:O(n)
class Solution {
public:
    vector<string> findAllRecipes(vector<string>& recipes, vector<vector<string>>& ingredients, vector<string>& supplies) {
        int n = recipes.size();
        vector<string> res;
        vector<bool> visited(n,0);
        unordered_set<string> supply(supplies.begin(), supplies.end());
        while(1){
            bool flag2 = 0;
            for(int i = 0; i < n; i++){
                if(visited[i] == 0){
                    bool flag = 1;
                    for(int j = 0; j < ingredients[i].size(); j++){
                        if(supply.find(ingredients[i][j]) == supply.end()){
                            flag = 0;
                            break;
                        }
                    }
                    if(flag){
                        visited[i] = 1;
                        flag2 = 1;
                        supply.insert(recipes[i]);
                        res.push_back(recipes[i]);
                    }
                }
            }
            if(flag2 == 0) break;
        }

        return res;
    }
};

/*
此題讓我們有些原物料 並且給我們某些食物組成成分 問說可以自己組成多少食物 note某食物可能是另一個食物的組成成分
大方向是先看原始成份可以組成什麼 ->加入我的成分供應中 ->在看加完後又可以組成什麼直到無法組成任何食物為止    
10^4 假設最慘每一次都只更新了一個食材 並且下一次又可以不斷更新 10^4 * 100*100 -> 10^8 但因為有終止條件 這題數據範圍免強過關
另一個更高效解法 topological sort 每個東西要先有某些東西才能解鎖 之後再不斷解鎖其他人 直到沒有入度為0的點

*/
