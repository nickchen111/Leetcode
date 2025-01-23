/*
1234. Replace the Substring for Balanced String
*/


// TC:O(n) SC:O(1)
class Solution {
public:
    int balancedString(string s) {
        int n = s.size(), ans = s.size(), i = 0;
        // 可以知道有多少個多餘的字元 他們分別是哪些 去找出符合這些字元的最短子串
        int target = n/4;
        vector<int> redundant(4, -target);
        unordered_map<char, int> mp = {{'Q', 0}, {'W',1},{'E',2}, {'R',3}};
        for(auto &ch : s) {
            redundant[mp[ch]] += 1;
        }
        int sum = 0;
        for(auto &r : redundant) {
            if(r > 0) sum += 1;
        }
        if(sum == 0) return 0;
        int valid = 0;
        vector<int> cnt(4);
        for(int j = 0; j < n; j++) {
            cnt[mp[s[j]]] += 1;
            if(cnt[mp[s[j]]] == redundant[mp[s[j]]]) valid += 1;
            while(valid == sum) {
                ans = min(ans, j - i + 1);
                if(cnt[mp[s[i]]] == redundant[mp[s[i]]]) valid -= 1;
                cnt[mp[s[i]]] -= 1;
                i += 1;
            }
        }
        return ans;
    }
};

// TC:O(n*4) SC:O(n)
class Solution {
    unordered_map<char, int> count;
    int n;
public:
    int balancedString(string s) {
        n = s.size();
        
        for(auto ch : s){
            count[ch] += 1;
        }
        bool flag = 1;
        for(auto x : count){
            if(x.second  != n/4) flag = 0;
        }
        if(flag) return 0;

        unordered_map<char, int> sum;
        int j = 0;
        int res = INT_MAX;
        for(int i = 0; i < n; i++){
            
            while(j < n && !isOk(sum,s)){
                sum[s[j]] += 1;
                j++;
            }
            if(isOk(sum,s)){
                res = min(res, j-i);
            }
            sum[s[i]] -= 1;
        }

        return res;
    }

    bool isOk(unordered_map<char, int>& sum, string& s){

        for(auto x : count){
            char ch = x.first;
            int freq = x.second;
            if(freq - sum[ch] > n/4) return false;
        }

        return true;
    }
};


//  TC:O(n) SC:O(n)
class Solution {
public:
    int balancedString(string s) {
        int n = s.size();
        unordered_map<char, int> map;
        int limit = n/4;
    
        for(int i = 0; i < n; i++){
            map[s[i]] += 1;
        }

        int valid = 0;
        unordered_set<char> set;

        if(map['W'] <= limit){
            set.insert('W');
            valid++;
        } 
        if(map['E'] <= limit){
            set.insert('E');
            valid++;
        } 
        if(map['R'] <= limit){
            set.insert('R');
            valid++;
        }
        if(map['Q'] <= limit){
            set.insert('Q');
            valid++;
        }
        


        int j = 0;
        int res = INT_MAX;
        for(int i = 0; i < n; i++){
            while(j < n && valid < 4){
                map[s[j]] -= 1;
                if(map[s[j]] <= limit && set.find(s[j]) == set.end()){
                    set.insert(s[j]);
                    valid++;
                }
                j++;
            }
            
            if(valid == 4) res = min(res, j-i);
            map[s[i]] += 1;
            if(map[s[i]] > limit) {
                set.erase(s[i]);
                valid -= 1;
            }
        }

    
        return res;
    }
};

/*
字串只包含 QWER 問說最短需要換多長的substring讓裡面QWER出現次數都一樣
長度確保會是4的倍數
QQWWQERR
QWRQWRQW
我可以確定說這一substring會固定多少個 8/4 = 2如果超過了的話？
WWQQRRR 差1W1Q2E  RQRQQ
找一個區間可以去改 可以利用map判斷外圍已經有哪些元素 然後利用現在圈起來的元素去補足缺少的元素
就是去圈出一些窗口讓外圍元素都不會超過n/4到那時就可以更新答案然後縮小窗口
*/
