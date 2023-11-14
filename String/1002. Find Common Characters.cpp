/*
1002. Find Common Characters
*/

// TC:O(26*n) SC:O(26*n) fast
class Solution {
public:
    vector<string> commonChars(vector<string>& words) {
        int n = words.size();
        //每個字元在每個字有多少個
        vector<vector<int>> freq(26,vector<int>(n));
        for(int i = 0; i<n; i++){
            for(auto ch:words[i]){
                freq[ch-'a'][i]+=1;
            }
        }

        vector<string> res;
        string str = "";
        for(int i =0; i<26; i++){
           int count = *min_element(freq[i].begin(),freq[i].end());
           for(int k =0; k<count; k++){
               str = i+'a';
               res.push_back(str);
           }
        }

        return res;
    }
};

// TC:O(n*k+26*n) n為字串數量 ｋ為字串的字元平均數量 SC:O(26*n) slow
class Solution {
public:
    vector<string> commonChars(vector<string>& words) {
        int n = words.size();
        //每個字的每個字元有多少個
        unordered_map<string,vector<int>> Table;
        for(auto word:words){
            Table[word] = vector<int>(26,0);
            for(auto ch:word){
                Table[word][ch-'a']+=1;
            }
        }

        vector<string> res;
        for(int i =0; i<26; i++){
            int minCount = INT_MAX;
            for(auto word:words){
                if(Table[word][i] < minCount){
                    minCount = Table[word][i];
                }
            }
            char c = i+'a';
            string str; str.push_back(c); 
            for(int i =0; i<minCount; i++){
                res.push_back(str);
            }
        }

        return res;
    }
};
