/*
271. encode and decode strings
*/


//TC:O(n) SC:O(n)
class Solution {
public:

    string encode(vector<string> &strs) {
        string res;
        //去紀錄編碼的string長度: 長度/字串 
        for(auto str:strs){
            int n = str.size();
            res+= to_string(n) + "/"+str;
        }

        return res;
    }

    vector<string> decode(string &str) {
        vector<string> res;
        int i = 0;
        while(i < str.size()){
            //找到每次/出現的位置 一個/ 對應一個字串
            int found = str.find("/",i);
            int len = stoi(s.substr(i,found-i));
            string temp = s.substr(found+1,len);
            res.push_back(temp);
            i = found+1+len;
        }
        return res;
    }
};
