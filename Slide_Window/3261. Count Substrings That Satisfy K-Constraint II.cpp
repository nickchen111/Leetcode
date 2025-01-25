/*
3261. Count Substrings That Satisfy K-Constraint II
*/

// 2025. 01.25 底下之前寫的方式比較簡單 這方式是過段時間再寫一次時自己領悟的不同視角
class Solution {
    using LL = long long;
public:
    vector<long long> countKConstraintSubstrings(string s, int k, vector<vector<int>>& queries) {
        int n = s.size();
        LL left = 0, cnt1 = 0, cnt0 = 0;
        vector<LL> diff(n+1);
        for(LL right = 0; right < n; right++) {
            cnt1 += (s[right] == '1');
            cnt0 += (s[right] == '0');
            while(cnt1 > k && cnt0 > k) {
                cnt1 -= (s[left] == '1');
                cnt0 -= (s[left++] == '0');
            }
            diff[left] += 1;
            diff[right+1] -= 1;
        }
        vector<LL> arr(n+1); // be careful ! this is 1-index
        vector<LL> presum(n+1);
        for(int i = 0; i < n; i++) {
            arr[i+1] = arr[i] + diff[i];
            presum[i+1] = presum[i] + arr[i+1];
        }
        
        int m = queries.size();
        vector<LL> ans(m);
        auto check = [&](int mid, int r) {
            if(arr[mid+1] + mid > r) {
                return false;
            }
            return true;
        };
        for(int i = 0; i < m; i++) {
            int l = queries[i][0], r = queries[i][1];
            int left = l, right = r;
            while(left < right) {
                int mid = left + (right - left + 1) / 2;
                if(check(mid, r)) left = mid;
                else right = mid - 1;
            }
            // cout << left << ' ' << l << ' ' << i << endl;
            if(check(left, r)) { // 注意 該left 算是會被包含在範圍內的left
                ans[i] = presum[left+1] - presum[l] + (LL)(r - left + 1) * (r - left) / 2;
                // cout << presum[left+1] << ' ' << presum[l] << ' ' << r << ' ' << left << ' ' << i << endl;
            }
            else 
                ans[i] = (LL)(r - l + 2) * (r - l + 1) / 2;
        }
        return ans;
    }
};

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
        int cnt[2]{}, i = 0;
        for (int j = 0; j < n; j++) {
            cnt[s[j] & 1]++;
            while (cnt[0] > k && cnt[1] > k) {
                cnt[s[i++] & 1]--;
            }
            left[j] = i;
            presum[j + 1] = presum[j] + j - i + 1;
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
