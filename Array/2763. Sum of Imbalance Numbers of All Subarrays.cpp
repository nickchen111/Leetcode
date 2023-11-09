/*
2763. Sum of Imbalance Numbers of All Subarrays
*/

// count subarray by element n方寫法 TC:O(n^2) SC:O(n)
class Solution {
public:
    int sumImbalanceNumbers(vector<int>& nums) {
        int n = nums.size();
        int res = 0;
        //遍歷每個點 assume他是區間最小值 如果後來發現不是的話要扣掉
        for(int i=0; i<n; i++){
            int prevInvalid = -1;
            int prevThanOne = -1;
            for(int j = i-1; j>=0; j--){
                if(nums[i]+1 == nums[j]){
                    prevInvalid = j;
                    break;
                }
                if(nums[j] > nums[i]+1 && prevThanOne == -1){
                    prevThanOne = j;
                }
            }

            int afterInvalid = n;
            int afterThanOne = n;
            for(int j = i+1; j<n; j++){
                if(nums[j] == nums[i] || nums[j] == nums[i]+1){
                    afterInvalid = j;
                    break;
                }
                if(nums[j] > nums[i]+1 && afterThanOne == n){
                    afterThanOne = j;
                }
            }

            int a = i-prevInvalid;
            int b = afterInvalid-i;
            int c = i-max(prevInvalid,prevThanOne);
            int d = min(afterInvalid,afterThanOne)-i;
            res+= a*b-c*d;
        }

        return res;
    }
};

// count subarray by element 線性寫法 TC:O(n) SC:O(n)
class Solution {
public:
    int sumImbalanceNumbers(vector<int>& nums) {
        //分四段去求
        int n = nums.size();
        vector<int> prevInvalid(n,-1);
        vector<int> val2pos(1005,-1);
        //開始求每個index前面比他還大1的位置
        for(int i = 0; i<n; i++){
            prevInvalid[i] = val2pos[nums[i]+1];
            val2pos[nums[i]] = i;
        }

        vector<int> afterInvalid(n,n);
        for(int i = 0; i<1005; i++) val2pos[i] = n;
        //求每個元素後面比他大一or一樣大的位置 
        for(int i = n-1; i>=0; i--){
            afterInvalid[i] = min(val2pos[nums[i]+1],val2pos[nums[i]]);
            val2pos[nums[i]] = i;
        }

        vector<int> prevThanOne(n,-1);
        vector<int> afterThanOne(n,n);
        stack<int> s;
        //求出每個位置前面比他大至少2的數字位置
        for(int i = 0; i<n; i++){
            while(!s.empty() && nums[s.top()] <= nums[i]+1){
                s.pop();
            }
            if(!s.empty()) prevThanOne[i] = s.top();
            s.push(i);
        }

        while(!s.empty()) s.pop();
        //求出每個位置後面比他大至少2的數字位置
        for(int i = n-1; i>=0; i--){
            while(!s.empty() && nums[s.top()] <= nums[i]+1){
                s.pop();
            }
            if(!s.empty()) afterThanOne[i] = s.top();
            s.push(i);
        }

        int res = 0;
        for(int i = 0; i<n; i++){
            int a = i - prevInvalid[i];
            int b = afterInvalid[i] - i;
            int c = i - max(prevInvalid[i],prevThanOne[i]);
            int d = min(afterInvalid[i], afterThanOne[i]) - i;
            res+= a*b-c*d;
        }

        return res;
    }
};

//巧妙的暴力解TC:O(n^2) SC:O(n)
class Solution {
public:
    int sumImbalanceNumbers(vector<int>& nums) {
        int n= nums.size();
        int res = 0;
        for(int i=0; i<n; i++){
            int count = -1;
            unordered_set<int> visited;
            for(int j = i; j<n; j++){
                if(visited.find(nums[j]) == visited.end()){
                    count+=1;
                    if(visited.find(nums[j]+1) != visited.end()){
                        count-=1;
                    }
                    if(visited.find(nums[j]-1) != visited.end()){
                        count-=1;
                    }
                }
                res+=count;
                visited.insert(nums[j]);
            }
        }

        return res;
    }
};

/*
此題比較巧妙的暴力解為去思考每個元素當頭 相對應每個以他為首的子數組的話每加入一個元素會對答案產生什麼樣影響
[X X X X ] count = Y;
新加入一個Z
[X X Z X X]
if nums[z] 已經存在了 count = count不變
if nums[z] 不存在 先假設count+=1;
判斷  nums[z]+1是否存在 存在 count-=1
     nums[z]-1是否存在 存在count-=1

第二種可以用線性解orn^2的方法為 count subarray be element
將每個元素都當成區間最小值
4 [x x x x x 3 x x x x x ]3
A.       C.  i.    D.     B      
約定一下前面的i如果遇到同樣元素 他就不能貢獻了 要靠後面的i
1. the subarray cannot contain nums[i]+1 before or after i
2. the subaray cannot contain nums[i] after i
A:prevInvalid
B;afterInvalid
需要扣掉一種情況nums[i]是老大 他排序後會無法貢獻數值
C:prevLargerThanOne
D:afterLargerThanOne
(i-prevInvalid)*(afterInvalid-i)
(i-prevLargerThanOne)*(afterLargerThanOne-i)

*/
