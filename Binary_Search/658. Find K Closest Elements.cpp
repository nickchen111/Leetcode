/*
658. Find K Closest Elements
*/

//二分  TC:O(lgn + k) SC:O(k)
class Solution {
public:
    vector<int> findClosestElements(vector<int>& arr, int k, int x) {
        int p = leftBound(arr,x);
        int left = p-1;
        int right = p;
        vector<int> res;

        while(right-left-1 < k){
            if(left == -1){
                res.push_back(arr[right]);
                right++;
            }
            else if(right == arr.size()){
                res.insert(res.begin(), arr[left]);
                left--;
            }
            else if(x-arr[left] > arr[right]-x){
                res.push_back(arr[right]);
                right++;
            }
            else{
                res.insert(res.begin(),arr[left]);
                left--;
            }
        }

        return res;
    }

    int leftBound(vector<int>& arr, int x){
        int left = 0;
        int right = arr.size();
        while(left < right){
            int mid = left + (right-left)/2;

            if(arr[mid] < x){
                left = mid+1;
            }
            else{
                right = mid;
            }
        }

        return left;
    }
};

//二分 想法優化 TC:O(lg(n-k)+k) SC:O(k)
class Solution {
public:
    vector<int> findClosestElements(vector<int>& arr, int k, int x) {
        //找k+1個區間出來 只找最左邊邊界符合條件下最左的位置
        int lo = 0;
        int hi = arr.size()-k;
        while(lo < hi){
            int mid = lo + (hi-lo)/2;
            //arr[mid+k]會算到k+1個去
            if(x-arr[mid] > arr[mid+k]-x){
                lo = mid+1;
            }
            else if(x-arr[mid] <= arr[mid+k]-x){
                hi = mid;
            }
        }

        vector<int> res;
        for(int i = lo; i<lo+k; i++){
            res.push_back(arr[i]);
        }

        return res;
    }
};

//heap TC:O(nlgn) SC:O(n)
class Solution {
public:
    vector<int> findClosestElements(vector<int>& arr, int k, int x) {
        //PQ 直接把差值小的放在頂堆
        auto comp = [](pair<int,int>& a, pair<int,int>& b){
            if(a.first != b.first){
                return a.first > b.first;
            }
            else{
                return a.second > b.second;// index前面的優先
            }
        };
        priority_queue<pair<int,int>, vector<pair<int,int>>, decltype(comp)> pq;
        for(int i = 0; i<arr.size(); i++){
            pq.push({abs(arr[i]-x),i});
        }
        vector<int> res;
        for(int i = 0; i<k; i++){
            res.push_back(arr[pq.top().second]);
            pq.pop();
        }
        sort(res.begin(), res.end());

        return res;
    }
};

/*
此題的二分可以有兩種想法
1. 先二分搜索出x所在位置 然後開始左右比對找到k個最近的數值
起始狀況：  1  2  3  4  5
            p-1 x(p)
2. 二分搜索的是k+1個區間 開始找左邊的邊界最左邊的位置在哪 找到以後開始算k-1個就是答案
可用pq
3. PQ 直接把差值小的放在頂堆
*/
