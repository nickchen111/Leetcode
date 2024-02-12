/*
1722. Minimize Hamming Distance After Swap Operations
*/

// TC:O(nlgn) SC:O(n)
class Solution {
    int parent[100005];
    unordered_map<int, multiset<int>> map;
    int find(int x){
        if(x != parent[x]){
            parent[x] = find(parent[x]);
        }

        return parent[x];
    }

    void union_(int x, int y){
        x = parent[x];
        y = parent[y];
        if(x < y){
            parent[y] = x;
        }
        else parent[x] = y;
    }
public:
    int minimumHammingDistance(vector<int>& source, vector<int>& target, vector<vector<int>>& allowedSwaps) {
        int n = source.size();
        for(int i = 0; i < n; i++){
            parent[i] = i;
        }
        
        // klgk
        for(auto x : allowedSwaps){
            int a = x[0], b = x[1];
            if(find(a) != find(b)){
                union_(a, b);
            }
            
        }

        for(int i = 0; i < n; i++){
            map[find(i)].insert(source[i]); // 某個index 可以去取用哪些數值
        }

        int res = 0;
        for(int i = 0; i < n; i++){
            int a = source[i], b = target[i];
            if(a != b){
                int anc = find(i);
                if(map[anc].find(b) != map[anc].end()){
                    map[anc].erase(map[anc].find(b));
                }
                else {
                    res += 1;
                }
            }
            else {
                int anc = find(i);
                if(map[anc].find(a) == map[anc].end()) res += 1;
                else map[anc].erase(map[anc].find(a));
            }
        }

        return res;
    }
};

/*
可以將指定的index做任意次數的swap
給你兩個source target array 問說經過翻轉之後 每個index上不同的元素最少可以有多少個
UF 並且將某個最小index當代表的所有可以連通的點都匯聚在一個set裡

*/
