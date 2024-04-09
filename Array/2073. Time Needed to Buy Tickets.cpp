/*
2073. Time Needed to Buy Tickets
*/

// TC:O(n^2) SC:O(n)
class Solution {
public:
    int timeRequiredToBuy(vector<int>& tickets, int k) {
        int n = tickets.size();
        queue<pair<int,int>> q; // ticket -> index
        for(int i = 0; i < n; i++){
            q.push({tickets[i], i});
        }

        int count = 0;
        while(!q.empty()){
            int sz = q.size();
            while(sz--){
                int curLeft = q.front().first;
                int idx = q.front().second;
                q.pop();
                curLeft -= 1;
                count += 1;
                if(curLeft == 0 && idx == k) return count;
                else if(curLeft > 0){
                    q.push({curLeft,idx});
                }
            }
        }

        return -1;
    }
};

/*
Simulation
問說指定的某個人多久可以買完他想買的票張數
一圈只能買一張的情況下 也就是在1之前都要一整圈到下一輪
最後一輪只要看前面有多少人比他大
n^2解 n = 100
*/
