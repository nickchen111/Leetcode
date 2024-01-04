/*
2870. Minimum Number of Operations to Make Array Empty
*/

// TC:O(n) SC:O(n)
class Solution {
public:
    int minOperations(vector<int>& nums) {
        int n = nums.size();
        unordered_map<int, int> map; // val -> freq;
        for(auto &x : nums){
            map[x] += 1;
        }

        int res = 0;
    
        for(auto &x : map){
            if(x.second % 3 == 0){
                res += x.second/3;
            }
            //如果消除奇數能讓他被整除
            else if(x.second >= 3 && x.second % 3  == 2){
                res += (x.second/3) + 1;
            }
            else if(x.second >= 3 && x.second % 3  == 1){
                res += (x.second/3-1) + 2;
            }

            else if(x.second % 2 == 0) res += x.second/2;
            
            else return -1; 
        }
        

        return res;
    }
};

/*
可以一次刪三個相同數字 或者一次刪兩個相同數字 問最少需要幾次操作刪除所有元素
如果無法返回-1
很直觀的會想讓3除可以得到最少的次數 如果3無法處理 那麼3最多可以處理幾次? ex : 7 -> 1次 變4 11 -> 3次變 2
也就是說如果除3餘數2 那就是整除結果+1 如果除3餘數變成1 那就是整除減一 + 2
3 -> 1
4-> 2
5 -> 1 + 1
6 -> 2
7 -> 2 + 1 - > 2個2 1個3
13 -> 3*3 + 4
11 -> 3*3 + 2
10 -> 3
*/
