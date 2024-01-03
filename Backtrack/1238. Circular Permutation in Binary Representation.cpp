/*
1238. Circular Permutation in Binary Representation
*/

// TC:O(2^n) SC:O(2^n)
class Solution {
    vector<bool> visited;
    vector<int> res;
public:
    vector<int> circularPermutation(int n, int start) {
        int m = 1 << n;
        visited.resize(m);
        
        vector<int> temp;
        DFS(n,start,start,temp);

        return res;
    }
    void DFS(int n, int state, int target, vector<int>& temp){
        
        if(res.size() != 0 || visited[state]){
            if(state == target && temp.size() == (1 << n)){
                res = temp;
            }
            return;
        }
        visited[state] = 1;
        temp.push_back(state);
        for(int i = 0; i < n; i++){
            //XOR 1 XoR 1 = 0 , 1 XOR 0 1
            int newState = state ^ (1<<i);
            DFS(n, newState, target, temp);
        }
        visited[state] = 0;
        temp.pop_back();
    }
};

/*
開頭必定是start 
中間要是前一個數字 只差1 bit 最後要跟start 也只差one bit
n = 16
backtrack state 2^16次方看有無遍歷過
2^16 -> [x x x x x x x x x... 16位]
*/
