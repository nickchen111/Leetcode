/*
2904. Shortest and Lexicographically Smallest Beautiful String
*/

// TC:O(n) SC:O(k)
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
