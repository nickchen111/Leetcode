/*
3387. Maximize Amount After Two Days of Conversions
*/

// TC:O(n1 + k*n2) k為會跑入回圈的從dfs來的點 SC:O(n1+n2)
class Solution {
public:
    double maxAmount(string initialCurrency, vector<vector<string>>& pairs1, vector<double>& rates1, vector<vector<string>>& pairs2, vector<double>& rates2) {
        unordered_map<string, double> map;
        map[initialCurrency] = 1.0;
        unordered_map<string, unordered_map<string, double>> day1;
        double res = 1.0;

        for (int i = 0; i < pairs1.size(); i++) {
            string s1 = pairs1[i][0], s2 = pairs1[i][1];
            day1[s1][s2] = rates1[i];
            day1[s2][s1] = 1.0 / rates1[i];
        }

        function<void(const string&)> dfs = [&](const string& s) {
            if (day1.find(s) != day1.end()) {
                for (const auto &[p, mon] : day1[s]) {
                    if (map[p] < mon * map[s]) {
                        double money = map[s];
                        map[p] = money * mon;
                        if(p == initialCurrency) res = max(res, map[p]);
                        dfs(p);
                    }
                }
            }
        };

        dfs(initialCurrency);

        unordered_map<string, unordered_map<string, double>> day2;
        for (int i = 0; i < pairs2.size(); i++) {
            string s1 = pairs2[i][0], s2 = pairs2[i][1];
            day2[s1][s2] = rates2[i];
            day2[s2][s1] = 1.0 / rates2[i];
        }

        function<void(const string&)> dfs2 = [&](const string& s) {
            if (day2.find(s) != day2.end()) {
                for (const auto &[p, mon] : day2[s]) {
                    if (map[p] < mon * map[s]) {
                        double money = map[s];
                        map[p] = money * mon;
                        if(p == initialCurrency) res = max(res, map[p]);
                        dfs2(p);
                    }
                }
            }
        };

        for (const auto &[p, mp] : map) {
            dfs2(p);
        }

        return res;
    }
};
