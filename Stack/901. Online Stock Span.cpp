/*
901. Online Stock Span
*/

// TC:O(n) 均攤下來會是O(1) SC:O(n)
class StockSpanner {
    vector<int> arr;
    stack<int> s;
    int i;
public:
    StockSpanner() {
        i = 0;
    }
    
    int next(int price) {
        arr.push_back(price);
        int res;
        if(s.empty() || arr[s.top()] > arr[i]){
            res = 1;
            s.push(i);
        }
        else{
            while(!s.empty() && arr[s.top()] <= arr[i]){
                s.pop();
            }
            if(!s.empty()){
                res = i-s.top();//x yyy i
            }
            else{
                res = i+1;
            }
            s.push(i);
        }

        i++;
        return res;
    }
};
/*
此題就是求previous smaller or equal
*/
