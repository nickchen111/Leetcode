/*
3394. Check if Grid can be Cut into Sections
*/

// TC:O(mlgm + nlgn) SC:O(m + n)
class Solution {
public:
    bool check(vector<pair<int, int>>& arr) {
        sort(arr.begin(), arr.end());
        int count = 0;
        int i = 0;
        while (i < arr.size()) {
            int end = arr[i].second;
            count++;
            int j = i + 1;
            while (j < arr.size() && arr[j].first < end) {
                end = max(end, arr[j].second);
                j++;
            }
            i = j;
        }

        return count >= 3;
    }

    bool checkValidCuts(int n, vector<vector<int>>& rectangles) {
        vector<pair<int, int>> allY;
        for (const auto& rect : rectangles) {
            allY.push_back({rect[1], rect[3]});  // starty, endy
        }

        if (check(allY)) return true;

        vector<pair<int, int>> allX;
        for (const auto& rect : rectangles) {
            allX.push_back({rect[0], rect[2]});  // startx, endx
        }

        if (check(allX)) return true;

        return false;
    }
};

/*
給你一個數組 問說是否有兩個切分點 這兩個點所涵蓋的範圍 他們之間不會有其他點跨過到他 可以擦邊 如果有跨過的 就拿跨過的當作切分點 看能否涵蓋到下一區域沒有這種現象
判斷 重疊現象發生的次數 可以用Union find 把重疊的交疊再一起 判斷uf後有多少種 更簡單點直接count就好
*/
