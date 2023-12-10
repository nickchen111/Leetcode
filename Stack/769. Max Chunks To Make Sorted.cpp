/*
769. Max Chunks To Make Sorted
*/

// Stack TC:O(n) SC:O(n)
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

// Multiset TC:O(nlgn) SC:O(n)
class Solution {
public:
    int maxChunksToSorted(vector<int>& arr) {
        multiset<int> set1; //裝原始的
        multiset<int> set2; //排序的
        int count = 0;
        vector<int> nums = arr;
        sort(arr.begin(), arr.end());
        for(int i = 0; i < arr.size(); i++){
            set1.insert(nums[i]);
            set2.insert(arr[i]);
            if(set1 == set2) {
                count++;
                set1.clear();
                set2.clear();
            }
        }

        return count;

    }
};

// Presum TC:O(nlgn) SC:O(1)
class Solution {
public:
    int maxChunksToSorted(vector<int>& arr) {
        int n = arr.size();
        vector<int> nums = arr;
        sort(nums.begin(), nums.end());
        int count = 0;
        int sum1 = 0;
        int sum2 = 0;
        for(int i = 0; i < n; i++){
            sum1 += arr[i];
            sum2 += nums[i];

            if(sum1 == sum2){
                count++;
                sum1 = 0;
                sum2 = 0;
            }
        }

        return count;

    }
};

/*
此題說如果將數組內的數字拆出來 然後分別sort 之後重組可以組成原本就是sort狀態的最大的split數量為多少
題目故意說裡面的數字會從0~n-1 感覺會跟idx 有點關係
解法有三
要有一個原始數組 跟一個排序好的數組來看看有什麼突破點
2 1 3 4 4
1 2 3 4 4
1. multiset兩個互相比對目前加入的數字是否相同 一旦相同兩邊互相消掉 
2. presum 排序後的加總肯定是最小加總 如果原始數組排序跟排序後的一樣大 到那時就代表這些是一組的 因為排序過後的肯定會是最小加總
代表不會比較大的數字混雜在裡面 
3. 單調棧 挺特殊的維護方式 不僅是單調遞增 而且要維護每個trunck的代表人物-最大那項
ex : 3 [7 8 4 6 5] 9
小數先將大數remove掉 自己也不入棧 將最大數加回去 最終剩餘的元素都會是標誌性人物 棧有多少元素就有多少trucnck
  
*/
