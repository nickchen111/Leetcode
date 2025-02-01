// TC:O(n) SC:O(9) -> constant
class Solution {
public:
    string findValidPair(string s) {
        vector<int> freq(9);
        for (char ch : s) {
            freq[ch - '1']++;
        }

        for (int i = 1; i < s.size(); i++) {
            char prev = s[i - 1], curr = s[i];
            if (prev != curr && freq[prev - '1'] == prev - '0' && freq[curr - '1'] == curr - '0') {
                return string(1, prev) + curr;
            }
        }
        return "";
    }
};

