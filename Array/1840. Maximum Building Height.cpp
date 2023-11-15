/*
1840. Maximum Building Height
*/


// TC:O(m) SC:O(m)
class Solution {
public:
    int maxBuilding(int n, vector<vector<int>>& restrictions) {
        restrictions.push_back({1,0});
        sort(restrictions.begin(),restrictions.end());
        int m = restrictions.size();
        vector<int> pos(m);
        vector<int> h(m);
        vector<int> lim(m);
        for(int i =0; i<m; i++){
            pos[i] = restrictions[i][0];
            lim[i] = restrictions[i][1];
        }
        h[0] = 0;//題目規定
        for(int i = 1; i<m; i++){
            h[i] = min(lim[i],h[i-1]+pos[i]-pos[i-1]);
        }
        for(int i = m-2; i>=1; i--){
            h[i] = min(h[i],h[i+1]+pos[i+1]-pos[i]); 
        }

        //開始找peak高度
        int res=0;
        for(int i=1; i<m; i++){
            int peak = h[i] + ((h[i-1]-h[i])+(pos[i]-pos[i-1]))/2;
            res = max(res,peak);
        }
        //最後可以無限遞增1
        res = max(res, h[m-1]+n-pos[m-1]);

        return res;
    }
};

/*
此題最難處在於想到兩個高樓的高度差必須 小於等於兩者的位置差 否則就無法造出peak
得知這點後就用two pass distribution的方式從左以及從右遍歷找出每個限定高度的高樓的最高高度
h[i]-h[i-1] <= p[i]-p[i-1];
h[i]-h[i+1] <= p[i+1]-p[i];

找peak高度就是二元一次方程式
h[i-1]+x = h[i]+y;
p[i-1]+x=p[i]-y;
peak = h[i-1]+x = h[i]+y = ((h[i-1]-h[i] )+(p[i]-p[i-1]))/2;
*/
