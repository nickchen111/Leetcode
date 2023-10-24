/*
85. Maximal Rectangle
*/

//TC:O(m*n) SC:O(n)
class Solution {
public:
    int maximalRectangle(vector<vector<char>>& matrix) {
        int m = matrix.size(); int n = matrix[0].size();
        vector<int> histog(n, 0);
        int res = 0;
        for(int i = 0; i<m; i++){//row
            for(int j = 0; j<n; j++){//column
                if(matrix[i][j] == '1'){
                    histog[j] = histog[j]+1;
                }
                else histog[j] = 0;
            }
            res = max(res, LargestRectagleArea(histog));//把每一層都當作是一次的直方圖去計算最大面積 會從第一row到最後一row
        }

        return res;
    }
    int LargestRectagleArea(vector<int> heights){
        int n = heights.size();
        stack<int> s;//裝的是index

        //先來找nextsmaller
        vector<int> nextsmaller(n,n);
        for(int i = 0; i<n; i++){
            while(!s.empty()&&heights[s.top()] > heights[i]){
                nextsmaller[s.top()] = i;
                s.pop();
            }
            s.push(i);
        }

        while(!s.empty()){
            s.pop();
        }

        //在來找prevsmaller
        vector<int> prevsmaller(n,-1);
        for(int i = 0; i<n; i++){
            while(!s.empty() && heights[s.top()] > heights[i]){
                s.pop();                
            }
            if(!s.empty()) prevsmaller[i] = s.top();
            s.push(i);
        }

        //計算面積
        int res =INT_MIN;
        for(int i = 0; i<n; i++){
            int H = heights[i];
            int area = H*(nextsmaller[i]-prevsmaller[i]-1);
            res = max(res, area);
        }

        return res;
    }
};

//優化
class Solution {
public:
    int maximalRectangle(vector<vector<char>>& matrix) {
        int m = matrix.size(); int n = matrix[0].size();
        vector<int> histog(n, 0);
        int res = 0;
        for(int i = 0; i<m; i++){//row
            for(int j = 0; j<n; j++){//column
                if(matrix[i][j] == '1'){
                    histog[j] = histog[j]+1;
                }
                else histog[j] = 0;
            }
            res = max(res, LargestRectagleArea(histog));//把每一層都當作是一次的直方圖去計算最大面積 會從第一row到最後一row
        }

        return res;
    }
    int LargestRectagleArea(vector<int> heights){
        stack<int> s;//裝的是index
        heights.insert(heights.begin(), 0);
        heights.push_back(0);//確保兩邊都會去觸發
        int ans =0;
        int n = heights.size();


        for(int i = 0; i<n; i++){
            while(!s.empty()&&heights[s.top()] > heights[i]){
                int H = heights[s.top()];
                s.pop();
                int area = H*(i-s.top()-1);
                ans = max(ans, area);
            }
            s.push(i);
        }

        return ans;
    }
};

