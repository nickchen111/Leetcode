/*
2957. Remove Adjacent Almost-Equal Characters
*/

// TC:O(n) SC:O(1)
class Solution {
public:
    int removeAlmostEqualCharacters(string word) {
        int n = word.size();
        int count = 0;
        for(int i = 1; i < n; i++){
            if(word[i] == word[i-1] || abs(word[i] - word[i-1]) == 1){
                count++;
                word[i] = '#';
            }
        }
        
        
        return count;
    }
};

/*
此題限制
1. 前後如果兩個字母一樣  a == b 
2. 前後兩個字母在字母表是在隔壁 abs((i+1) -i) == 1
a != b && abs(word[i] - word[i-1] != 1) 
一開始用DP想 太費腦了 改了一個他前前一個會受影響 改後一個又不好說後後一個原本跟他好好的因為這次改動產生了影響 DP狀態轉移感覺可寫但燒腦
最後姑且相信每當遇到不滿足時我就改後一個並且 稍微思考了幾個例子感覺到他一定能找的一個可以顧前顧後的字母 所以都將他設為 # 不與任何人相同 

DP草稿想法：
dp[i][a~z]截至i的長度 結尾是 a~z 並且合法的所需替換的最小次數    
那就要換掉 問最少操作次數
"acddez" -> "ybdoez" 
兩個字母一樣時 -> 要換哪個 -> 從 i 跟 i-2 之間判斷 i > i - 2 換到i後面兩個 if i < i-2 換到 i後面兩個
*/
