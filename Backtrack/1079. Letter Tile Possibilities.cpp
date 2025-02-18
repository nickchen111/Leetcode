/*
1079. Letter Tile Possibilities
*/

// 利用字母特性做組合 排列自己算: TC:O(n * 2^n) SC:O(n)
class Solution {
public:
    int numTilePossibilities(string tiles) {
        unordered_map<char,int> mp;
        for(auto &ch : tiles) mp[ch] += 1;
        auto dfs = [&](auto &&dfs) -> int{
            int total = 0;
            for(auto &[ch, freq] : mp) {
                if(freq != 0) {
                    freq -= 1;
                    total += 1 + dfs(dfs);
                    freq += 1;
                }
            }
            return total;
        };
        return dfs(dfs);
    }
};

// 直接backtrack: TC:O(n * n!) SC:O(n!) 
class Solution {
public:
    int numTilePossibilities(string tiles) {
        int n = tiles.size();
        unordered_set<string> set;
        auto backtrack = [&](auto &&backtrack, int state, int i, string& s) -> void {
            set.insert(s);
            if(i == n) {
                return;
            }
            for(int j = 0; j < n; j++) {
                if(((state >> j) & 1) == 0) {
                    s.push_back(tiles[j]);
                    backtrack(backtrack, state | (1 << j), i + 1, s);
                    s.pop_back();
                } 
            }
        };
        string s;
        backtrack(backtrack, 0, 0, s);
        return (int)set.size() - 1;
    }
};

/*
給你一堆磁磚 上面有寫大寫字母 問說有多少種不同的字可以拼出
n = 7 -> backtrack 用set去重 列舉所有可能
*/
