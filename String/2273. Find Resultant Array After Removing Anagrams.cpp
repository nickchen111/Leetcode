// TC:O(nlogn) SC:O(n)
class Solution {
public:
    vector<string> removeAnagrams(vector<string>& words) {
        // 為了方便比較可以先將字串排序 就可以直接比較了 後面就用stack
        unordered_map<string, string> mp;
        for (auto &s : words) {
            string tmp = s;
            ranges::sort(tmp);
            mp[s] = tmp;
        }
        
        vector<string> st;
        
        for (auto &s : words) {
            if (!st.empty() && mp[st.back()] == mp[s]) {
                continue;
            }
            st.push_back(s);
        }

        return st;
    }
};
