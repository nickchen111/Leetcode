// TC:O(n) SC:O(n)
class Solution {
public:
    std::vector<int> getRow(int rowIndex) {
        vector<int> res(1, 1);
        long long prev = 1;
        for(int k = 1; k <= rowIndex; k++) {
            long long next_val = prev * (rowIndex - k + 1) / k;
            res.push_back(next_val);
            prev = next_val;
        }
        return res;
    }
};

// 公式 TC:O(n^2) SC:O(n) 
const int MX = 34;
vector<int> c[MX];

auto init = []() {
    for (int i = 0; i < MX; i++) {
        c[i].resize(i + 1, 1);
        for (int j = 1; j < i; j++) {
            // 左上方的数 + 正上方的数
            c[i][j] = c[i - 1][j - 1] + c[i - 1][j];
        }
    }
    return 0;
}();

class Solution {
public:
    vector<int> getRow(int rowIndex) {
        return c[rowIndex];
    }
};
