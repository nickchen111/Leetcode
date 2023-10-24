/*
134. Gas Station
*/


//Graph  TC:O(n) SC:O(1)
class Solution {
public:
    int canCompleteCircuit(vector<int>& gas, vector<int>& cost) {
        //Graph 得出的結論 從過程中最低點當作出發點 相等於整個圖往上平移 所有點都會大於等於0
        int n = gas.size();
        int sum = 0;
        int minSum = 0;
        int start = 0;
        for(int i = 0; i<n; i++){
            sum+=gas[i]-cost[i];
            if(sum < minSum){
                start = i+1;//經過第i站後油量來到最低點 所以i+1站為出發點
                minSum = sum;
            }
        }

        if(sum < 0) return -1;//代表油量根本不夠
        return start == n ? 0:start;

        
    }
};

// Greedy TC:O(n) SC:O(1)
class Solution {
public:
    int canCompleteCircuit(vector<int>& gas, vector<int>& cost) {
        //Greedy根據觀察可以發現 只要從i 到 j的時候會變成負數 那麼從i到j之間出發的點都不可能是起點 
        //因為這之間從i到j時油量已經會是正數 還讓這之間的點從0開始 那更不可能到j時會是正數

        int n = gas.size();
        int tank = 0;
        int start = 0;
        int sum = 0;
        for(int i = 0; i<n; i++){
            sum+=gas[i]-cost[i];
            tank+=gas[i]-cost[i];
            if(tank < 0){
                start = i+1;
                tank = 0;
            }
        }
        if(sum < 0) return -1;

        return start == n ? 0:start;
    }
};
