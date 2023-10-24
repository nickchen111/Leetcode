/*
1326. Minimum Number of Taps to Open to Water a Garden
*/


//sort by starting point TC:O(n+nlgn) SC:O(n)
class Solution {
    static bool cmp(pair<int,int>& a, pair<int,int>& b){
        if(a.first != b.first){
            return a.first < b.first;
        }

        else return a.second > b.second;//越長涵蓋越多的越好 greedy感
    }
public:
    int minTaps(int n, vector<int>& ranges) {
        vector<pair<int,int>> intervals(n+1);// 也可以用array<int,2>

        for(int i = 0; i < ranges.size(); i++){
            intervals[i] = {i-ranges[i], i+ranges[i]};
        }

        sort(intervals.begin(), intervals.end(), cmp);

        int i = 0;
        int count = 0;
        int far = 0;
        while(i < intervals.size()){
            int nextFar = far;
            while(i < intervals.size() && intervals[i].first <=far){
                nextFar = max(nextFar, intervals[i].second);
                i++;
            }
            count++;
            if(nextFar >= n) return count;
            else if(nextFar == far) return -1;//有斷層
            far = nextFar;
        }

        return -1;
    }
};

/*
與1024概念相同的題目
想求至少要開幾個水龍頭去澆到所有的花
min 涵蓋所有區間 -> sort by starting point
*/
