/*
2516. Take K of Each Character From Left and Right
*/

// 2025.01.18 TC:O(n) SC:O(1)
class Solution {
public:
    int takeCharacters(string s, int k) {
        int n = s.size();
        if(n < 3 * k) return -1;
        int cnt[3];
        for(auto &ch : s) {
           cnt[ch-'a'] += 1;
        }
        if(cnt[0] < k || cnt[1] < k || cnt[2] < k) return -1;
        // 這題跟 1658 很像 要用最少時間取頭取尾 那就是中間盡量長
        int i = 0, ans = 0;
        for(int j = 0; j < n; j++) {
            cnt[s[j] - 'a'] -= 1;
            while(cnt[s[j] - 'a'] < k) {
                cnt[s[i] - 'a'] += 1;
                i += 1;
            }
            ans = max(ans, j - i + 1);
        }
        return n - ans;
    }
};

// 1120 TC:O(n) SC:O(1)
class Solution {
public:
    int takeCharacters(string s, int k) {
        int n = s.size();
        if(n < 3*k) return -1;
        if(k == 0) return 0;
        int j = n-1;
        vector<int> suf(3,0);
        int sum = 0;
        while(j >= 0) {
            suf[s[j]-'a'] += 1;
            if(suf[s[j]-'a'] == k) sum += 1;
            if(sum == 3) break;
            j--;
        }
        if(j < 0) return -1;
        // x x x x x x x 
        int res = n - j;
        vector<int> pre(3,0);
        for(int i = 0; i < n; i++) {
            pre[s[i]-'a'] += 1;
            // while(j < n && i >= j) {
            //     suf[s[j]-'a'] -= 1;
            //     j++;
            // }
            while(j < n) {
                if(suf[s[j]-'a'] + pre[s[j]-'a'] > k) {
                    suf[s[j]-'a'] -= 1;
                    j++;
                }
                else break;
            }
            res = min(res, i+1 + (n-j));
        }

        return res;
    }
};



/*
每次可以從前or後拿元素 問說最少拿多少次可以a, b, c 都拿到至少k個
*/

// TC:O(n) SC:O(1)
class Solution {
public:
    int takeCharacters(string s, int k) {
        int A = 0; int B = 0; int C = 0;
        for(int i = 0; i<s.size(); i++){
            if(s[i] == 'a') A+=1;
            else if(s[i] == 'b') B+=1;
            else if(s[i] == 'c') C+=1;
        }
        if(A < k || B < k || C < k) return -1;

        A = A-k; B = B-k; C = C-k;
        int res = 0;
        int n = s.size();
        int j = 0;
        int countA = 0; int countB = 0; int countC = 0;
        for(int i = 0; i<s.size(); i++){
            while(countA <= A && countB <= B && countC <= C){
                res = max(res,j-i);
                if(j == n) break;
                if(s[j] == 'a') countA+=1;
                else if(s[j] == 'b') countB+=1;
                else if(s[j] == 'c') countC+=1;
                j++;
            }
            if(s[i] == 'a') countA-=1;
            else if(s[i] == 'b') countB-=1;
            else if(s[i] == 'c') countC-=1;
        }

        return n-res;
    }
};
/*
每一次都能從最前或者最後拿數字 return最少需要拿幾次 才能拿到a b c三種各字數量k個
在條件滿足的狀況下中間最長的window可以多寬 中間的windo必定滿足 每個字的總數目-K >= count 
此題變相在問一個區間限制次數的話最長會是多少
*/
