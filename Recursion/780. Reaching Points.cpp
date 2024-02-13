/*
780. Reaching Points
*/

// TC:O(log(max(tx, ty))) SC: O(log(max(tx, ty)))
class Solution {
public:
    bool reachingPoints(int sx, int sy, int tx, int ty) {
        if(sx == tx && sy == ty) return true;
        else if(sx > tx || sy > ty) return false;
        else if(sx == tx){
            if((ty-sy) % sx == 0) return true;
            else return false;
        }
        else if(sy == ty){
            if((tx-sx) % sy == 0) return true;
            else return false;
        }

        if(tx > ty) return reachingPoints(sx,sy, tx%ty,ty);
        else if(tx == ty) return false;
        else {
            return reachingPoints(sx,sy, tx,ty%tx);
        }
    }
};

/*
給你指定兩個座標(sx,sy) (tx,ty)
問說能否藉由 (x,y+x) (x+y,y) 這種操作達到tx, ty 
第一個想法是BFS 還可以順便求最少操作次數 但是這題坐標到 10^9次方 BFS大概率會超時
在仔細觀察 會發現數字肯定是遞增向上的 並且每次操作的時候加法的那項都會超過另一項 
所以這意味著我們可以從結果往回推 判斷上次操作的狀況是哪種 一直推到tx == sx && ty == sy 的狀況就會是正解
如果其他狀況的話就要在判斷一下
*/
