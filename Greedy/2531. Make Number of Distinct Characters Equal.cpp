/*
2531. Make Number of Distinct Characters Equal
*/

// 4/16
class Solution {
public:
    bool isItPossible(string word1, string word2) {
        int m = word1.size();
        int n = word2.size();
        vector<int> count1(26,0);
        vector<int> count2(26,0);
        int num1 = 0, num2 = 0;
        for(auto ch : word1){
            count1[ch-'a'] += 1;
            if(count1[ch-'a'] == 1) num1 += 1;
        }
        for(auto ch : word2){
            count2[ch-'a'] += 1;
            if(count2[ch-'a'] == 1) num2 += 1;
        }

        if(abs(num1 - num2) > 2) return false;

        for(int i = 0; i < 26; i++){
            if(count1[i] == 0) continue;
            for(int j = 0; j < 26; j++){
                if(count2[j] == 0) continue;
                int tmp1 = num1;
                int tmp2 = num2;
                if(i == j){
                    if(tmp1 == tmp2) return true;
                }
                else {
                    if(count1[i]-1 == 0) tmp1 -= 1;
                    if(count2[j]-1 == 0) tmp2 -= 1;
                    if(count1[j] == 0) tmp1 += 1;
                    if(count2[i] == 0) tmp2 += 1;
                    if(tmp1 == tmp2) return true;
                }
            }
        }

        return false;
    }
};


/*
能不能靠換一個字 讓兩邊的獨特元素數量相等
*/

// TC:O(26*26 + n+m) SC:O(52)
class Solution {
public:
    bool isItPossible(string word1, string word2) {
        int n = word1.size();
        int m = word2.size();
        
        vector<int> count1(26,0);
        vector<int> count2(26,0);
        int num1 = 0, num2 = 0;
        for(auto ch : word1){
            count1[ch-'a'] += 1;
            if(count1[ch-'a'] == 1) num1 += 1;
        }
        for(auto ch : word2){
            count2[ch-'a'] += 1;
            if(count2[ch-'a'] == 1) num2 += 1;
        }
        if(abs(num1 - num2) > 2) return false;
        
        for(int i = 0; i < 26; i++){
            int x = count1[i];
            if(x == 0) continue;
            
            for(int j = 0; j < 26; j++){
                int y = count2[j];
                if(y == 0) continue;
                auto temp1 = count1, temp2 = count2;
                int temp_num1 = num1, temp_num2 = num2;
                temp2[i] += 1;
                if(temp2[i] == 1) temp_num2+=1;
                temp2[j] -= 1;
                if(temp2[j] == 0) temp_num2 -= 1;
                
                temp1[i] -= 1;
                if(temp1[i] == 0) temp_num1 -= 1;
                temp1[j] += 1;
                if(temp1[j] == 1) temp_num1 += 1;
                if(temp_num1 == temp_num2) return true;
            
            }
        }

        return false;
    }
};

/*
此題考說是否能藉由交換兩個字串其中一個字 讓兩邊獨特字的數量相同
ex : abcc aab -> 3種 2種 -> 可以換過去一種字串一本來就有的字 abac acb 這樣大家都有三種 一邊是換自己有的但他是把自己重複的換掉 一邊是自己沒有的
*/
