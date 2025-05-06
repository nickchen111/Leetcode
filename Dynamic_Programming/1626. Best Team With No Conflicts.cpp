// 排序+DP TC:O(n^2 + nlgn) SC:O(n)
class Solution {
public:
    int bestTeamScore(vector<int>& scores, vector<int>& ages) {
        int n = scores.size();
        vector<pair<int,int>> player;
        for(int i = 0; i < n; i++) {
            player.emplace_back(scores[i], ages[i]);
        }
        ranges::sort(player);  // 先按照分數小到大 在按照年齡小到大
        vector<int> dp(n);
        for(int i = 0; i < n; i++) {
            for(int j = 0; j < i; j++) {
                if(player[j].second <= player[i].second) {
                    dp[i] = max(dp[i], dp[j]);
                }
            }
            dp[i] += player[i].first;
        }
        return *max_element(dp.begin(), dp.end());
    }
};

// 排序+ 按照值域 TC:O(n*U+ nlgn) U = 年齡最大值 SC:O(n)
class Solution {
public:
    int bestTeamScore(vector<int>& scores, vector<int>& ages) {
        int n = scores.size();
        vector<pair<int,int>> player;
        for(int i = 0; i < n; i++) {
            player.emplace_back(scores[i], ages[i]);
        }
        ranges::sort(player); // 分數低到高
        int mx = *max_element(ages.begin(), ages.end());
        vector<int> max_sum(mx+1); // 枚舉每個年齡當作最大會有的最大值
        for(auto &[score, age] : player) {
            max_sum[age] = *max_element(max_sum.begin(), max_sum.begin() + age + 1) + score;
        }
        return *max_element(max_sum.begin(), max_sum.end());
    }
};

// BIT TC:O(nlgU + nlgn) U為年齡最大值 SC:(n + U)
template<typename T>
class FenwickTree {
    vector<T> tree;
public:
    // 使用下標 1 到 n
    FenwickTree(int n) : tree(n + 1) {}

    // a[i] 增加 val
    // 1 <= i <= n
    // 時間複雜度 O(log n)
    void update(int i, T val) {
        for (; i < tree.size(); i += i & -i) {
            tree[i] = max(tree[i], val);
        }
    }

    // 求前缀和 a[1] + ... + a[i]
    // 1 <= i <= n
    // 時間複雜度 O(log n)
    T pre(int i) const {
        T res = 0;
        for (; i > 0; i &= i - 1) {
            res = max(res, tree[i]);
        }
        return res;
    }

    // 求區間和 a[l] + ... + a[r]
    // 1 <= l <= r <= n
    // 時間複雜度 O(log n)
    T query(int l, int r) const {
        if (r < l) {
            return 0;
        }
        return pre(r) - pre(l - 1);
    }
};
class Solution {
public:
    int bestTeamScore(vector<int>& scores, vector<int>& ages) {
        /*
        方法1:
        n = m = 1000
        age <= 1000
        當前的一定選 那我就要去找我之前跟我一樣大或者比我小可以組成的最大總和是多少
        會想到前面如果有一個有序樹組 可以 n ^ 2 去找到前面以某個點當作結束員工的最大值
        方法2:
        BIT, 因為你是在找當前不超過目前這個球員的年紀的前面最大總和是多少這可以用BIT去維護
        然後將目前這個員工加進去 會是nlgn
        */
        int n = ages.size();
        vector<pair<int, int>> players(n);
        for (int i = 0; i < n; i++) {
            players[i] = {scores[i], ages[i]};
        }
        sort(players.begin(), players.end());
        int mxAge = *max_element(ages.begin(), ages.end());
        FenwickTree<int> bit(mxAge);
        for (int i = 0; i < n; i++) {
            int age = players[i].second, score = players[i].first;
            bit.update(age, bit.pre(age) + score);
        }
        return bit.pre(mxAge);
        /*
        DP
        vector<int> dp(mxAge + 1);
        int ans = 0;
        for (int i = 0; i < n; i++) {
            int age = players[i].second, score = players[i].first;
            for (int j = age; j >= 1; j--) {
                dp[age] = max(dp[age], dp[j] + score);
            }
            ans = max(ans,dp[age]);
        }
        return ans;
        */
    }
};
