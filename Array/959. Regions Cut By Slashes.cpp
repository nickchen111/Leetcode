/*
959. Regions Cut By Slashes
*/

// TC:O(n^2) SC:O(n)
class Solution {
    vector<int> parent;
    int find(int x){
        if(x != parent[x]){
            parent[x] = find(parent[x]);
        }
        return parent[x];
    }
    void union_(int x, int y){
        x = find(x);
        y = find(y);
        if(x < y){
            parent[y] = x;
        }
        else parent[x] = y;
    }
public:
    int regionsBySlashes(vector<string>& grid) {
        int n = grid.size();
        parent.resize((n+1)*(n+1));

        for(int i = 0; i <= n; i++){
            for(int j = 0; j <= n; j++){
                int idx = i*(n+1)+j;
                parent[idx] = idx;
                if(i == 0 || j == 0 || i == n || j == n) parent[idx] = 0;
            }
        }

        int count = 1;
        for(int i = 0; i < n; i++){
            for(int j = 0; j < n; j++){
                if(grid[i][j] == ' ') continue;
                int a, b;
                if(grid[i][j] == '/'){
                    a = i*(n+1)+j+1;
                    b = (i+1)*(n+1)+j;
                }
                else if(grid[i][j] == '\\'){
                    a = i*(n+1)+j;
                    b = (i+1)*(n+1)+(j+1);
                }

                if(find(a) == find(b)){
                    count ++;
                }
                else {
                    union_(a, b);
                }
            }
        }

        return count;
    }
};

/*
" /"
"/ "

"/\\",
"\\/"
*/
