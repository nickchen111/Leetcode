/*
2904. Shortest and Lexicographically Smallest Beautiful String
*/

// Sliding Window  TC:O(n^2) SC:O(1)
class Solution {
public:
    string shortestBeautifulSubstring(string s, int k) {
        if (count(s.begin(), s.end(), '1') < k) {
            return "";
        }
        string ans = s;
        int cnt1 = 0, left = 0;
        for (int right = 0; right < s.length(); right++) {
            cnt1 += s[right] - '0';
            while (cnt1 > k || s[left] == '0') {
                cnt1 -= s[left++] - '0';
            }
            if (cnt1 == k) {
                string t = s.substr(left, right - left + 1);
                if (t.length() < ans.length() || t.length() == ans.length() && t < ans) {
                    ans = move(t);
                }
            }
        }
        return ans;
    }
};


// TC:O(n^2) SC:O(k)
class Solution {
public:
    string shortestBeautifulSubstring(string s, int k) {
        int n = s.size();
        int count = 0;
        string res = "";
        int len = INT_MAX;
        deque<int> q;
        for(int i = 0; i<n; i++){
            q.push_back(i);
            if(s[i] == '1') count++;
            while(count > k){
                count -= (s[q.front()] == '1');
                q.pop_front();
                while(s[q.front()] == '0') q.pop_front();
            }
            if( !q.empty() && count == k && len > q.size() || (len == q.size() && s.substr(q.front(),len) < res )){
                while(s[q.front()] == '0') q.pop_front();
                res = s.substr(q.front(),q.back()-q.front()+1);
                len = q.size();
                
            }
        }
        
        return res;
    }
};
