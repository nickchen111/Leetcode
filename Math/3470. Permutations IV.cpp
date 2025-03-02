// TC:O(m^2) SC:O(m) m=min(n,f −1 (k))
// 重要步驟 預處理 overflow的數字就都免除 ex n超大的f[n] 超過預期範圍
vector<long long> f = {1};
int init = []() {
    for (int i = 1; f.back() < 1e15; i++) {
        f.push_back(f.back() * i);
        f.push_back(f.back() * i);
    }
    return 0;
}();
class Solution {
public:
    vector<int> permute(int n, long long k) {
        k --;
        if(n < f.size() && k >= f[n] * (2 - n % 2)) return {};
        vector<int> cand[2];
        for(int i = 2; i <= n; i += 2) cand[0].push_back(i);
        for(int i = 1; i <= n; i += 2) cand[1].push_back(i);
        
        vector<int> ans;
        int parity = 1;
        for(int i = 0; i < n; i++) {
            int j = 0; // 拿來判斷在哪一組
            if(n - i - 1 < f.size()) {
                long long size = f[n-i-1];
                j = k / size;
                k %= size;
                // 如果是偶數開頭 就會有double可能 所以parity要改 一開始設為1 並且組數 // 2
                if(n % 2 == 0 && i == 0) {
                    parity = 1 - j % 2; // 根據他拿的組數判斷現在應該是在哪個parity
                    j /= 2;
                }
            }
            ans.push_back(cand[parity][j]);
            cand[parity].erase(cand[parity].begin() + j);
            parity ^= 1;
        }
        return ans;
    }
};
