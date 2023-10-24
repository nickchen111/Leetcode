/*
84. Largest Rectangle in Histogram
*/

//three pass
// tc: O(3n) sc:O(3n)
class Solution {
    //three pass版本
public:
    int largestRectangleArea(vector<int>& heights) {
        //單調遞增棧
        int n = heights.size();
        stack<int> s;//裝的是index

        //先來找nextsmaller
        vector<int> nextSmaller(n, n);//此index next smaller的Index為何
        for(int i =0; i < n; i++){
            while(!s.empty() && heights[s.top()] > heights[i]){
                nextSmaller[s.top()] = i;
                s.pop();
            }
            s.push(i);
        }

        //將s清空
        while(!s.empty()){
            s.pop();
        }

        //找prevsmaller
        vector<int> prevSmaller(n, -1);
        for(int i = 0; i < n; i++){
            while(!s.empty() && heights[s.top()] > heights[i]){
                s.pop();
            }
            if(!s.empty()) prevSmaller[i] = s.top();
            s.push(i);
        }

        //開始算面積
        int res = INT_MIN;
        for(int i = 0; i<n; i++){
            int area = heights[i]*(nextSmaller[i]-prevSmaller[i] - 1);
            res = max(res, area);
        }

        return res;
    }
};

// one pass
// tc: O(n) sc:O(n)
class Solution {
    //one pass版本
public:
    int largestRectangleArea(vector<int>& heights) {
        //單調遞增棧
        heights.push_back(0);
        heights.insert(heights.begin(), 0);
        int n = heights.size();
        int res = 0;
        stack<int> s;//裝的是index


        for(int i =0; i < n; i++){
            // i就是nextsmaller s.top() 就是prevsmaller 只要能觸發這玩意 所以需要前後都加0 
            while(!s.empty() && heights[s.top()] > heights[i]){
                int H = heights[s.top()];
                s.pop();
                int area = H*(i-s.top()-1);
                res = max(res, area);
            }
            s.push(i);
        }


        return res;
    }
};


/*
解題思路：
感覺有點單調遞增stack的味道
去找到一個高度他的前一個比他低的 跟後一個比他低的  兩index 相減x高度就是此面積
但要注意如果前面沒比他低的 就放-1 後面沒有的話就放n(數組index從0~n-1)
上述寫法為three pass
有one pass的方式但要注意的細節也是 跟前一個問題一樣 但他的操作是在前後各加上0 因為不會有比低的數值
*/
