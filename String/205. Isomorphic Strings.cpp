/*
205. Isomorphic Strings
*/

// 新增test case後 兩個字串不一定等長 TC:O(n) SC:O(m+n)
class Solution {
public:
    bool isIsomorphic(string s, string t) {
        unordered_map<char, string> map1;
        unordered_set<string> map2;
        int m = s.size();
        int n = t.size();
        int k = n/m;
        int j = 0;
        for (int i=0; i < m && j < n; i++) {
            if (map1.find(s[i]) != map1.end()){
                if(map1[s[i]] != t.substr(j,k)) return false;
            }
            else if (map2.find(t.substr(j,k)) != map2.end()) return false;
            map1[s[i]]=t.substr(j,k);
            map2.insert(t.substr(j,k));
            j+=k;
        }
        return true;
    }
};

// old TC:O(n) SC:O(m+n)
class Solution {
public:
    bool isIsomorphic(string s, string t) {
         unordered_map<char, char> mp, mp2;
        for (int i=0; i<s.length(); ++i) {
            if (mp[s[i]] && mp[s[i]]!=t[i]) return false;
            if (mp2[t[i]] && mp2[t[i]]!=s[i]) return false;
            mp[s[i]]=t[i];
            mp2[t[i]]=s[i];
        }
        return true;
    }
};
