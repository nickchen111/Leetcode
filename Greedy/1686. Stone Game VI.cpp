/*
1686. Stone Game VI
*/

//TC:O(nlgn) SC:O(n)
class Solution {
public:
    int stoneGameVI(vector<int>& aliceValues, vector<int>& bobValues) {
        //創建一個最大收益由高到低的vector
        int n = aliceValues.size();
        vector<pair<int, int>> temp(n);

        for(int i = 0; i < n; i++){
            temp[i]= {aliceValues[i]+bobValues[i], i};
        }

        sort(temp.begin(), temp.end());
        reverse(temp.begin(), temp.end());

        int x=0; int y = 0; //遊戲開始
        for(int i = 0; i < n; i++){
            if(i%2 == 0) // alice 回合
                x+=aliceValues[temp[i].second];
            else y+=bobValues[temp[i].second];
        }

        if(x> y) return 1;
        else if(x < y) return -1;
        else return 0;
    }
};
