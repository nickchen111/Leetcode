// TC:O(n * M) M 為數字十進制平均長度 SC:O(1)
class Solution {
public:
    vector<int> getNoZeroIntegers(int n) {
        int cur = n / 2;
        auto check = [](int m) -> bool {
            while (m) {
                int tmp = m % 10;
                if (tmp == 0) return false;
                m /= 10;
            }
            return true;
        };
        while (true) {
            if (check(cur) && check(n - cur)) return {cur, n - cur};
            cur += 1;
        }

        return {};
    }
};
