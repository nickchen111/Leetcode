/*
1996. The Number of Weak Characters in the Game
*/


// TC:O(nlgn) SC:O(n)
class Solution {
public:
    int numberOfWeakCharacters(vector<vector<int>>& properties) {
        auto cmp = [](const vector<int>& a, const vector<int>& b){
            if(a[0] != b[0]) return a[0] < b[0];
            else return a[1] > b[1];
        };
        sort(properties.begin(), properties.end(), cmp);
        int res = 0;
        int n = properties.size();
        stack<int> stack;
        for(int i = 0; i < n; i++){
            while(!stack.empty() && properties[stack.top()][1] < properties[i][1]){
                stack.pop();
            }
            stack.push(i);
        }
        int count = 0;
        while(!stack.empty()){
            count += 1;
            stack.pop();
        }
        return n - count;
    }
};

/*
[1 5] [2 8] [2 4] [3 6] 2個 
[1 8] [2 4] [3 8] 維護單調遞減序列棧裡面的元素是吃不掉的
有點像俄羅斯娃娃354那題 先排序好某個寬 然後去判斷高
排序方式如果寬一樣 那麼較高的優先放入棧中
*/
