/*
1387. Sort Integers by The Power Value
*/

// TC:O(n*k) SC:O(n)
class Solution {
    unordered_map<int,int> memo;// val -> times for memorization
    int solve(int n){
        int num = n;
        if(num == 1) return 0;
        int step = 0;
        while(num != 1){
            if(memo.find(num) != memo.end()) return step+memo[num];
            if(num % 2 == 0){
                num/=2;
            }
            else {
                num = 3*num + 1;
            }
            step++;
        }
        memo[num] = step;
        return step;
    }
public:
    int getKth(int lo, int hi, int k) {
        set<pair<int,int>> set; // times -> val for heap
        
        for(int i = lo; i <= hi; i++){
            int step = solve(i);
            set.insert({step,i});
            while(set.size() > k) set.erase(--set.end());
        }
        

        return (set.rbegin()->second);
    }
};

/*
此題定義了一個power代表一個數經過多少步驟能夠變成1 
然後給你一段區間 問說這段區間變成1的步驟次數排序後 第k個為多少
某個數走到1的次數肯定是固定的 可以用記憶化的方式把此步驟記起來 -> map key:數字 val->次數
*/
