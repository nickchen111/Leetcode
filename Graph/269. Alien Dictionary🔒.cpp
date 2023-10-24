/*
269. Alien Dictionary 🔒
*/


//topological sort by BFS TC:O(C+V+E) SC:O(V+E) C為所有字的總數 V為節點總數->字串個數 E為edge數
class Solution {
public:
    string alienOrder(vector<string> &words) {
        //topological sort
        //建立一個鄰接表
        unordered_ma<char, unordered_set<char>> next;
        unordered_map<char, int> indegree;
        //先將所有出現過的字顯示入度0
        for(auto word:words){
            for(auto ch:word){
                indegree[ch] = 0;
            }
        }

        for(int i = 0; i<words.size()-1; i++){
            string s = words[i];
            string t = words[i+1];
            //極端狀況 ex ab a
            if(s.size() > t.size() && s.substr(t.size()) == t) return "";

            for(int j = 0; j<min(s.size(),t.size()); j++){
                if(s[j]==t[j]) continue;
                if(next[s[j]].find(t[j]) == next[s[j]].end()){
                    next[s[j]].insert(t[j]);
                    indegree[s[j]]+=1;
                }
                break;//後面的字都沒意義了
            }

            queue<int> q;
            //入度0的加入隊列
            for(auto x:indegree){
                if(x.second == 0) q.push(x.first);
            }
            string res;
            //將入度0的慢慢彈出並且看他是否讓其他人入度變成0
            while(!q.empty()){
                char cur = q.front();
                res.push_back(cur);

                for(auto neighbor:next[cur]){
                    indegree[neighbor]-=1;
                    if(indegree[neighbor] == 0) q.push(neighbor);
                }
            }

            //代表有環
            if(res.size() != indegree.size()) return "";
            else return res;
        }
    }
};
