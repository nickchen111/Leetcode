/*
1814. Count Nice Pairs in an Array
*/


// 寫成Hash + prefix 形式 稍微慢一點
class Solution {
    long long M = 1e9+7;
public:
    int countNicePairs(vector<int>& nums) {
        //hash map+prefix
        unordered_map<int,long long> map;
        int n = nums.size();
        vector<int> arr(n);
        long long res = 0;
        for(int i =0; i<n; i++){
            arr[i] = reverseNum(nums[i]);
            if(map[nums[i]-arr[i]] > 0){
                res = (res + map[nums[i]-arr[i]])%M;
            }
            map[nums[i]-arr[i]]+=1;
        }


        return res;

    }
    //整數reverse操作
    int reverseNum(int n){
        int r = 0;
        while(n != 0){
            r = r*10;
            r = r+n%10;
            n/=10;
        }

        return r;
    }
};

// 查找完後 Cn取2將答案取出
class Solution {
    long long M = 1e9+7;
public:
    int countNicePairs(vector<int>& nums) {
        //hash map
        unordered_map<int,long long> map;
        int n = nums.size();
        vector<int> arr(n);
        for(int i =0; i<n; i++){
            arr[i] = reverseNum(nums[i]);
            map[nums[i]-arr[i]]+=1;
        }

        long long res = 0;
        for(auto p:map){
            if(p.second > 1){
                res = (res + ((p.second)*(p.second-1)/2))%M;
            }
        }

        return res;

    }
    //整數reverse操作
    int reverseNum(int n){
        int r = 0;
        while(n != 0){
            r = r*10;
            r = r+n%10;
            n/=10;
        }

        return r;
    }
};
/*
nums[i]+ rev[j] = nums[j] + rev[i]
nums[i]-rev[i] = nums[j] - rev[j]; hash map去找一樣的
cn取k這種的
*/
