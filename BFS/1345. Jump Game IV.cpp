/*
1345. Jump Game IV
*/

// TC:O(n) SC:O(n)
class Solution {
public:
    int minJumps(vector<int>& arr) {
        int n = arr.size();
        unordered_map<int, vector<int>> map;
        vector<int> visited(n);
        for(int i = 0; i < n; i++){
            map[arr[i]].push_back(i);
        }

        queue<int> q;
        q.push(0);
        visited[0] = 1;

        int step = -1;
        while(!q.empty()){
            int sz = q.size();
            step += 1;
            while(sz--){
                int idx = q.front();
                q.pop();
                if(idx == n-1) return step;
                if(idx+1 < n && visited[idx+1] == 0){
                    q.push(idx+1);
                }
                if(idx-1 >= 0 && visited[idx-1] == 0) {
                    q.push(idx-1);
                }
                if(map.find(arr[idx]) != map.end()){
                    for(auto p : map[arr[idx]]){
                        visited[p] = 1;
                        q.push(p);
                    }
                    map.erase(arr[idx]);
                }
            }
        }

        return -1;
    }
};

/*
升級版jump game
可往前往後跳一格 或者跳到跟當前數字一樣的地方 但是i != j
問說從起點跳到終點的最短路徑 
1 <= arr.length <= 5 * 10^4
看來只接受 O(n) or (nlgn)
花了20分鐘嘗試Binary Search但是因為你不能確定是你前面的哪個點跳過來最近所以二分找點這招失效
也沒辦法二分 肯定前面的點比你還小 等於是花n^2時間找最佳解
此題最佳解還是用BFS方式去思考每個點的三種選擇
*/
