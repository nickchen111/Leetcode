// TC:O(nlgn) SC:O(n)
class Solution {
    using ll = long long;
public:
    long long putMarbles(vector<int>& weights, int k) {
        /*
        問說必須分成k組 最大分組方式 跟最小的差 並且看起來是要分完
        dp[i][j] 分了i組 走到j 會是
        max(dp[i-1][j-1] + cost[j], dp[i-1][j-2] + cost[j-1][j], .... )
        這樣寫會是n * n * k 就算能去掉 j 變數 還是太大了
        必須想想貪心
        可以想見 如果想選三個數字那麼代價會是犧牲中間的數字 這樣不划算 所以區間其實就是不超過2的區間
        這些選大小即可
        並且需要觀察出 因為一定要涵蓋整段區間 所以頭尾兩個一定要選
        */
        vector<ll> arr;
        int n = weights.size();
        for(int i = 0; i < n - 1; i++) {
            arr.emplace_back(weights[i] + weights[i+1]);
        }
        ranges::sort(arr);
        ll mx = 0;
        ll mn = 0;
        for(int i = 0; i < k - 1; i++) {
            mn += arr[i];
            mx += arr[arr.size() - i - 1];
        }
        return mx - mn;
    }
};
