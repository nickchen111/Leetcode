/*
973. K Closest Points to Origin
*/


//TC:O(n) SC:O(n)
class Solution {
    using LL = long long;
    vector<pair<LL,int>> arr;//(dist,index)
public:
    vector<vector<int>> kClosest(vector<vector<int>>& points, int k) {
        for(int i = 0; i<points.size(); i++){
            LL dist = (pow(points[i][0],2) + pow(points[i][1],2));
            arr.push_back({dist,i});
        }

        //quick sort
        LL kthDist = quickselect(0,arr.size()-1,k);//求出第k個的element對應的距離
        vector<vector<int>> res;
        for(auto x:arr){
            if(x.first <=kthDist){
                res.push_back(points[x.second]);
            }
        }

        return res;
    }
    LL quickselect(int a, int b, int k){
        LL pivot = arr[(a+b)/2].first;

        int i = a; int t = a; int j = b;//t是我們要走的指針
        while(j>=t){
            if(arr[t].first < pivot){
                swap(arr[t],arr[i]);
                i++;
                t++;
            }
            else if(arr[t].first > pivot){
                swap(arr[t],arr[j]);
                j--;
            }
            else {
                t++;
            }
        }

        if(i-a >= k) return quickselect(a,i-1,k);
        else if(j-a+1 >=k) return pivot;
        else return quickselect(j+1,b,k-(j-a+1));
    }
};

/*
O O O O O X X X X B B B B
a         i     jt
此題不僅僅是PQ考題 也可以用quick select優化 達到O(n)時間複雜度
*/
