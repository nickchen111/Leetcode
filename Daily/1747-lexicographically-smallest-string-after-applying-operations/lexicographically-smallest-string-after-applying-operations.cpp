class Solution {
public:
    string findLexSmallestString(string s, int a, int b) {
        queue<string> q;
        q.push(s);
        string ans = s;
        unordered_set<string> visited;
        while (!q.empty()) {
            string cur = q.front();
            q.pop();
            if (visited.count(cur)) continue;
            visited.insert(cur);
            ans = min(ans, cur);
            // 執行兩個操作
            string nxt = cur;
            for (int i = 1; i < cur.size(); i += 2) {
                int num = (cur[i] - '0' + a) % 10;
                nxt[i] = num + '0';
            }

            if (!visited.count(nxt)) q.push(nxt);
            string nxtt;
            for (int i = s.size() - b; i < s.size(); i++) {
                nxtt += cur[i];
            }
            for (int i = 0; i < s.size() - b; i++) {
                nxtt += cur[i];
            }
            if (!visited.count(nxtt)) q.push(nxtt);
        }

        return ans;
    }
};