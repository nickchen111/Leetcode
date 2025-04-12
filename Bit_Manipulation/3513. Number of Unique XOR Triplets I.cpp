// TC:O(1) SC:O(1)
class Solution {
public:
    int uniqueXorTriplets(vector<int>& nums) {
        /*
        問說隨便選三個元素 會有多少種XOR的結果
        n = 1e5
        數字只會從1-n 這個特性需要利用
        XOR : 相同為0, 不同為1
        也就是lgn的位數 他們可能會有辦法 選到 e * e * e or e * o * o ... 就是2^lgn種可能性
        那就看當前最大的二進制位數在哪 
        */
        int n = nums.size();
        int m = bit_width(unsigned(n));
        return n >= 3 ? pow(2, m) : n;
    }
};
