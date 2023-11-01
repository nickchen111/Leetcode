/*
3. Longest Substring Without Repeating Characters
*/

// 10/9
class Solution {
public:
    int lengthOfLongestSubstring(string s) {
        // slide window maximum
        int res = 0;
        int left = 0;
        int right = 0;
        unordered_map<char,int> map;
        while(right < s.size()){
            char c = s[right];
            map[c]++;
            right++;
            while(map[c] > 1){
                map[s[left]]--;
                left++;
            }
            res = max(res, right-left);
        }

        return res;
    }
};

// 11/1
class Solution {
public:
    int lengthOfLongestSubstring(string s) {
        int n = s.size();
        int i = 0;
        int res = 0;
        unordered_map<char,int> map;
        for(int j=0; j<n; j++){
            while(map[s[j]] > 0){
                map[s[i]]-=1;
                i++;
            }
            res = max(res, j-i+1);
            map[s[j]]+=1;
        }

        return res;
    }
};



//slide window 直接將two pointer當作count 不用另外多設一個count time:o(n) space: o(n)
class Solution1 {
public:
    int lengthOfLongestSubstring(string s) {
       int ans = 0;
       int j = 0;
       int i = 0;
       int n = s.length();
       unordered_set<char> set;
       while(i < n && j < n){
           if(set.find(s[i]) == set.end()){
           set.insert(s[i++]);
           ans = max(ans, i-j);
           }
           else set.erase(s[j++]);
       }
       return ans;
    }
};


//正版slide window 模板 tc: o(n) sc:o(k) k為最長子串長度
class Solution {
//用slide window的方法
public:
    int lengthOfLongestSubstring(string s) {
        int left = 0, right = 0;
        unordered_map<char, int> window;
        int ans = 0;

        while(right < s.size()){
            char c = s[right];
            right++;
            window[c]++;

            while(window[c] > 1){
                char d = s[left];
                left++;
                window[d]--;
            }
            ans = max(ans, right-left);
        }
        return ans;
    }
};

/*
解題思維   
這題就不需要need容器紀錄所需字元了 也不需要valid 但還是需要window
然後要判斷哪個才是最大的
*/
