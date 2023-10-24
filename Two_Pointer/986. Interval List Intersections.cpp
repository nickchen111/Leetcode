/*
986. Interval List Intersections
*/

//TC:O(m+n) SC:O(m+n)
class Solution {
public:
    vector<vector<int>> intervalIntersection(vector<vector<int>>& firstList, vector<vector<int>>& secondList) {
        int i = 0; int j = 0;
        vector<vector<int>> res;
        while(i < firstList.size() && j < secondList.size()){
            int a1 = firstList[i][0]; int a2 = firstList[i][1];
            int b1 = secondList[j][0]; int b2 = secondList[j][1];
            

            //肯定重疊的狀態為
            if(!(b1 > a2 || a1 > b2)){
                res.push_back({max(a1,b1),min(a2,b2)});
            }

            //看誰該繼續move on
            if(a2 > b2){
                j++;
            }
            else if(a2 < b2){
                i++;
            }
            else{
                i++;
                j++;
            }
        }

        return res;
    }
};

/*
求有交集的區間是哪些
要想到說 有兩個區間有交集的狀況會是頭取兩區間最大值 尾取兩區間最小值
*/
