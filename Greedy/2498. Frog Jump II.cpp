/*
2498. Frog Jump II
*/

// TC:O(n) SC:O(1)
class Solution {
public:
    int maxJump(vector<int>& stones) {
        int n = stones.size();
        if(n == 2) return stones[1] - stones[0];
        
        int test1 = 0;
        for(int i = 0; i < n; i++){
            if(i+2 < n){
                test1 = max(test1, max(stones[i+2] - stones[i], stones[i+1] - (i-1 >= 0 ? stones[i-1]:stones[0]) ));
                i += 1;
            }
            else if(i+1 < n){
                test1 = max(test1, max(stones[i+1]-stones[i], stones[i+1] - (i-1 >= 0 ? stones[i-1]:stones[0]) ));
            }
        }

        return test1;
    }
};

/*
青蛙從原點跳到終點在跳回原點
中間經過的路線的最大值 找最小可能跳一圈
我最初想法是 要保留距離原點近的石頭 別人跳回來可以省一段路
原點到其他點 [0 2 5 6 7]
終點到其他點 [7 5 2 1 0]
貪心的想 如果我第一個點跳 2 7跳回來最短就會是 5 如果我跳5 7會經過2跳回來 2
有種這點我跳下點我不可跳的感覺 需要間隔跳
*/
