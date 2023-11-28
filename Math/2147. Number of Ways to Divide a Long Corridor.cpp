/*
2147. Number of Ways to Divide a Long Corridor
*/

//TC:O(n) SC:O(n)
class Solution {
    long long M = 1e9+7;
public:
    int numberOfWays(string corridor) {
        int n = corridor.size();
        vector<int> pos;
        for(int i = 0; i<n; i++){
            if(corridor[i] == 'S'){
                pos.push_back(i);
            }
        }
        if(pos.size()%2 != 0 || pos.size() == 0) return 0;
        long long res = 1;
        for(int i = 2; i+2<= pos.size(); i+=2){
            long long diff = pos[i]-pos[i-1];
            res *=diff;
            res%=M;
        }

        return res;
    }
};


/*
此題可以用數學方式解出來 兩個沙發一組 問你可以有多少種放屏風的方式
只需要把沙發兩兩一組後 互相減去雙方的距離代表可以插入屏風的位置選擇數量 相乘即答案
*/
