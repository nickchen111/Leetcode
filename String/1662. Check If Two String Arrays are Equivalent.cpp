/*
1662. Check If Two String Arrays are Equivalent
*/

// 暴力解取字元 TC:O(n*k) SC:O(n*k)
class Solution {
public:
    bool arrayStringsAreEqual(vector<string>& word1, vector<string>& word2) {
        string str1,str2;
        for(auto word:word1){
            for(auto ch:word){
                str1+=ch;
            }
        }
        for(auto word:word2){
            for(auto ch:word){
                str2+=ch;
            }
        }

        return str1 == str2;
    }
};

//技巧性取 中間有問題就會暫停
class Solution {
public:
    bool arrayStringsAreEqual(vector<string>& word1, vector<string>& word2) {
        int wordIdx1 = 0, wordIdx2 = 0, chIdx1 = 0, chIdx2 = 0;
        
        while(1){
            char ch1 = word1[wordIdx1][chIdx1];
            char ch2 = word2[wordIdx2][chIdx2];
            if(ch1 != ch2) return false;

            chIdx1++; chIdx2++;

            if(chIdx1 == word1[wordIdx1].size()){
                wordIdx1++;
                chIdx1 = 0;
            }
            if(chIdx2 == word2[wordIdx2].size()){
                wordIdx2++;
                chIdx2 = 0;
            }

            if(wordIdx1 == word1.size() && wordIdx2 == word2.size()) break;
            if(wordIdx1 == word1.size() || wordIdx2 == word2.size()) return false;
        }

        return true;
    }
};

// 最佳解無腦取字串TC:O(n) SC:O(n*k)
class Solution {
public:
    bool arrayStringsAreEqual(vector<string>& word1, vector<string>& word2) {
        string s1 = "";
        string s2 = "";

        for(const string& s : word1)
            s1 += s;
        for(const string& s : word2)
            s2 += s;

        return s1==s2;
    }
};
