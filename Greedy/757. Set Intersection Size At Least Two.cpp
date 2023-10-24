/*
757. Set Intersection Size At Least Two
*/

// sort by ending point TC:O(nlgn) SC:O(1)
class Solution {
    static bool cmp(vector<int>& a, vector<int>& b){
        return a[1] < b[1];
    }
public:
    int intersectionSizeTwo(vector<vector<int>>& intervals) {
        //sort by ending point 來解這種non-overlapping題目
        sort(intervals.begin(), intervals.end(), cmp);

        //two pointer
        int secArrow = intervals[0][1]-1;
        int firArrow = intervals[0][1];
        int i = 1;
        int count = 2;
        while(i < intervals.size()){
            //兩箭都射到
            if(intervals[i][0] <= secArrow){
                i++;
            }
            //只射到一箭
            else if(intervals[i][0] <= firArrow){
                count++;
                secArrow = firArrow;
                firArrow = intervals[i][1];
                i++;
                //也可以將sort那段改成 短邊先sort在前面
                if(secArrow == firArrow){
                    secArrow = firArrow-1;
                }
            }
            //兩箭都沒射到
            else if(intervals[i][0] > firArrow){
                count+=2;
                secArrow = intervals[i][1]-1;
                firArrow = intervals[i][1];
                i++;
            }
        }

        return count;
    }
};
/*
與射氣球問題類似 by greedy
但是改成每個區間要兩箭
所以要考慮三種情況
1.目前的兩件完全涵蓋到下個區間
2.目前兩件只有一件涵蓋到下個區間
3.目前兩件完全沒有任何一件涵蓋到下個區間
*/
