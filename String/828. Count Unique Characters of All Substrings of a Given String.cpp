/*
828. Count Unique Characters of All Substrings of a Given String
*/

// TC:O(n) SC:O(26*k) k 為平均位置的數量
class Solution {
public:
    int uniqueLetterString(string s) {
        //先計算每個字母的位置
        int n = s.size();
        vector<vector<int>> pos(26);
        //每個字母怕只出現一次所以頭尾都要添加虛擬位置
        for(int i=0; i<26; i++){
            pos[i].push_back(-1);
        }
        for(int i=0; i<n; i++){
            pos[s[i]-'A'].push_back(i);
        }
        for(int i = 0; i<26; i++){
            pos[i].push_back(n);
        }

        int res = 0;
        //遍歷不是從s頭到s尾 這樣很難做 而是按照字母遍歷
        for(int k = 0; k<26; k++){
            for(int i = 1; i<pos[k].size()-1; i++){
                res+= (pos[k][i]-pos[k][i-1])*(pos[k][i+1]-pos[k][i]);
            }
        }

        return res;
    }
};

/*
此題n^2解就是枚舉所有substring 每次都去計算他的種類就會是他的得分
n線性解 看每個元素可以貢獻給多少個substring 
此題也屬於count subarray by element類型 但是是用string做 string最快查找位置的方式還是用vector容器去裝各個字母的位置
C | X X X C  X C X X X C X X | C
-1.       i.   j.      k       n

(j-i)*(k-j)
*/
