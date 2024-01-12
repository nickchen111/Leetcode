/*
3001. Minimum Moves to Capture The Queen
*/

// TC:O(m*n) SC:O(1)
class Solution {
public:
    int minMovesToCaptureTheQueen(int a, int b, int c, int d, int e, int f) {
        int candidate1, candidate2;
        //第一個棋子狀況
        //三個都在同個row上
        if(a == c && c == e){
            if(d > b && d < f || d < b && d > f) candidate1 = 3;
            else candidate1 = 1;
        }
        else if(b == d && d == f){
            if(c > a && c < e || c < a && c > e) candidate1 = 3;
            else candidate1 = 1;
        }
        
        else if(a == e || b == f) candidate1 = 1;
        else candidate1 = 2;
        
        //才可能走到
        bool flag = 0;
        if(abs(c-e) == abs(d-f)){
            //兩個都要++
            while(c < e && d < f){
                c += 1;
                d ++;
                if(c == a && d == b) {
                    candidate2 = 3;
                    flag = 1;
                    break;
                }
            }
            while(c > e && d < f){
                c -= 1;
                d ++;
                if(c == a && d == b) {
                    candidate2 = 3;
                    flag = 1;
                    break;
                }
            }
            while(c > e && d > f){
                c -= 1;
                d -= 1;
                if(c == a && d == b) {
                    candidate2 = 3;
                    flag = 1;
                    break;
                }
            }
            while(c < e && d > f){
                c += 1;
                d -= 1;
                if(c == a && d == b) {
                    candidate2 = 3;
                    flag = 1;
                    break;
                }
            }
        }
        if(flag == 0 && abs(c-e) == abs(d-f)) candidate2 = 1;
        else if(c == e || d == f) candidate2 = 2;
        else candidate2 = INT_MAX;
        return min(candidate2, candidate1);
        
    }
};

/*
一個棋子 網上下左右
一個棋子只能對角線移動 
問最少走幾步兩個哪個可以最快走到queen
這題我對每個棋子都思考了三種狀況
直線棋:
1. 如果對角線跟終點都在同一個row or column上
->討論 1.1對角線是否擋到直線棋 是的話要走三步 1.2不是就只需走一步 
2.如果跟終點在同一路徑上且確定沒人擋我 直接走到底達陣 一步
3. 如果沒人擋我並且沒有任何row col與終點相同 走兩步達陣

對角線棋
1. 如果有可能走到終點的狀況 去判斷是否會有人擋 有人擋 答案就會是三步 or INT_MAX 但因為不管選哪個直線棋都會比較快 因此可以任意設
三步是在我最佳路徑上還有其他路可以選  或者我可能剛好在四個死角根本走不了
2. 如果我跟終點在同條row or col 就算直線棋有擋到我我也可以走另外一角 走兩步達陣
3. 如果完全沒人擋我 我可以直接走對角一步達陣

*/
