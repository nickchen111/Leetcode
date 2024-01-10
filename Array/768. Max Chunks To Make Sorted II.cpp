/*
768. Max Chunks To Make Sorted II
*/

// Stack TC:O(n) SC:O(1)
class Solution {
public:
    int maxChunksToSorted(vector<int>& arr) {
        int n = arr.size();
        int curMax = 0;
        stack<int> stack;
        for(int i = 0; i < n; i++){
            if(stack.empty() || stack.top() < arr[i]){
                stack.push(arr[i]);
                curMax = arr[i];
            }
            else {
                while(!stack.empty() && stack.top() > arr[i]) stack.pop();
                stack.push(curMax);
            }
        }

        return stack.size();
    }
};

// Presum TC:O(nlgn) SC:O(1)
class Solution {
    using LL = long long;
public:
    int maxChunksToSorted(vector<int>& arr) {
        int n = arr.size();
        vector<int> temp = arr;
        sort(temp.begin(), temp.end());
        

        int res = 0;
        LL sum1 = 0;
        LL sum2 = 0;
        for(int i = 0; i < n; i++){
            sum1 += arr[i];
            sum2 += temp[i];
            if(sum1 == sum2){
                res += 1;
                sum1 = 0;
                sum2 = 0;
            }
        }

        return res;
        
    }
};

/*
有重複項 切割數組最多能切幾塊 讓切割數組排序後能跟整個數組排序有一樣的結果
如果一段數組的presum值 等於 排序後的presum值 那麼這段數組就可以被切割出一組 代表裡面的數值排序後會在正確的位置上
*/
