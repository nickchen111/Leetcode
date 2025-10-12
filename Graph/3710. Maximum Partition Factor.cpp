// TC:O(n ^ 2 * logn) SC:O(n ^ 2)
class Solution {
public:
    int maxPartitionFactor(vector<vector<int>>& points) {
        int n = points.size();
        if (n == 2) return 0;
        unordered_set<int> st;
        for (int i = 0; i < n; i++) {
            for (int j = i + 1; j < n; j++) {
                st.insert(abs(points[i][0] - points[j][0]) + abs(points[i][1] - points[j][1]));
            }
        }

        vector<int> allDist(st.begin(), st.end());
        ranges::sort(allDist);

        auto check = [&](int mid) -> bool {
            vector<vector<int>> g(n);
            for (int i = 0; i < n; i++) {
                for (int j = i + 1; j < n; j++) {
                    if (abs(points[i][0] - points[j][0]) + abs(points[i][1] - points[j][1]) < allDist[mid]) {
                        g[i].emplace_back(j);
                        g[j].emplace_back(i); // 他們不能在同組 可用二分圖染色判定
                    }
                }
            }

            vector<int> color(n, -1);
            auto bfs = [&](int i) -> bool {
                queue<int> q;
                q.push(i);

                while (!q.empty()) {
                    int cur = q.front();
                    q.pop();

                    for (auto &nxt : g[cur]) {
                        if (color[nxt] == -1) {
                            color[nxt] = 1 - color[cur];
                            q.push(nxt);
                        } else if (color[nxt] == color[cur]) return false;
                    }
                }
                return true;
            };

            for (int i = 0; i < n; i++) {
                if (color[i] == -1) {
                   if(!bfs(i)) return false;
                }
            }

            return true;
        };

        int left = 0, right = allDist.size() - 1;
        while (left < right) {
            int mid = left + (right - left + 1) / 2;
            if (check(mid)) {
                left = mid;
            } else {
                right = mid - 1;
            }
        }

        return allDist[left];
    }
};
