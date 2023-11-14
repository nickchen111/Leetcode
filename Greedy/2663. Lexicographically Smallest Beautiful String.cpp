/*
2663. Lexicographically Smallest Beautiful String
*/

/*
此題可以在任意位上變更其字元 但是只有k種選擇從4~26 並且更新後的字串不能是回文串 也就是說 更新的字元 不能跟前面還有前前面相等
此題的精華在於要去釐清回文串的定義 回文串就像是一大串包一小串 如果小串的非回文 那麼大串也不可能是回文了 所以只需檢查len= 2 & 3
*/

// TC:O(n*k) SC:O(1)
class Solution {
public:
    string smallestBeautifulString(string s, int k) {
        //此題跟你說可以在任意位上變更其字元 但是只有k種選擇從4~26 並且更新後的字串不能是回文串 也就是說 更新的字元 不能跟前面還有前前面相等
        string original = s;
        int n = s.size();
        bool flag = 0;
        for(int i = n-1; i>=0; i--){
            //對每個字加一 看是否可以符合題目字元更改範圍
            for(char ch = s[i]+1; ch<'a'+k; ch++){
                if(!checkOk(s,i,ch)) continue;
                s[i] = ch;

                for(int j = i+1; j<n; j++){
                    //合法的字後面的字可以從a開始替換
                    for(char c = 'a'; c<'a'+k; c++){
                        if(checkOk(s,j,c)){
                            s[j] = c;
                            break;
                        }
                    }
                }
                flag = 1;
                break;
            }
            if(flag) break;
        }
        //已經換無可換沒有更好的可以替換之後變得更大
        if(s == original) return "";
        return s;
    }

    bool checkOk(string& s, int i, char ch){
        if(i-1>=0 && ch == s[i-1]) return false;
        if(i-2>=0 && ch == s[i-2]) return false;
        return true;
    }
};
