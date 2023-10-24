/*
332. Reconstruct Itinerary
*/


//構築路徑方式 B + path2 + path1  TC:O(ElgE) SC:O(E)
class Solution {
    static bool cmp(vector<string>& a, vector<string>& b){
        if( a[0] != b[0]){
            return a[0] > b[0];
        }
        else return a>b;
    }
    unordered_map<string, vector<string>> map;
public:
    vector<string> findItinerary(vector<vector<string>>& tickets) {
        sort(tickets.begin(),tickets.end(), cmp);
        
        for(auto ticket:tickets){
            map[ticket[0]].push_back(ticket[1]);
        }

        return DFS("JFK");
    }

    //用構建的方式構建答案路徑
    vector<string> DFS(string start){

        vector<vector<string>> path;
        while(map[start].size() > 0){
            string next = map[start].back();
            map[start].pop_back();
            path.push_back(DFS(next));
        }

        vector<string> res({start});
        for(int i = path.size()-1; i>=0; i--){
            for(auto p:path[i]){
                res.push_back(p);
            }
        }
        return res;
    }
};

//先裝 path1-> path2->B 再reverse TC:O(ElgE) SC:O(E)
class Solution {
    static bool cmp(vector<string>& a, vector<string>& b){
        if( a[0] != b[0]){
            return a[0] > b[0];
        }
        else return a>b;
    }
    unordered_map<string, vector<string>> map;
public:
    vector<string> findItinerary(vector<vector<string>>& tickets) {
        sort(tickets.begin(),tickets.end(), cmp);
        
        for(auto ticket:tickets){
            map[ticket[0]].push_back(ticket[1]);
        }
        vector<string> path;
        DFS("JFK", path);
        reverse(path.begin(), path.end());
        
        return path;
    }

    //改成構築 path1(reverse的) + path2(reverse) + B 在一口氣倒過來
        void DFS(string start, vector<string>& path){

        while(map[start].size() > 0){
            string next = map[start].back();
            map[start].pop_back();
            DFS(next, path);
        }

        path.push_back(start);
    }
};
