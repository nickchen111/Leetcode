/*
42. Trapping Rain Water
*/

//three pass TC:O(n) SC:O(n)
class Solution {
public:
    int trap(vector<int>& height) {
        int n = height.size();
        vector<int> leftMost(n,0);
        vector<int> rightMost(n,0);

        for(int i = 1; i < n; i++){
            leftMost[i] = max(leftMost[i-1], height[i-1]);//自已i本身不算
        }

        for(int i = n-2; i>=0; i--){
            rightMost[i] = max(rightMost[i+1],height[i+1]);
        }

        int res = 0;
        for(int i = 0; i<n; i++){
            int h = min(leftMost[i], rightMost[i])-height[i];
            res+=max(0,h*1);//有可能0減掉自己高度變成負數
        }

        return res;
    }
};

//單調棧 one pass TC:O(n) SC:O(n)
class Solution {
public:
    int trap(vector<int>& height) {
        int n = height.size();
        stack<int> Stack;
        
        int res = 0;
        for(int i = 0; i<n; i++){
            while(!Stack.empty() && height[i] > height[Stack.top()]){
                int base = height[Stack.top()];
                Stack.pop();
                if(Stack.empty()) continue;
                int w = i - Stack.top()-1;
                int h = min(height[Stack.top()],height[i]) - base;
                res+=h*w;
            }
            Stack.push(i);
        }

        return res;
    }
};


//two pointer TC:O(n) SC:O(1)
class Solution {
public:
    int trap(vector<int>& height) {
        int n = height.size();
        if(n == 0) return 0;
        int l = 0;
        int r = n-1;
        //去計算每個格子的蓄水量
        int max_l = height[0];//往前走將會不斷紀錄目前走的階段最高的位置
        int max_r = height[n-1];
        int ans = 0;
        while(l < r){
            if(max_l < max_r){
                ans+=max_l - height[l];
                max_l = max(max_l,height[++l]);
            }
            else {
                ans+=max_r - height[r];
                max_r = max(max_r,height[--r]);
            }
        }

        return ans;
    }
};

/*
此題有3種想法
1.去挨個計算每個方格能儲存的水量 所以需要去紀錄他左邊最高跟右邊最高 取最小值 TC:O(n) SC:O(n) 此方法如果想將空間降到1只能提升時間變 n^2
2.維護一個單調遞減棧 高度為棧中倒數第二的元素減去自身高度 寬度為棧中倒數第二跟即將進棧的元素之間的index差-1 TC:O(n) SC:O(n)
3. 根據第一個想法會發現 leftMost是單調遞增的 rightMost 從右邊往左看也是單調遞增 可以思考用two pointer的形式來做 可得到 TC:O(n) SC:O(1)的最優解
*/
