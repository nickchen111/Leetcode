// 調和級數枚舉倍數類似素數篩 TC:O(m + n * lgU)  U 為最大的數字數值 SC:O(U)
class Solution {
public:
    vector<int> assignElements(vector<int>& groups, vector<int>& elements) {
        int n = groups.size(), m = elements.size();
        int mx = *max_element(groups.begin(), groups.end());
        vector<int> target(mx+1, -1);
        vector<int> ans(n, -1);
        for(int i = 0; i < m; i++) {
            if(elements[i] > mx || target[elements[i]] >= 0) continue;
            for(int j = elements[i]; j <= mx; j += elements[i]) {
                if(target[j] == -1) target[j] = i;
            }
        }
        for(int i = 0; i < n; i++) {
            ans[i] = target[groups[i]];
        }
        return ans;
    }
};

// 因式分解: TC:O(m + n * sqrt(U))  U 為最大的數字數值 SC:O(U)
class Solution {
public:
    vector<int> assignElements(vector<int>& groups, vector<int>& elements) {
        int n = groups.size(), m = elements.size();
        unordered_map<int,int> mp;
        vector<int> ans(n, INT_MAX);
        for(int i = 0; i < m; i++) {
            if(!mp.count(elements[i])) mp[elements[i]] = i; 
        }
        for(int i = 0; i < n; i++) {
            for(int j = 1; j*j <= groups[i]; j++) {
                if(groups[i] % j == 0) {
                    int cand1 = j, cand2 = groups[i] / j;
                    if(mp.count(cand1)) {
                        ans[i] = min(ans[i], mp[cand1]);
                    }
                    if(mp.count(cand2)) {
                        ans[i] = min(ans[i], mp[cand2]);
                    }
                }
            }
        }
        for(int i = 0; i < n; i++) {
            if(ans[i] == INT_MAX) ans[i] = -1;
        }
        return ans;
    }
};

/*
30 -> (2, 15), (3, 10), ()
*/
