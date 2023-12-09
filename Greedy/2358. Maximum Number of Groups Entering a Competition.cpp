/*
2358. Maximum Number of Groups Entering a Competition
*/

// TC:O(nlgn) SC:O(1)
class Solution {
public:
    int maximumGroups(vector<int>& grades) {
        int res = 0;
        sort(grades.begin(), grades.end());
        int n = grades.size();
        int i = 0;
        int take = 1;
        int sum = 0;
        while(i < grades.size()){
            int sum_new = 0;
            int count = 0;
            for(int j = 0; j < take; j++){
                if(i == n) break;
                sum_new += grades[i];
                count++;
                i++;
            }
            if(sum_new > sum && take == count){
                res++;
                sum = sum_new;
                take = take + 1;
            }
        }

        return res;
    }
};


/*
此題限制
1.輸入的某一組總和小於下一組
2.輸入的某一組人數小於下一組
請問最多可以輸入幾組
1 2 3 4 5 6 
*/
