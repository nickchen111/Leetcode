/*
1052. Grumpy Bookstore Owner
*/


// TC:O(n) SC:O(1)
class Solution {
public:
    int maxSatisfied(vector<int>& customers, vector<int>& grumpy, int minutes) {
        int n = customers.size();
        int sum = 0;
        int count = 0;
        int i = 0;
        int res = 0;
        for(int i = 0; i<n; i++){
            if(grumpy[i] == 0) sum+=customers[i];
        }

        for(int j = 0; j < n; j++){
            if(grumpy[j] == 1){
                sum+=customers[j];
            }
            count++;
            if(count > minutes){
                if(grumpy[i] == 1){
                    sum-=customers[i];
                }
                i++;
                count--;
            }
            res = max(res, sum);
        }

        return res;
    }
};
