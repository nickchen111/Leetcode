/*
1423. Maximum Points You Can Obtain from Cards
*/

// TC:O(n + k) SC:O(1)
class Solution {
public:
    int maxScore(vector<int>& cardPoints, int k) {
        int n = cardPoints.size();
        if(n == k) return accumulate(cardPoints.begin(), cardPoints.end(), 0);

        int res = 0;
        int sum = 0;
        for(int i = 0; i < k; i++){
            sum += cardPoints[i];
        }
        res = max(sum,res);

        int right = n - 1;
        int left = k - 1;
        while(left >= 0){
            sum -= cardPoints[left];
            sum += cardPoints[right];
            left--;
            right--;
            res = max(res, sum);
        }

        return res;
    }
};

/*
此題問每次拿牌可以從頭或者尾 可以獲得的最大分數為多少
模擬所有情況 從頭先拿k張 到底了再從尾巴開始拿 退掉上次拿到的最後一張
*/
