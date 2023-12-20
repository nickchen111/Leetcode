/*
2182. Construct String With Repeat Limit
*/

//TC:O(n + n*lg26) SC:O(n)
class Solution {
public:
    string repeatLimitedString(string s, int repeatLimit) {
        int n = s.size();
        unordered_map<char, int> freq;
        priority_queue<char, vector<char>, less<char>> pq;
        for(int i = 0; i < n; i++){
            freq[s[i]] += 1;
        }
        for(auto p : freq){
            pq.push(p.first);
        }

        string res;
        while(!pq.empty()){
            char ch = pq.top();
            pq.pop();
            if(freq[ch] <= repeatLimit){
                int num = freq[ch];
                for(int i = 0; i < num; i++){
                    res.push_back(ch);
                }
                freq[ch] = 0;
            }
            // o p q r s t u v
            else {
                for(int i = 0; i < repeatLimit; i++){
                    res.push_back(ch);
                }

                freq[ch] -= repeatLimit;
                if(!pq.empty()){
                    res += pq.top();
                    freq[pq.top()] -= 1;
                    if(freq[pq.top()] == 0) pq.pop();
                    pq.push(ch);
                }
                else {
                    break;
                }
            }
        }

        return res;
    }
};

/*
此題要你用給定的字串組成字典序最大的狀況 並且給你連續出現的字不能超過的次數
如果某個超小的字母超多個 那他肯定會被被迫穿插 但這種情況在這題沒事
因為還是要先比前面的字 不一定要將所有字都用完
PQ裝從小到大的字 一個map紀錄頻率  如果較大的字不夠limit全用 超過的話 先記錄起來 之後找次大的字補一個
重複此動作 直到沒有次大的字
*/
