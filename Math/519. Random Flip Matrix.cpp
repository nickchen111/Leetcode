/*
519. Random Flip Matrix
*/

// TC:O(1) SC:O(m*n)
class Solution {
    int m,n;
    int count;
    unordered_map<int, int> map;//被選過的值去映射當前最後的值(此值有可能也映射了別的值)
public:
    Solution(int m, int n) {
        this->m = m;
        this->n = n;
        count = 0;
    }
    
    vector<int> flip() {
        int k = rand()%(m*n-count);// ex:2x3 只會有index 到 5 所以會是 0~5 正確
        count++;
        int res;
        //代表之前有被選過了
        if(map.find(k) != map.end()){
            res = map[k];
        }
        else res = k;

        if(map.find(m*n-count) != map.end()){
            map[k] = map[m*n-count];
        }
        else map[k] = m*n-count;

        return {res/n,res%n};
    }
    
    void reset() {
        map.clear();
        count = 0;
    }
};
/*
算是710的進階題 黑名單會更新== 
因此要想如何更新黑名單
用一個map 去替換當前的最後一個數字
因為每次flip過一次就將選擇-1
0. 1 2 3 {4} 5 6 7  4去跟7換
但有種情況要特別考慮
0 1 2 3 4 5 {6} 7 6跟7換
下一次在選:
0 1 2 {3} 4 5 6 選3 這時候不是無腦的跟6換
應該是map[k] =map[m*n-count];
*/
