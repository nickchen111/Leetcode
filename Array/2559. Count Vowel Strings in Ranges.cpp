// TC:O(n) SC:O(n)
class Solution {
public:
    vector<int> vowelStrings(vector<string>& words, vector<vector<int>>& queries) {
        int m = queries.size();
        int n = words.size();
        unordered_set<char> set = {'a', 'e', 'i', 'o', 'u'};
        vector<int> presum(n+1);
        for(int i = 0; i < n; i++) {
            if(set.find(words[i][0]) != set.end() && set.find(words[i].back()) != set.end()) {
                presum[i+1] = presum[i] + 1;
            }
            else presum[i+1] = presum[i];
        }

        vector<int> res(m);
        for(int i = 0; i < m; i++) {
            int a = queries[i][0], b = queries[i][1];
            res[i] = presum[b+1] - presum[a];
        }
        return res;
    }
};
