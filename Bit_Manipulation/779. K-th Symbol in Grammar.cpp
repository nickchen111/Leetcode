/*
779. K-th Symbol in Grammar
*/


// TC:O(n) SC:O(n)
class Solution {
public:
    int kthGrammar(int n, int k) {
        if (n == 1) return 0;
        int length = 1 << (n - 2); // ex: n == 4 0001<<2 1左移兩位 -> 0100 變成4代表他的上一層長度為4

        if (k <= length) return kthGrammar(n - 1, k);
        else return 1 - kthGrammar(n - 1, k - length);//補數操作
    }
};
/*
0
01
0110
01101001
0110100110010110
*/
