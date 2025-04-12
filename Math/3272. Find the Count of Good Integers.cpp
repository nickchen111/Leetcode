// TC:O(10^m + nlgn)  m = (n-1) / 2 SC:O(10^m * n)
class Solution {
public:
    long long countGoodIntegers(int n, int k) {
        /*
        一個數字要能夠被k整除 並且要是回文串 然後長度是n會有多少種這種數字
        所以回文串枚舉一波 然後要判斷他可以被k整除 可以的話再做排列組合 看他能有多少種數字排法
        但要注意不重不漏 有可能重複 ex: 12321, 21312 可以用哈希表 紀錄排過的數字 從小到大排序
        再來就是排序了 他是有重複的排列個數 就會是n! / c0! c1! c2!...c9! 這是沒前導零的情況
        有前導零: ex: 10221 ->  4 * 5! (不考慮重複情況) 
        再除上重複的 4 * 5! / 2! * 2! * 2! 也就是 (n - c0) * (n - 1) ! / c0!...c9! 
        因為數字了不起10! 還不需要用到模運算求逆元
        */
        vector<int> fac(n+1);
        fac[0] = 1;
        for(int i = 1; i <= n; i++) {
            fac[i] = fac[i-1] * i;
        }

        int base = pow(10, (n-1) / 2);
        unordered_set<string> visited;
        int ans = 0;
        for (int i = base; i < base * 10; i++) {
            string s = to_string(i);
            s += string(s.rbegin() + (n % 2), s.rend());
            if(stoll(s) % k) continue; // 無法整除
            ranges::sort(s);
            if(visited.count(s)) continue;
            visited.insert(s);
            vector<int> cnt(10);
            for(auto &ch: s) {
                cnt[ch - '0'] += 1;
            }
            int num = (n - cnt[0]) * fac[n - 1];
            for(int i = 0; i <= 9; i++) {
                num /= fac[cnt[i]];
            }
            ans += num;
        }
        return ans;
    }
};
