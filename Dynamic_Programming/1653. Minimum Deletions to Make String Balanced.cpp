/*
1653. Minimum Deletions to Make String Balanced
*/

// TC:O(n) SC:O(n)
class Solution {
public:
    int minimumDeletions(string s) {
        int n = s.size();
        vector<int> suffix(n);
        int count = 0;
        for(int i = n - 1; i >= 0; i--){
            suffix[i] = count;
            if(s[i] == 'a') count += 1;
        }
        int res = min(count, n - count);

        count = 0;
        for(int i = 0; i < n; i++){
            res = min(res, suffix[i] + count);
            if(s[i] == 'b') count += 1;
        }

        return res;
    }
};

/*
no ba
only bbbbb or aaaa or aabbbb
*/
