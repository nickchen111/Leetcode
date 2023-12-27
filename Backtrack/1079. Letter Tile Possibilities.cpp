/*
1079. Letter Tile Possibilities
*/

// TC:O(2^n) SC:O(2^n) 
class Solution {
    unordered_set<string> set;
    vector<bool> visited;
public:
    int numTilePossibilities(string tiles) {
        string str = "";
        int n = tiles.size();
        visited = vector<bool>(n,0);
        backtrack(tiles, str);

        return (int)set.size();
    }
    void backtrack(string& tiles, string& str){
       
        for(int i = 0; i < tiles.size(); i++){
            if(visited[i] == 1) continue;

            visited[i] = 1;
            str += tiles[i];
            set.insert(str);
            backtrack(tiles,str);
            str.pop_back();
            visited[i] = 0;
        }

        
    }
};

/*
給你一堆磁磚 上面有寫大寫字母 問說有多少種不同的字可以拼出
n = 7 -> backtrack 用set去重 列舉所有可能
*/
