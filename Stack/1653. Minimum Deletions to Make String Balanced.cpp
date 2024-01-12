/*
1653. Minimum Deletions to Make String Balanced
*/

// Stack TC:O(n) SC:O(n) 
class Solution {
public:
    int minimumDeletions(string s) {
        int n = s.size();

        int res = 0;
        stack<char> stack;
        for(int i = 0; i < n; i++){
            if(s[i] == 'b'){
                stack.push('b');
            }
            else {
                if(!stack.empty()){
                    res += 1;
                    stack.pop();
                }
            }
        }

        return res;
    }
};

// Two pass TC:O(n) SC:O(n) 
class Solution {
public:
    int minimumDeletions(string s) {
        int n = s.size();

        int res = INT_MAX;
        vector<int> countB(n);
        vector<int> countA(n);
        int count = 0;
        for(int i = n-1; i >= 0; i--){
            countA[i] = count;
            if(s[i] == 'a') count += 1;
        }
        count = 0;
        for(int i = 0; i < n; i++){
            countB[i] = count;
            res = min(res, countA[i] + countB[i]);
            if(s[i] == 'b') count += 1;
        }
        
        return res;
    }
};

/*
給你一串字串裡面只有 a b
問最少要刪掉幾個字能讓這個字不會有ba相鄰
應該是用stack處理
aabaaaaaaa
不能有ba
1. 如果遇到b就加入棧 判斷一下是後面的a多還是當前的b多來決定要刪除哪個
2. 如果棧非空 無條件先捨去一個b 答案+1 這樣的好處是 我刪到後面如果每一段都剩下一些b那麼他最後會累加成更長的b 這種情況 就變成是刪除後面的a
ex: "baababbaabbaaabaa"bbabbbabaaaaaa"baabababaaababbb"
3. two pass 答案最終一定是長 aaabbb or aaaa 那麼我在每個分界點去紀錄 當下左邊有多少個b右邊有多少個a 就可以在遍歷一次判段最小值
*/
