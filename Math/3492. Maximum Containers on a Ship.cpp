// TC:O(1) SC:O(1)
class Solution {
public:
    int maxContainers(int n, int w, int maxWeight) {
        int cnt = n * n;
        // w * 數量 <=  maxWeight, 數量 <= cnt
        return min(cnt, maxWeight / w);
    }
};
