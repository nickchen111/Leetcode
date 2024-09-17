/*
884. Uncommon Words from Two Sentences
*/

// TC:O(m+n) SC:O(m+n)
class Solution {
public:
    vector<string> uncommonFromSentences(string s1, string s2) {
        vector<string> res;
        unordered_map<string, int> map1;
        int j = 0;
        while(j < s1.size()){
            string cur;
            while(j < s1.size() && s1[j] != ' '){
                cur += s1[j];
                j++;
            }
            j++;
            map1[cur] += 1;
        }

        j = 0;
        unordered_map<string, int> map2;
        while(j < s2.size()){
            string cur;
            while(j < s2.size() && s2[j] != ' '){
                cur += s2[j];
                j++;
            }
            j++;
            map2[cur] += 1;
        }

        for(auto p : map1){
            if(p.second == 1 && map2.find(p.first) == map2.end()) res.push_back(p.first);
        }
        for(auto p : map2){
            if(p.second == 1 && map1.find(p.first) == map1.end()) res.push_back(p.first);
        }

        return res;
    }
};
