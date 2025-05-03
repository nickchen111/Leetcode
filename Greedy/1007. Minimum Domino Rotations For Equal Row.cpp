// TC:O(6 * n) SC:O(1)
class Solution {
public:
    int minDominoRotations(vector<int>& tops, vector<int>& bottoms) {
        /*
        馬上想到的是嘗試1-6 然後看看當前數字是否能替換即可 這樣需要 6 * n 時間複雜度
        這樣就需要跑兩次，思考是否可以更快
        感覺可以先預判哪邊的1-6較多 較多的去實作即可
        那是否有辦法不要跑1-6呢? 如果兩邊總和不超過n 就不用走啦
        能否不用預處理 直接跑兩個 可以~
        */
        int n = tops.size();
        int ans = n + 1;
        for (int num = 1; num <= 6; num ++) {
            int cnt = 0;
            int tswap = 0, bswap = 0;
            for (int i = 0; i < n; i++) {
                if (tops[i] != num && bottoms[i] != num) {
                    tswap = n + 1;
                    bswap = n + 1;
                    break;
                }
                if (tops[i] != num) tswap += 1;
                else if (bottoms[i] != num) bswap += 1;
            }
            ans = min({tswap, bswap, ans});
        }
        return ans == n + 1 ? -1 : ans;
    }
};

class Solution {
public:
    int minDominoRotations(vector<int>& tops, vector<int>& bottoms) {
        int n = tops.size();
        vector<int> cnt1(6), cnt2(6);
        for (int i = 0; i < n; i++) {
            cnt1[tops[i]-1] += 1;
            cnt2[bottoms[i]-1] += 1;
        }
        int ans = n + 1;
        for (int num = 0; num < 6; num ++) {
            int cnt = 0;
            int tswap = 0, bswap = 0;
            if (cnt1[num] + cnt2[num] < n) continue;
            for (int i = 0; i < n; i++) {
                if (tops[i]-1 != num && bottoms[i]-1 != num) {
                    tswap = n + 1;
                    bswap = n + 1;
                    break;
                }
                if (tops[i]-1 != num) tswap += 1;
                else if (bottoms[i]-1 != num) bswap += 1;
            }
            ans = min({tswap, bswap, ans});
        }
        return ans == n + 1 ? -1 : ans;
    }
};
};
