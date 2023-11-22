/*
2747. Count Zero Request Servers
*/

// TC:O(n+n*lgn) SC:O(n)
class Solution {
public:
    vector<int> countServers(int n, vector<vector<int>>& logs, int x, vector<int>& queries) {
        for(int i =0; i<logs.size(); i++){
            logs[i] = {logs[i][1],logs[i][0]};
        }
        //按照時間排序
        sort(logs.begin(),logs.end());
        //offline queries 也按照時間對應index排序
        vector<vector<int>> q;
        int m = queries.size();
        for(int i=0; i<m; i++){
            q.push_back({queries[i],i});
        }
        sort(q.begin(),q.end());
        vector<int> res(m);
        unordered_map<int,int>map; // 服務器編號 ->調用次數
        int i = 0; int j = 0;
        for(auto qq:q){
            int t = qq[0]; int idx = qq[1];
            while(j < logs.size() && logs[j][0]<=t){
                map[logs[j][1]]++;
                j++;
            }
            while(i < logs.size() && logs[i][0] < t-x){
                map[logs[i][1]]--;
                if(map[logs[i][1]] == 0){
                    map.erase(logs[i][1]);
                }
                i++;
            }
            res[idx] = n-map.size();
        }

        return res;
    }
};

/*
此題在問某個時間區段沒在做事的guys 那就把所有guys減掉有在做事的guys
*/
