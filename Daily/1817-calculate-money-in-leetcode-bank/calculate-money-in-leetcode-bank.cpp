class Solution {
public:
    int totalMoney(int n) {
        constexpr int D = 7;
        int w = n / D, r = n % D;
        return (w * D * (w + D) + r * (w * 2 + r + 1)) / 2;
    }
};
