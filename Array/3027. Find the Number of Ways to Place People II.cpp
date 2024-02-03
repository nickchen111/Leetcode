/*
3027. Find the Number of Ways to Place People II
*/

// TC:O(nlgn + n^2) SC:O(1)
class Solution {
public:
    int numberOfPairs(vector<vector<int>>& points) {
        auto cmp = [](const vector<int>& a, const vector<int>& b){
            if(a[0] != b[0]) return a[0] < b[0];
            else return a[1] > b[1];
        };
        
        sort(points.begin(), points.end(), cmp);
        int res = 0;
        
        for(int i = 0; i < points.size(); i++){
            int maxHeight =  INT_MIN;
            int maxRight = INT_MAX;
            for(int j = i+1; j < points.size(); j++){
                //按照我的邏輯一開始會先遇到比較左邊的可能性
                // x軸相同 先看他最低可以到多低 之後的都要比他高
                if(points[j][0] < maxRight && points[j][1] > maxHeight && points[i][0] == points[j][0]){
                    res += 1;
                    maxHeight = max(maxHeight, points[j][1]);
                }
                // y軸相同
                else if(points[j][1] > maxHeight && points[j][0] < maxRight && points[i][1] == points[j][1]){
                    res += 1;
                    maxRight = max(maxRight, points[j][0]);
                    maxHeight = max(maxHeight, points[j][1]);
                }
                else if(points[j][1] > maxHeight && points[j][0] < maxRight && points[i][0] < points[j][0] && points[i][1] > points[j][1]) {
                    res += 1;
                    maxHeight = max(maxHeight, points[j][1]);;
                    maxRight = max(maxRight, points[j][0]);
                }
            
            }
        }
        
        return res;
    }
};

/*
此題給你一堆座標 問說兩個動漫角色想要獨處 總共有幾種方式可以獨處 獨處定義為不能有其他人在邊上or在圍欄內
c大本人必須在左上角 t大必須在右下角 每個點都必須放置一人 總共n個人
可以圍成一個方形 也可以是一條線

我的想法是先sort最左邊的然後再看最上面 以這點當作左上角開始遍歷他的所有可能
當前遇到的第一個點最近的有可能就是他底下的點 如果更新了這點 那麼他底下所有點也就無法更新了 所以我們要時時更新maxHeight 之後的點都要大於這個點才能被加入
再來排除跟自己同x軸的點後 後面遇到的點可能會是跟我們水平的或者右上右下的 不論哪個他肯定都是離我們最近的 這時候要更新maxRight 之後的點都要小於他才行
[[1,6],[0,9],[0,3]]
*/
