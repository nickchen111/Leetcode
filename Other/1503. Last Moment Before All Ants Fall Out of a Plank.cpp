/*
1503. Last Moment Before All Ants Fall Out of a Plank
*/


//TC:O(mlgm+nlgn) SC:O(1)
class Solution {
public:
    int getLastMoment(int n, vector<int>& left, vector<int>& right) {
        //往左走的會去找往右走比他小的格子上的 
        //往右走的會找往左走的比他剛好大一點的 兩個相遇相消
        //但這題仔細分析 相撞其實就是把任務交棒
        sort(left.begin(),left.end());
        sort(right.begin(),right.end());
        int t1 = (left.size() == 0) ? 0:left.back()-0;
        int t2 = (right.size() == 0) ? 0:n - right[0];

        return max(t1,t2);
    }
};

/*
x x x x x x x x 
      o o
*/
