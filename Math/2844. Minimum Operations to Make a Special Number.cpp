/*
2844. Minimum Operations to Make a Special Number
*/


// TC:O(n^2) SC:O(1)
class Solution {
public:
    int minimumOperations(string s) {
        int n = s.size();
        int res = INT_MAX;

        for(int i = n-1; i >= 0; i--){
            if(s[i] == '0'){
                bool flag = 1;
                for(int j = i-1; j >= 0; j--){
                    if(s[j] == '5' || s[j] == '0'){
                        res = min(res,n - 1 - i + i - j - 1);
                        flag = 0;
                        break;
                    }
                }
                if(flag) {
                    res = min(res, n - 1);
                }
            }
            else if(s[i] == '5'){
                 for(int j = i-1; j >= 0; j--){
                    if(s[j] == '2' || s[j] == '7'){
                        res = min(res,n - 1 - i + i - j - 1);
                        break;
                    }
                }
            }
        }

        return res == INT_MAX ? n : res;
    }
};

/*
問說一串字串裡面的數字要怎麼刪除最少的量能讓他被25整除
能被25整除的數尾數會是
25 
00
75
50
0 -> 5 or 0 
5 -> 2. or 7
要怎麼刪除最少的數達到當前這四種可能
x x x x j x x i x x n
*/
