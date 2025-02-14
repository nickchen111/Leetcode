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

// 線段樹 TC:O(nlgU + nlgn) U為年齡最大值 SC:(n + U)
class Solution {
    static constexpr int MX = 1000;
    int t[MX + 1];

    // 返回 max(max_sum[:i+1])
    int query(int i) {
        int mx = 0;
        for (; i; i &= i - 1)
            mx = max(mx, t[i]);
        return mx;
    }

    void update(int i, int mx) {
        for (; i <= MX; i += i & -i)
            t[i] = max(t[i], mx);
    }

public:
    int bestTeamScore(vector<int> &scores, vector<int> &ages) {
        int n = scores.size();
        vector<pair<int,int>> player;
        for(int i = 0; i < n; i++) {
            player.emplace_back(scores[i], ages[i]);
        }
        ranges::sort(player);  // 先按照分數小到大 在按照年齡小到大

        for (auto &[score, age] : a)
            update(age, query(age) + score);
        return query(MX);
    }
};
