/*
3377. Digit Operations to Make Two Integers Equal
*/

// TC:O(X * d * (lgn + lgP)) X為可能要處理的數字量,P是有多少個數字在PQ, d是數字位數, n是埃氏篩數字大小 SC:O(X + P)
class Solution {
public:
    int minOperations(int n, int m) {
        auto isPrime = [&](int n) -> bool {
            if(n == 1) return false;
            for(int i = 2; i*i <= n; i++) {
                if(n % i == 0) return false;
            }  
            return true;
        };
        if(n == m && !isPrime(n)) return m;
        if(isPrime(n) || isPrime(m)) return -1;
        priority_queue<pair<int,int>, vector<pair<int,int>>, greater<pair<int,int>>> pq; // 加總,數字
        pq.push({n,n});
        unordered_map<int, int> minSum;
        while(!pq.empty()) {
            auto [curSum, num] = pq.top();
            pq.pop();
            if(num == m) return curSum;
            if(minSum.find(num) != minSum.end()) continue;
            minSum[num] = curSum;
            string s = to_string(num);
            for(int i = 0; i < s.size(); i++) {
                if(s[i] != '0') {
                    string new_s = s;
                    new_s[i] -= 1;
                    int nxt_num = stoi(new_s);
                    if(!isPrime(nxt_num)) {
                        pq.push({nxt_num + curSum, nxt_num});
                    }
                }
                if(s[i] != '9') {
                    string new_s = s;
                    new_s[i] += 1;
                    int nxt_num = stoi(new_s);
                    if(!isPrime(nxt_num)) {
                        pq.push({nxt_num + curSum, nxt_num});
                    }
                }
            }
        }
        
        return -1;
    }
};
