/*
2438. Range Product Queries of Powers
*/

// TC:O(n+32*32) SC:O(32*32+n)
class Solution {
    using LL = long long;
    LL M = 1e9+7;
public:
    vector<int> productQueries(int n, vector<vector<int>>& queries) {
        vector<int> arr;//裡面放的是指數
        int count = 0;
        while(n!=0){
            int cur = n&1;
            n>>=1;
            if(cur != 0){
                arr.push_back(count);
            }
            count+=1;
        }

        int m = arr.size();
        vector<int> presum(m+1);
        presum[0] = 0;
        for(int i = 1; i<=m; i++){
            presum[i] = presum[i-1]+arr[i-1];
        }

        vector<int> two(32*32);//1+2+3+4+.....+32 if每個32位上都是1的話 2^0 + 2^1+2^2+2^3...
        two[0] = 1;
        for(int i =1; i<32*32;i++){
            two[i] = two[i-1]*2%M;
        }

        vector<int> res;
        for(auto q:queries){
            int a = q[0]; int b = q[1];
            int sum = presum[b+1]-presum[a];
            res.push_back(two[sum]);//此處可以對pow 先做預處理否則每次2的100次方101次方都真的會做100 101次
        }

        return res;
    }
};

//另外一種轉十進位變二進位寫法
class Solution {
    using LL = long long;
    LL M = 1e9+7;
public:
    vector<int> productQueries(int n, vector<vector<int>>& queries) {
        vector<int> arr;//裡面放的是指數
        for(int i = 0; i<32; i++){
            if(n%2 != 0){
                arr.push_back(i);
            }
            n/=2;
            if(n==0) break;
        }

        int m = arr.size();
        vector<int> presum(m+1);
        presum[0] = 0;
        for(int i = 1; i<=m; i++){
            presum[i] = presum[i-1]+arr[i-1];
        }

        vector<int> two(32*32);//1+2+3+4+.....+32 if每個32位上都是1的話 2^0 + 2^1+2^2+2^3...
        two[0] = 1;
        for(int i =1; i<32*32;i++){
            two[i] = two[i-1]*2%M;
        }

        vector<int> res;
        for(auto q:queries){
            int a = q[0]; int b = q[1];
            int sum = presum[b+1]-presum[a];
            res.push_back(two[sum]);//此處可以對pow 先做預處理否則每次2的100次方101次方都真的會做100 101次
        }

        return res;
    }
};

//乘法做法 難點在 (x*y)%M != (x%M)*(y%M)
class Solution {
    using LL = long long;
    LL M = 1e9+7;
public:
    vector<int> productQueries(int n, vector<vector<int>>& queries) {
        vector<LL> arr;
        int count = 0;
        while(n!=0){
            int cur = n&1;
            n>>=1;
            if(cur != 0){
                arr.push_back(pow(2,count));
            }
            count+=1;
        }

        int m = arr.size();
        vector<LL> presum(m+1);
        presum[0] = 1;
        for(int i = 1; i<=m; i++){
            presum[i] = presum[i-1]*arr[i-1];//難點在 (x*y)%M != (x%M)*(y%M)
        }

        vector<int> res;
        for(auto q:queries){
            int a = q[0]; int b = q[1];
            int cur = (presum[b+1]/presum[a])%M;
            res.push_back(cur);
        }

        return res;
    }
};
