/*
3307. Find the K-th Character in String Game II
*/

// Recursion TC:O(max(n, lgk)) SC:O(1)
class Solution {
    using LL = long long;
public:
    char kthCharacter(long long k, vector<int>& operations) {
        if(operations.empty()) return 'a';

        int op = operations.back();
        // 判斷 k 是在右半邊還是左半邊 每次都二分 lgk時間複雜度
        operations.pop_back();
        int n = operations.size(); // 這裡是n-1的概念
        // __lg 取lg 因為 最多就是 k <= 2^i -> i >= lgk 大概這個概念 你也可以直接覺得不超過2^60 ~= 10^18次方
        if(n >= (int)__lg(k)+1 || k <= (1LL << n)){
            return kthCharacter(k, operations);
        }
        
        char ch = kthCharacter(k - (1LL << n), operations);

        return 'a' + ((ch - 'a' + op) % 26);
    }
};

// iterative TC:O(max(n, lgk)) SC:O(1)
class Solution {
    using LL = long long;
public:
    char kthCharacter(long long k, vector<int>& operations) {
        int n = min((int)operations.size(), (int)__lg(k)+1);
        int incr = 0;
        for(int i = n-1; i >= 0; i--){
            if(k > (1LL << i)){
                incr += operations[i];
                k -= (1LL << i);
            }
        }

        return 'a' + incr % 26;
    }
};
