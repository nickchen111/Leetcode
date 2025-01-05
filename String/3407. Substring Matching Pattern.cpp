// TC:O(n*m) SC:O(1)
class Solution {
public:
    bool hasMatch(string s, string p) {
        int star = p.find('*');
        int i = s.find(p.substr(0, star));
        return i != string::npos && s.substr(i + star).find(p.substr(star + 1)) != string::npos;
    }
};


// 醜寫法 TC:O(n*m) SC:O(n)
class Solution {
public:
    bool hasMatch(string s, string p) {
        int starPos = p.find('*');
        
        string prefix = p.substr(0, starPos);
        string suffix = p.substr(starPos + 1);
        
        if (prefix.size() + suffix.size() > s.size()) {
            return false;
        }
        int idx1 = -1;
        int idx2 = -1;
        if(!prefix.empty()) {
            for(int i = 0; i < s.size(); i++) {
                int j = 0;
                int i1 = i;
                while(j < prefix.size() && i1 < s.size()) {
                    if(prefix[j] == s[i1]) {
                        j++;
                        i1++;
                    }
                    else break;

                    if(j == prefix.size()) {
                        idx1 = i1;
                        break;
                    }
                }
                if(idx1 != -1) break;
            }
            if(idx1 == -1) return false;
        }
        if(!suffix.empty()) {
            for(int i = max(idx1, 0); i < s.size(); i++) {
                int j = 0;
                int i1 = i;
                while(j < suffix.size() && i1 < s.size()) {
                    if(suffix[j] == s[i1]) {
                        j++;
                        i1++;
                    }
                    else break;
                    
                    if(j == suffix.size()) {
                        idx2 = i1;
                        break;
                    }
                }
                if(idx2 != -1) break;
            }
            if(idx2 == -1) return false;
        }
        return true;
    }
};

/*
"ggmgmrmrm"
"*gmg"
*/

