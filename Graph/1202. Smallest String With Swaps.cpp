/*
1202. Smallest String With Swaps
*/

//Union find TC:O(n + mlogn + n + nlogn)  SC:O(n) 
class Solution {
    vector<int> parent;
public:
    string smallestStringWithSwaps(string s, vector<vector<int>>& pairs) {
        int n = s.size();
        parent.resize(n);
        for(int i = 0; i < n; i++){
            parent[i] = i;
        }

        for(auto pair : pairs){
            int a = pair[0], b = pair[1];
            if(findFather(a) != findFather(b)){
                union_(a,b);
            }
        }

        unordered_map<int, vector<int>> map; // root idx -> all union idx
        for(int i = 0; i < n; i++){
            map[findFather(i)].push_back(i);
        }

        for(auto p : map){
            string temp;
            for(auto x : p.second){
                temp.push_back(s[x]);
            }
            sort(temp.begin(), temp.end());
            int k = 0;
            for(auto idx : p.second){
                s[idx] = temp[k];
                k++;
            }
        }

        return s;
    }
    int findFather(int x){
        if(x != parent[x]){
            parent[x] = findFather(parent[x]);
        }

        return parent[x];
    }

    void union_(int x, int y){
        int rootx = parent[x];
        int rooty = parent[y];
        if(rootx > rooty){
            parent[rootx] = rooty;
        }
        else parent[rooty] = rootx;
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
