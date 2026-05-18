class Solution {
public:
    int minJumps(vector<int>& arr) {
        int n = arr.size();
        unordered_map<int,vector<int>> map;
        vector<bool> visited(n);
        for(int i = 0; i < n; i++){
            map[arr[i]].push_back(i);
        }

        queue<int> q;
        q.push(0);
        int step = -1;
        while(!q.empty()){
            int sz = q.size();
            step += 1;
            while(sz--){
                int curIdx = q.front();
                q.pop();
                if(visited[curIdx]) continue;
                visited[curIdx] = true;
                if(curIdx == n - 1) return step;
                if(curIdx - 1 >= 0 && visited[curIdx-1] == 0){
                    q.push(curIdx-1);
                }
                if(curIdx + 1 < n && visited[curIdx+1] == 0){
                    q.push(curIdx+1);
                }

                for(auto p : map[arr[curIdx]]){
                    q.push(p);
                }
                map.erase(arr[curIdx]);
            }
        }

        return step;
    }
};


/*
每一步可以往前or往後一格 or 找跟自己數字一樣的跳 問說最少幾步可以跳到終點
*/