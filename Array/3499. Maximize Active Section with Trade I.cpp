// TC:O(n) SC:O(1) 也可以寫成分組循環
class Solution {
public:
    int maxActiveSectionsAfterTrade(string s) {
        int n = s.size(), cnt = 0, pre0 = INT_MIN, mx = 0, ans = 0;
        for(int i = 0; i < n; i++) {
            cnt ++;
            if(i == n - 1 || s[i] != s[i+1]) {
                if(s[i] == '1') ans += cnt;
                else {
                    mx = max(mx, pre0 + cnt);
                    pre0 = cnt;
                }
                cnt = 0;
            }
        }
        return ans + mx;
    }
};

// 比賽時作法 前後綴分解 TC:O(n) SC:O(n)
class Solution {
public:
    int maxActiveSectionsAfterTrade(string s) {
        /*
        我的想法是選擇一段區間 他被0包圍的 裡面那段是啥都可以被加入答案中，然後看外圈還有多少個1
        這個可以用prefix suffix做
        loop 應該是做說 如果當前是1並且後面也都是1 然後最後保留一個0我就讓這段都是1
        "10110"
        */
        int n = s.size();
        vector<int> prefix(n,-1), suffix(n, n); // 上一個1的位置在哪
        int pos = -1;
        int cnt = 0;
        for(int i = 0; i < n; i++) {
            prefix[i] = pos;
            if(s[i] == '1') {
                pos = i;
                cnt += 1;
            }
        }
        pos = n;
        for(int i = n-1; i >=0; i--) {
            suffix[i] = pos;
            if(s[i] == '1') pos = i;
        }
        int ans = 0, i = 0;
        while(i < n) {
            int j = i;
            if (s[i] == '1') {
                while(j + 1 < n && s[j + 1] == '1') j += 1;
                if(i && j + 1 < n && s[i-1] == '0' && s[j+1] == '0') {
                    ans = max(ans,  i - prefix[i] - 1 + suffix[j] - j - 1);
                }
            }
            i = j + 1;
        }
        return ans + cnt;
    }
};
