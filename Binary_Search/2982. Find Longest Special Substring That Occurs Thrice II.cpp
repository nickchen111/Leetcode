/*
2982. Find Longest Special Substring That Occurs Thrice II
*/

// Hash Map by Vector TC:O(n + klgk) k 為某字母出現的長度可能性數量 SC:O(n)
class Solution {
public:
    int maximumLength(string s) {
        int n = s.size();
        vector<vector<int>> arr(26);
        //找每一段最長的連續出現字
        vector<int> maxLen(n);
        for(int i = n-1; i >= 0; i--){
            maxLen[i] = 1;
            if(i+1 < n && s[i] == s[i+1]){
                maxLen[i] = maxLen[i+1]+1;
            }
            arr[s[i]-'a'].push_back(maxLen[i]);
        }
        
        int res = -1;
       
        for(int c = 0; c < 26; c++){
            if(arr[c].size() < 3) continue;
            sort(arr[c].rbegin(), arr[c].rend());
            res = max(res, arr[c][2]);
            
        }
        
        return res;
     
    }
};

// Binary Search + Slide Window TC:O(nlgn) SC:O(n) 
class Solution {
public:
    int maximumLength(string s) {
        int n = s.size();
        int low = 0;
        int high = n-1;
        int maxLen = -1;
        //長度
        while(low < high){
            int mid = low + (high - low+1)/2;
            if(check(s,mid)){
                low = mid;
                maxLen = max(maxLen, mid);
            }
            else high = mid-1;
        }
        
       
        return maxLen;
    }
    
    bool check(string& s, int len){
        unordered_map<string, int> map;
        int n = s.size();
        int j = 0;
        int i = 0;
        string temp;
        while(j < n){
            temp += s[j];
            if(s[j] != s[i]){
                temp = "";
                temp += s[j];
                i = j;
                j++;
                continue;
            }
            if(temp.size() == len) {
                map[temp] += 1;
                if(map[temp] >= 3) return true;
                temp.erase(0,1); // 這個寫法學起來 可以消除前面元素
                i++;
            }
            
            j++;
        }
        
        return false;
    }
};



// Binary Search TC:O(nlgn) SC:O(n) -> TLE
class Solution {
public:
    int maximumLength(string s) {
        int n = s.size();
        int low = 0;
        int high = n;
        //長度
        while(low < high){
            int mid = low + (high - low+1)/2;
            if(check(s,mid)){
                low = mid;
            }
            else high = mid-1;
        }
        
        if(low == 0) return -1;
        return low;
    }
    
    bool check(string& s, int len){
        unordered_map<string, int> map;
        vector<int> freq(26,0);
        int count = 0;
        int n = s.size();
        int j = 0;
        for(int i = 0; i < n; i++){
            while(j < n && j-i+1 <= len){
                string str = s.substr(i,j-i+1);
                freq[s[j]-'a'] += 1;
                if(freq[s[j]-'a'] == 1) count += 1;
                if(count == 1 && j-i+1 == len) map[str] += 1;
                j++;
            }
            
            freq[s[i]-'a'] -= 1;
            if(freq[s[i]-'a'] == 0) count -= 1;
        }
        
        for(auto p:map){
            if(p.second >= 3) return true;
        }
        
        return false;
    }
};


/*
數據規模來到 必須線性或者 最多nlgn級別 or善用字母特性 26 試試看binary search-> TLE
規定一個字串要滿足
1. 只有他自己一個字
2. 字串要重複出現至少3次 
這樣的字最長會是多長 沒有的話返回-1
1. slide window 
如果要每個點走到極致 然後再開始計算他有出現過的可能性 會挺難寫的
2. Binary Search nlgn n = 5*10^5 照理來說應該是可行 但是用hash map會超時
3. 利用字母特性26個 每個字都去算他在每一段的連續出現長度 取第三大 如果小於 3個 直接略過
但要紀錄上每個連續字母有可能的長度 要用倒著遍歷 才不會走到尾巴前面短的沒記錄到
if 5:2 4:2 3:5 取哪個  每次都取第三大的準沒錯
ex: 5:1 4:1 3:1 / 5:2 4:1

aaaa 至少 2
aaaaa 長度5 至少可以3次
aaaaaa 長度6 至少4的長度三次 5的兩次 6的一次 
*/
