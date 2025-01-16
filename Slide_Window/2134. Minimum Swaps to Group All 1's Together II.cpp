/*
2134. Minimum Swaps to Group All 1's Together II
*/

// 2025.01.16
class Solution {
public:
    int minSwaps(vector<int>& nums) {
        int cnt1 = 0;
        for(auto &num : nums)  cnt1 += num;
        if(cnt1 == 0) return 0;
        int n = nums.size();
        for(int i = 0; i < n; i++) {
            if(i < cnt1-1) {
                nums.push_back(nums[i]);
            }
        }
        n = nums.size();
        int i = 0;
        int res = INT_MAX;
        int sum = 0;
        for(int j = 0; j < n; j++) {
            //入
            sum += (nums[j] == 1);
            // 出
            if(j - i + 1 == cnt1) {
                res = min(res, cnt1 - sum);
                sum -= (nums[i] == 1);
                i++;
            }
        }

        return res;
    }
};

// TC:O(n) SC:O(1)
class Solution {
public:
    int minSwaps(vector<int>& nums) {
        int n =  nums.size();
        int count1 = 0;
        for(int i = 0 ; i < n; i++){
            if(nums[i] == 1) count1 += 1;
        }

        if(count1 <= 1) return 0;

        // make a circular array
        for(int i = 0; i < count1-1; i++){
            nums.push_back(nums[i]);
        }
        n = nums.size();

        // ex: len: 7~9 count1 = 3 , only need to from original index 6 to 8
        // 9 - 3 = 6
        // i means index 
        int count0 = 0;
        int j = 0;
        int res = INT_MAX;
        for(int i = 0; i <= n - count1; i++){
            while(j-i < count1){
                if(nums[j] == 0) count0 += 1;
                j++;
            }
            if(j-i == count1)
                res = min(res, count0);
            if(nums[i] == 0) count0 -= 1;
        }

        return res;
    }
};

/*
可以任意移動兩點的位置 給你一個circular array
要移動最少多少次讓裡面的1全部相鄰
[0,1,0,1,1,0,0]
[0 1 0 0 0 1 1 0 0 1 1 0 0 1 0 0 1 1 1 0 0] -> 4
主要的想法是我們要將1全部移動到一起 那麼最終結果勢必就是這個長度
那麼固定這個長度滑窗判斷當下區間有多少個0那就是如果要達成在這個區間都是1的狀況下所要移動的次數 
為了加入circular aray的考慮 我打算將數組補他可能所需個數 取決於1有幾個

Thinking: 要想到這點還是要考慮到 如果我想盡量減少swap那麼有某一串連續的1很長的 我會希望盡量往他靠攏 那麼他會形成的數組就有可能是
以他為周圍可以涵蓋到他一開始的1與最後的1的區間 至於怎麼移比較好就判斷在這些可能區間中哪個區間的1最多 相對來說我需要移動的次數就會
是最少
*/
