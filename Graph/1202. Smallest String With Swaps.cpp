/*
1202. Smallest String With Swaps
*/

//update 2025.01.02 Union find TC:O(n + (m + n)* α(n) + nlogn)  SC:O(n)
class Solution {
public:
    string smallestStringWithSwaps(string s, vector<vector<int>>& pairs) {
        int n = s.size();
        vector<int> parent(n);
        for(int i = 0; i < n; i++) parent[i] = i;
        auto find = [&](auto &&find, int x) -> int {
            if(x != parent[x]) {
                parent[x] = find(find, parent[x]); 
            }
            return parent[x];
        };
        auto union_ = [&](int x, int y) -> void{
            x = find(find, x);
            y = find(find, y);
            if(x < y) {
                parent[y] = x;
            } else {
                parent[x] = y;
            }
        };

        for(auto &pair : pairs) {
            int a = pair[0], b = pair[1];
            if(find(find, a) != find(find, b)) union_(a,b);
        }

        // root -> string
        unordered_map<int, vector<int>> index;
        for(int i = 0; i < n; i++) {
            int pa = find(find, i);
            index[pa].push_back(i);
        }
        string res = s;
        for(auto p : index) {
            int pa = p.first;
            string tmp;
            for(auto &idx : p.second) {
                tmp += s[idx];
            }
            sort(tmp.begin(), tmp.end());
            int idxx = 0;
            for(auto &idx : p.second) {
                res[idx] = tmp[idxx];
                idxx ++;
            }
        }

        return res;
        
    }
};

// DFS
class Solution {
    vector<int> graph[100005];
    char pos[100005];
    vector<bool> visited;
    vector<char> ch;
    vector<int> p;
public:
    string smallestStringWithSwaps(string s, vector<vector<int>>& pairs) {
        int n = s.size();
       
        for(auto pair : pairs){
            graph[pair[0]].push_back(pair[1]);
            graph[pair[1]].push_back(pair[0]);
        }

        visited.resize(n);
        for(int i = 0; i < n; i++){
            if(visited[i]) continue;
            DFS(i,s); 
            sort(ch.begin(), ch.end());
            sort(p.begin(), p.end());
            for(int i = 0; i < p.size(); i++){
                pos[p[i]] = ch[i];
            }
            ch.clear();
            p.clear();
        }
        string res;
        for(int i = 0; i < n; i++){
            res.push_back(pos[i]);
        }

        return res;
    }

    void DFS(int cur, string& s){
        visited[cur] = 1;
        ch.push_back(s[cur]);
        p.push_back(cur);
        for(auto x : graph[cur]){
            if(visited[x]) continue;
            DFS(x, s);
        }
    }
};


/*
問說一個string 要經由給定規則的翻轉 達到字典序最小的字串會是什麼
這題藏的很深 當下看會以為是一個貪心題 但是仔細想會發現說他給的翻轉次數沒有限制
代表說有互相連通的字在無數次的翻轉後肯定可以讓他們在限定的位置中排序好
我會想大致實現此目標 有哪些字母可以選->對應有哪些位置可以塞
*/
