/*
738. Monotone Increasing Digits
*/


// TC:O(n^2) SC:O(n) n = 10
class Solution {
public:
    int monotoneIncreasingDigits(int n) {
        
        string str = to_string(n);
        int m = str.size();
        string res;
        for(int i = m-1; i >= 1; i--){
            if(str[i] < str[i-1]){
                res.clear();
                for(int j = 0; j < m-i; j++){
                    res.push_back('9');
                }
                str[i-1] = str[i-1] - '1' + '0';
            }
            else res = str[i] + res;
        }
        
        if(str[0] != '0') res = str[0] + res;
        if(res.empty()) return n;
        
        return stoi(res);
        
    }
}; 
/*
這題希望你構建出一個比給你的數字n小於等於的滿足某個條件的最大值 並且這個最大值 從左到右邊的數字要是非遞減的 ex : 1223455567 
我覺得容易想到的突破點是倒過來從右邊到左邊 想要維護一個非遞增的數列  一旦遞增了 那麼後頭的數字就都貪心的改成9 然後當前較大的那個數字減一 就繼續往前看
最後不會加入最左邊的數字 如果他不是1就把他加入答案 並且確定一下給的數字n不是個位數 如果是個位數答案就是他本身 最後return res
*/
