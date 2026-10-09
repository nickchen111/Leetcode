class Solution {
public:
    int minInsertions(string s) {
        int n = s.size();
        int count = 0;
        int res = 0;
        for(int i = 0; i < n; i++){
           if(s[i] == '(') count += 1;
           else {
               if(i + 1 < n && s[i+1] == s[i]){
                   count--;
                   i++;
               }
               //補一個  ）
               else {
                   res += 1;
                   count --;
               }
           }

           if(count < 0){
               res += 1;
               count = 0;
           }
        }

        if(count > 0) res += count*2;

        return res;
    }
};

/*
一個 ( 對應兩個 ））
最少需插入多少讓他 Balance 
1. ) ( 
計算count ( 加上2 ))減一減一 遇到變成 0的時候 繼續走 直到 -2 可以加入一個左括弧 歸零他
如果最後count = -1 加上2 一左一右
2. 左括弧太多了 count > 0 res += count;
3. count = -1 ex :  ) ( 又突然有一個左括弧 res += 1; 歸零 開始
(  ) ( -> 5
*/