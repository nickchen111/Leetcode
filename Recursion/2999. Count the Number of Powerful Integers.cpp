/*
2999. Count the Number of Powerful Integers
*/

// TC:O(9*n) SC:O(n) n 最多50 from lg10^15
class Solution {
    using LL = long long;
public:
    long long numberOfPowerfulInt(long long start, long long finish, int limit, string s) {
        return helper(to_string(finish), limit, s) - helper(to_string(start-1), limit, s);
    }
    LL helper(string a, int limit, string s){
        if(a.size() < s.size()) return 0;

        return DFS(a,limit,s, 0, true);
    }
    // k代表看到第幾位數
    LL DFS(string a, int limit, string s, int k, bool same){

        if(a.size() - k == s.size()){
            //合法狀態就會是 最終沒有貼合 代表不會違法 or 貼合了但是我的上界原本的數字本身就大於等於string s
            if(!same || a.substr(k) >= s){
                return 1;
            }
            else return 0;
        }

        LL res = 0;
        if(!same){
            int d = a.size() - s.size() - k;
            res = pow(1+limit, d);
        }
        //貼合上界
        else {
            for(int i = 0; i <= min(limit, a[k]-'0'); i++){
                if(i > a[k]-'0') break;
                else if(i == a[k]-'0'){
                    res += DFS(a, limit, s, k+1, true);
                }
                else {
                    res += DFS(a, limit, s, k+1, false);
                }  
            }
        }

        return res;
        
    }
};

/*
此題希望你找出給定區間中 
滿足以下條件的字串總數
1 字串尾數是指定的字串
2.字串其他數字不能超過limit
首先因為他給了上界下界 所以用兩次遞歸的方式去做會比較方便只需考慮一個上界
再來考慮目前recursion的前綴是否貼合給的上限 這樣就分成兩種情況
1. 貼合 那麼我後續走的數字就只能是 min(a[k], limit) 取較小的 
2. 不貼合 那麼我後面的數字其實都可以在limit範圍內任意取 a.size()-s.size()-k個

x x x x x x 
n = 6 k = 3 s = 3
*/
