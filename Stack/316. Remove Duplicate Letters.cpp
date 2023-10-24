/*
316. Remove Duplicate Letters
*/

//TC:O(n) SC:O(1)
class Solution {
public:
    string removeDuplicateLetters(string s) {
        int n = s.size();
        unordered_map<char,int> map; 
        unordered_set<char> set;
        string res;
        for(int i = 0; i < n; i++){
            map[s[i]]++;
        }

        for(int i = 0; i < n; i++){
            if(set.find(s[i]) != set.end()){
                map[s[i]]--;
                continue;
            }
            while(res.size() > 0 && res.back() > s[i] && map[res.back()] > 0){
                set.erase(res.back());
                res.pop_back();
            }

            set.insert(s[i]);
            res+=s[i];
            map[s[i]]--;
        }
        return res;
    }
};
