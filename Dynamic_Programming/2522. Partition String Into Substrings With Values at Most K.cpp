/*
2522. Partition String Into Substrings With Values at Most K
*/

//  DP TC:O(n) SC:O(n) 
class Solution {
    int dp[100005];
public:
    int minimumPartition(string s, int k) {
        int n = s.size();
        s = "#" + s;
        int m = to_string(k).size();
        if(m == 1){
            for(int i = 1; i <= n; i++){
                if(s[i]-'0' > k) return -1;
            }
        }

        dp[0] = 0;
        for(int i = 1; i <= n; i++){
            //長度可以符合m的情況
            if(i - m + 1 >= 1 && stoi(s.substr(i-m+1, m)) <= k){
                dp[i] = dp[i-m] + 1;
            }
            else {
                //考量兩點 1. 如果m超大變負數代表那段區間都可以被接受 2.剛好符合的長度不行往下降一個長度絕對可以
                dp[i] = dp[max(0, i - m + 1)] + 1;
            }
        }

        return dp[n];
    }
};

// Greedy TC:O(n) SC:O(1)
class Solution {
public:
    int minimumPartition(string s, int k) {
        long long num = 0, count = 0;
        for(int i = 0; i < s.size(); i++){
            num = num * 10 + s[i] - '0';
            if(num > k){
                count++;
                num = s[i] - '0';
            }
            //如果是個位數的情況 還是大於k
            if(num > k) return -1;
        }

        return count + 1;
    }
};

/*
此題給你一串字串 然後搭配一個上限 k 問說最少次數的將字串分割後 分割出來的數字不超過k的方式可以分出幾個區
dp[i] : the minimum number of substrings in a good partition of s[0:i]
理解題目後會發現如果一個數字想要跟前面的搭上 那一定是先試試看能否跟正好長度的情況上搭上 
如果不行那就會找在後一個肯定能搭上 ex k = 293  string: 129 來了一個5 -> 295 x -> 95 -> O
並且要理解如果字串越長分出來的區間肯定就會越多  不可能 長度從100 變 101 區間從 5 -> 4
*/
