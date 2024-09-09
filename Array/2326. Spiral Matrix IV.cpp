/*
2326. Spiral Matrix IV
*/


// TC:O(n) SC:O(1)
class Solution {
public:
    vector<vector<int>> spiralMatrix(int m, int n, ListNode* head) {
        vector<vector<int>> res(m, vector<int>(n,-1));
        // right down left up
        vector<pair<int,int>> dirs = {{0,1}, {-1,0}, {0,-1}, {1,0}};
        int k = dirs.size();
        int idx = 0;
        int x = 0, y = 0;
        while(head){
            res[x][y] = head->val;
            int nx = dirs[idx%k].first + x;
            int ny = dirs[idx%k].second + y;
            if(nx >= m || ny >= n || nx < 0 || ny < 0 || res[nx][ny] != -1){
                idx += 1;
                if(head->next == NULL) break;
            }
            else {
                x = nx;
                y = ny;
                head = head -> next;
            } 
        }

        return res;
    }
};
