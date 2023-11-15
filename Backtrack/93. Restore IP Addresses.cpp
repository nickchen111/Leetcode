/*
93. Restore IP Addresses
*/

// TC:O(2^n) SC:O(2^n) 
class Solution {
    vector<string> res;
public:
    vector<string> restoreIpAddresses(string s) {
        vector<string> track;
        backtrack(track,s,0);

        return res;
    }

    void backtrack(vector<string>& track, string& s, int cur){
        if(cur == s.size() && track.size() == 4){
            string tmp = "";
            for(auto str:track){
                tmp+=str+".";
            }
            tmp.pop_back();
            res.push_back(tmp);
            return;
        }
        if(track.size() >= 4) return;
        
        for(int i = cur; i<s.size(); i++){
            if(!isValid(s,cur,i)) continue;
            string str = s.substr(cur,i-cur+1);
            track.push_back(str);
            backtrack(track,s,i+1);
            track.pop_back();
        }
    }
    bool isValid(string& s, int start, int end){
        //no leading zero
        int len = end-start+1;
        if(len >4 || len == 0) return false;
        if(len > 1 && s[start] == '0') return false;
        if(stoi(s.substr(start,len)) > 255) return false;
        return true;
    }
};
