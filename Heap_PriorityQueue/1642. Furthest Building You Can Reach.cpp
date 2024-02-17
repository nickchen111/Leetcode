/*
1642. Furthest Building You Can Reach
*/

// TC:O(nlgn) SC:O(n)
class Solution {
    using LL = long long;
public:
    int furthestBuilding(vector<int>& heights, int bricks, int ladders) {
        int n = heights.size();
        int count = ladders;
        priority_queue<int, vector<int>, greater<int>> pq;
        LL sum = 0;
        bool flag = 0;
        int res = 0;
        for(int i = 1; i < n; i++){
            if(heights[i] > heights[i-1] && count > 0){
                count -= 1;
                pq.push(heights[i] - heights[i-1]);
                res = max(res, i);
            }
            else if(heights[i] > heights[i-1] && count == 0){
                pq.push(heights[i] - heights[i-1]);
                if(!pq.empty() && sum + pq.top() <= bricks){
                    sum += pq.top();
                    res = max(res, i);
                } 
                else if(!pq.empty() && sum + pq.top() > bricks){
                    flag = 1;
                    break;
                }
                if(!pq.empty()) pq.pop();
            }
            else if(heights[i] <= heights[i-1]){
                res = max(res, i);
            }

            if(flag) break;
        }

        
        return res;

    }
};


/*
此題說從最左邊開始走走到右邊 遇到一樣高或比較矮的可以直接走過去 但如果遇到比較高的
樣用磚頭或者單純一個梯子過去 問說最遠可以走到哪個index
最佳策略會想要盡量將磚頭花完 所以維護一個單調遞減序列
[4,2,7,6,9,14,12] -> 5, 3, 5 這題就轉化為 有ladders次扣打 問說加總總和小於等於 bricks的最長長度為多少
我會想到用presum紀錄 然後 presum[i] - bricks 這些會是我沒辦法單純用bricks的數量 然後看前面那段是否小於等於ladders長度 就代表可以走到
但會很難judge 如果 bricks很小 然後前面都可以通過突然遇到一個超高的 這時用柱子最好 high - low 去 lower-bound這個還是很高
會找到當下的index 往前推一個踢子數量可能不夠 不是最佳貪心策略
所以要想說都先用踢子 如果不夠了再把先前最矮的用磚頭 一直這樣走到磚頭不夠
或者反過來想 都先用磚頭 如果超過上限了 那麼我們再派出踢子 直到題子不夠用並且是超過上限時
*/
