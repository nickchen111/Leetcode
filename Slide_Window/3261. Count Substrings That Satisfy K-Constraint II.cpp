/*
3261. Count Substrings That Satisfy K-Constraint II
*/

// TC:O(n + mlgn) SC:O(n)
class Solution {
    using LL = long long;
public:
    vector<long long> countKConstraintSubstrings(string s, int k, vector<vector<int>>& queries) {
        int n = s.size();
        vector<LL> left(n);
        vector<LL> presum(n+1);
        int count1 = 0, count0 = 0;
        int i = 0;
        for(int j = 0; j < n; j++){
            if(s[j] == '1') count1 += 1;
            else count0 += 1;
            while(count1 > k && count0 > k){
                if(s[i] == '1') count1 -= 1;
                else count0 -= 1;
                i++;
            }
            left[j] = i;
            presum[j+1] = presum[j] + (j-i+1);
        }
        
        int m = queries.size();
        vector<LL> res(m);
        for(int i = 0; i < m; i++){
            LL l = queries[i][0], r = queries[i][1];
            LL j = lower_bound(left.begin()+l, left.begin()+r+1, l) - left.begin(); // 大於等於l的第一個位置
            res[i] = presum[r+1] - presum[j] + (LL)(j-l+1)*(j-l)/2;
            
        }
        
        return res;
        
    }
};


// Bit 寫法 更優雅一點 TC:O(n + mlgn) SC:O(n)
class Solution {
    using LL = long long;
public:
    vector<long long> countKConstraintSubstrings(string s, int k, vector<vector<int>>& queries) {
        int n = s.size();
        vector<LL> left(n);
        vector<LL> presum(n+1);
        int count1 = 0, count0 = 0;
        int cnt[2]{}, l = 0;
        for (int i = 0; i < n; i++) {
            cnt[s[i] & 1]++;
            while (cnt[0] > k && cnt[1] > k) {
                cnt[s[l++] & 1]--;
            }
            left[i] = l;
            // 计算 i-left[i]+1 的前缀和
            presum[i + 1] = presum[i] + i - l + 1;
        }
        
        int m = queries.size();
        vector<LL> res(m);
        for(int i = 0; i < m; i++){
            LL l = queries[i][0], r = queries[i][1];
            LL j = lower_bound(left.begin()+l, left.begin()+r+1, l) - left.begin(); // 大於等於l的第一個位置
            res[i] = presum[r+1] - presum[j] + (LL)(j-l+1)*(j-l)/2;
            
        }
        
        return res;
        
    }
};
