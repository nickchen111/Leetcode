/*
638. Shopping Offers
*/

// TC:O(2^n) SC:O(2^24)
class Solution {
    int n;
    int memo[1<<24];
public:
    int shoppingOffers(vector<int>& price, vector<vector<int>>& special, vector<int>& needs) {
        vector<vector<int>> specials;
        n = price.size();
        for(int i=0; i < special.size(); i++){
            int sum = 0;
            for(int j = 0; j < n; j++){
                sum+=special[i][j]*price[j];
            }
            if(sum > special[i].back()){
                specials.push_back(special[i]);
            }
        }

        int state = 0;
        for(int i = 0; i<n; i++){
            state += (needs[i]<<(i*4));
        }
        return DFS(state,specials,price);
    }

    int DFS(int state, vector<vector<int>>& specials, vector<int>& price){
        if(state == 0) return 0;
        if(memo[state] != 0) return memo[state];

        int res = 0;
        for(int i = 0; i<n; i++){
            res += (state>>(i*4))%16 * price[i];
        }

        //先判斷combo能不能用
        for(auto &comb:specials){
            int flag = 1;
            for(int i = 0; i<n; i++){
                if(((state>>(i*4))%16) < comb[i]){
                    flag = 0;
                    break;
                }
            }

            if(flag == 0) continue;

            //可以用的話 
            int state2 = state;
            for(int i = 0; i<n; i++){
                state2 -= (comb[i]* (1<<(i*4)));
            }

            res = min(res, comb[n] + DFS(state2,specials,price));
        }
        memo[state] = res;

        return res;
    }
};

/*
此題是NP問題 沒有特別優秀的解法
但是有一個地方可以縮短判斷每個物品購買數量 也就是類似將一堆數字轉成二進位碼的狀態壓縮
很像用map映射 
另外就是DFS過程中的記憶化了可以快速縮短時間 並且這題有個小陷阱 組合包不一定是最好的
此外 這題的bit操作也很值得學習 %8 or % 16這種就是可以只取出某段bit最尾巴的三位或者4位
*/
