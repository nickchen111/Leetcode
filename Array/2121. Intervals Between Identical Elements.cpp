/*
2121. Intervals Between Identical Elements
*/

// TC:O(n) SC:O(n)
class Solution {
    using LL = long long;
public:
    vector<long long> getDistances(vector<int>& arr) {
        int n = arr.size();
        vector<LL> res(n);

        unordered_map<int, vector<int>> pos;
        
        for(int i = 0; i < n; i++){
            pos[arr[i]].push_back(i);
        }

        for(auto & p : pos){
            if(p.second.size() == 1) {
                res[p.second[0]] = 0;
                continue;
            }
            int m = p.second.size();
            vector<LL> presum(m+1);
            presum[0] = 0;
            for(int i = 1; i <= m; i++){
                presum[i] = presum[i-1] + p.second[i-1];
            }
            for(int i = 0; i < m; i++){
                LL cur = (p.second[i] * (LL)(i) - presum[i]) + (presum[m] - presum[i+1]) - p.second[i]*(LL)(m-1-i);
                res[p.second[i]] = cur;
            }
        }

        return res;

    }
};

// 純公式寫法做結論轉移 不用presum
class Solution {
public:
    vector<long long> getDistances(vector<int>& arr) {
        int n = arr.size();
        vector<long long> rets(n, 0);
        unordered_map<int, vector<int>> Map;

        for(int i = 0; i < arr.size(); ++i) {
            Map[arr[i]].push_back(i);
        }

        for(auto& [val, pos]: Map) {
            for(int x: pos) {
                rets[pos[0]] += x - pos[0];
            }

            for(int i = 1; i < pos.size(); ++i) {
                rets[pos[i]] = rets[pos[i-1]] + (pos[i] - pos[i-1]) * i - (pos[i] - pos[i-1]) * (pos.size() - i);
            }
        }

        return rets;
    }
};

/*
找每個數字 如果有重複出現將他們每點的距離差取絕對值相加 
如果沒有重複就是 0 當下數字減去別的數字
[1 3 5 7] -> 12 8 8 12  -> ex 3  3*(i) + presum[i] + (presum[n]-presum[i+1]) - 3*(n-1-i);
紀錄每個數字的位置 然後對他做presum 
*/
