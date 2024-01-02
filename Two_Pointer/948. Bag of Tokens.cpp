/*
948. Bag of Tokens
*/


// TC:O(n) SC:O(1)
class Solution {
public:
    int bagOfTokensScore(vector<int>& tokens, int power) {
        int n = tokens.size();
        if(n == 0) return 0;
        sort(tokens.begin(), tokens.end());

        int score = 0;
        if(tokens[0] > power) return 0;
        int res = 0;
        int j = n - 1;
        int i = 0;
        while(i <= j){
            if(power >= tokens[i]){
                score += 1;
                power -= tokens[i];
                i++;
            }
            else if(power < tokens[i]){
                if(j > i && score > 0){
                    score -= 1;
                    power += tokens[j];
                    j--;  
                }
                else break;
            }
            res = max(res, score);
        }

        return res;
    }
};

// TC:O(n) SC:O(n) 
class Solution {
public:
    int bagOfTokensScore(vector<int>& tokens, int power) {
        int n = tokens.size();
        if(n == 0) return 0;
        sort(tokens.begin(), tokens.end());

        int score = 0;
        if(tokens[0] > power) return 0;
        int res = 0;
        int j = n - 1;
        vector<int> visited(n);
        int i = 0;
        while(i <= j){
            if(visited[i]){
                i++;
                continue;
            }

            if(power >= tokens[i]){
                score += 1;
                power -= tokens[i];
                visited[i] = 1;
                i++;
            }
            else if(power < tokens[i]){
                if(visited[j] == 0 && score > 0){
                    score -= 1;
                    power += tokens[j];
                    visited[j] = 1;
                    j--;  
                }
            }
            res = max(res, score);
        }

        return res;
    }
};

/*
給你個初始值 並且分數從０ 開始
可以任意挑怪打的概念 每打掉一個救得一分 但是初始值會變小
但如果你至少有一分 你可以捨棄一分來獲得初始值提升某一個怪的分數
問說最多可以得幾分
首先會先選最小於自己的至少獲得一分 然後去換成較大的數字 如果這樣做划算的話 
貪心的想 肯定都是先取掉最小的分數
1.不論是將來想換大分數
2. 將來持續往後取
*/
