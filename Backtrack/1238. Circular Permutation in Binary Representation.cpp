/*
1238. Circular Permutation in Binary Representation
*/


// Gray code TC:O(n^2 + 2^n) SC:O(2^n)
class Solution {
public:
    vector<int> circularPermutation(int n, int start) {
        vector<int> arr;
        arr.push_back(0);

        for(int i = 0; i < n; i++){
            int len = arr.size();
            for(int j = len-1; j >= 0; j--){
                arr.push_back(arr[j]+(1<<i));
            }
        }

        int j = 0;
        while(arr[j] != start){
            j++;
        }
        vector<int> res;
        for(int i = j; i < arr.size(); i++){
            res.push_back(arr[i]);
        }
        for(int i = 0; i < j; i++){
            res.push_back(arr[i]);
        }

        return res;
    }
};

/*
之前backtrack不給過了＠＠
只能改用數學 gray code
ex :
1. 先去對某個長度的數字做鏡像
2. 然後前半部補0 後半部鏡像的補1 這樣就是格雷馬數了
00
01
11
10 
11
10
01
00

000
001
011
010 
011
111
110
000
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
