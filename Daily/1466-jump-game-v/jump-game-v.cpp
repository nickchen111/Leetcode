class Solution {
    int memo[1005];
    int d, n;
public:
    int maxJumps(vector<int>& arr, int d) {
        this -> d = d;
        n = arr.size();
        memset(memo,-1,sizeof(memo));
        int res = 1;

        for(int i = 0; i < arr.size(); i++){
            if(memo[i] != -1) continue;
            res = max(res, DFS(arr,i));
        }

        return res;
    }
    int DFS(vector<int>& arr, int curPos){
        if(memo[curPos] != -1) return memo[curPos];

        int start = max(0, curPos-d);
        int end = min(n-1, curPos + d);
        int res = 1;
        for(int i = curPos+1; i <= end; i++){
            if(arr[curPos] <= arr[i]) break;
            res = max(res, DFS(arr, i) + 1);
        }

        for(int i = curPos-1; i >= start; i--){
            if(arr[curPos] <= arr[i]) break;
            res = max(res, DFS(arr,i)+1);
        }

        memo[curPos] = res;
        return res;
    }
};

/*
只能跳特定左右範圍 並且高度從高到低
可任意從某個index開始跳 問說最多可以跳到多少個index
*/