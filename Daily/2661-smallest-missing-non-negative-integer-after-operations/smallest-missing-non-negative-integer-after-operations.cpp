class Solution {
public:
    int findSmallestInteger(vector<int>& nums, int value) {
        /*
        原本會有一個最小的數字了 希望讓較大數字去減到他或者小的數字去補到他 讓這個數字可以上升
        */
        vector<int> cnt(value + 1);
        for (auto &x : nums) cnt[((x % value) + value) % value] += 1;
        int ans = 0;
        while (true) {
            if (cnt[ans % value] == 0) return ans;
            cnt[ans % value] -= 1;
            ans += 1;
        }
        return ans;
    }
};