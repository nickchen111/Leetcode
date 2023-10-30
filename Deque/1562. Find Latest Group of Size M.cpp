/*
1562. Find Latest Group of Size M
*/


// Deque TC:O(n) SC:O(n)
class Solution {
public:
    int findLatestStep(vector<int>& arr, int m) {
        int n = arr.size();
        if(n == m) return n;//只有一天的狀況
        arr.insert(arr.begin(),0);
        vector<int> day(n+1);
        for(int i =1; i<=n; i++){
            day[arr[i]] = i;
        }

        //開始判斷是否有符合條件的窗口
        deque<int> dq;
        int res = -1;
        for(int i = 1; i<=n; i++){
            //老去
            while(!dq.empty() && i-dq.front() >= m){
                dq.pop_front();
            }
            //被後面大數淘汰
            while(!dq.empty() && day[dq.back()] < day[i]){
                dq.pop_back();
            }
            dq.push_back(i);

            if(i < m) continue;
            
            int t = day[dq.front()];
            int left = INT_MAX; int right = INT_MAX;
            if(i-m>=1) left = day[i-m];
            if(i+1 <=n) right = day[i+1];

            if(left > t && right > t){
                res = max(res, min(left,right)-1);
            }
        }

        return res;
    }
};

/*
此題也是要從題目來理解到每次都需要去找區間裡的最晚的那次翻牌 然後比較前後是否都比他還晚翻 才能去確定是否可以更新答案
arr[i] = x i代表他翻的那個index x代表他第幾天翻的
day[i] = x 反過來表示 更好懂

t:the earlist day when the interval become all one
[i:j] 這個滑窗符合 m的大小之間 i-1跟j+1翻牌的天數會大於[i:j]翻牌的天數

...i-m[i-m+1, i]i+1...
*/
