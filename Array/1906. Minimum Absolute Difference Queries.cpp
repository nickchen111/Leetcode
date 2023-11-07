/*
1906. Minimum Absolute Difference Queries
*/

// TC:O(N*100 + 100*n) N為數組長度 n為query次數 SC:O(100*N+n)
class Solution {
public:
    vector<int> minDifference(vector<int>& nums, vector<vector<int>>& queries) {
        int n = nums.size();
        vector<vector<int>> presum(101,vector<int>(n+1,0));

        // 這段TC n*100
        for(int k = 1; k<=100; k++){
            for(int i = 1; i<=n; i++){
                //即可知道任意區間包含多少種k的數字 O(1)時間知道
                presum[k][i] = presum[k][i-1] + (nums[i-1] == k);
            }
        }

        vector<int> res;
        for(auto query:queries){
            int left = query[0]; int right = query[1];
            vector<int> arr;
            for(int k = 1; k<=100; k++){
                int cur = presum[k][right+1]-presum[k][left];
                if(cur > 0) arr.push_back(k);
                //小優化
                if(arr.size() >= 2 && arr.back()-arr[arr.size()-2] == 1) break;
            }

            if(arr.size() <= 1) res.push_back(-1);
            else {
                int gap = INT_MAX/2;
                for(int i = 1; i<arr.size(); i++){
                    gap = min(gap,arr[i]-arr[i-1]);
                }
                res.push_back(gap);
            }
        }

        return res;

    }
};

/*
此題如果是單純求問你一個數組內最大跟最小的差值就很簡單 直接紀錄最大最小然後求差值or利用前綴和判斷哪個區間相減最小 
但這題考察如果我要問很多次的話該怎麼降時間複雜度 題目有給一個條件是數組裡面的數字數值最多只到100
那麼如果創一個presum數組去紀錄某段區間內的此數字有幾個即可在O(1)時間判斷出gap最小值 但當然還是得遍歷一次1~100
小小優化是當數組遍歷過程中有發現gap為一時就可以停止不用遍歷到最後100
*/
