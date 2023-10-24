/*
49. Group Anagrams
*/


// TC:O(n*m) SC:O(n*m) m為字串平均長度
class Solution {
public:
    vector<vector<string>> groupAnagrams(vector<string>& strs) {

        unordered_map<string, vector<string>> map;
        for(auto str:strs){
            string code = encode(str);//對他做編碼
            map[code].push_back(str);
        }
        vector<vector<string>> res;
        for(auto [code, group]:map){
            res.push_back(group);
        }

        return res;
    }

    //不要對傳進去的字串做排序 會修改原始碼 對他進行編碼
    string encode(string& str){
        vector<int> count(26,0);
        for(auto ch:str){
            count[ch-'a']++;
        }
        string code(count.begin(),count.end());
        return code;
    }
};


//直接對字元sort 不編碼
class Solution {
public:
    vector<vector<string>> groupAnagrams(vector<string>& strs) {

        unordered_map<string, vector<string>> map;
        vector<vector<string>> res;
        for(int i = 0; i < strs.size(); i++){
            string s = strs[i];
            sort(s.begin(), s.end());
            map[s].push_back(strs[i]);
        }
        for(auto p:map){
            res.push_back(p.second);
        }

        return res;
    }
};
