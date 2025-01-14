// TC:O(n * ⍺{n)) SC:O(n)
class Solution {
public:
    vector<int> avoidFlood(vector<int>& rains) {
        // 並查集概念是 每段會被灌水的地 都去union到他後面的可以dry out day 遇到相同時 就用map判斷他上一個位置是否在dry out day之前
        int n = rains.size();
        vector<int> pa(n);
        vector<int> idx(n);
        vector<int> res(n,1);
        unordered_map<int,int> occur;
        auto find = [&](int x) -> int {
            int rt = x;
            while(rt != pa[rt]) rt = pa[rt];
            if(x != rt) pa[x] = rt;
            return rt;
        };
        for(int i = 0; i < n; i++) {
            if(rains[i]) {
                if(i && rains[i-1]) {
                    pa[i] = pa[i-1];
                }
                else {
                    pa[i] = i;
                    idx[i] = 1000000;
                }
                if(occur.find(rains[i]) != occur.end()) {
                    int lastPos = occur[rains[i]];
                    int f = find(lastPos);
                    if(idx[f] >= i) return {};
                    res[idx[f]++] = rains[i];
                    if(idx[f] < rains.size() && rains[idx[f]]) pa[f] = find(idx[f]);
                }
                occur[rains[i]] = i;
                res[i] = -1;
            } else if(i && rains[i-1]){
                idx[find(i-1)] = i;
            }
        }

        return res;
    }
};
