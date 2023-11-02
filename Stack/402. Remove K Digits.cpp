/*
402. Remove K Digits
*/

// TC:O(n) SC:O(n)
class Solution {
public:
    string removeKdigits(string num, int k) {
        int n = num.size();
        stack<int> s;
        int count = 0;
        string res;
        for(int i = 0; i<n; i++){
            while(!s.empty() && num[s.top()] > num[i] && count < k){
                count+=1;
                res.pop_back();
                s.pop();
            }
            
            res+=num[i];
            s.push(i);
        }

        while(count < k){
            res.pop_back();
            count+=1;
        }

        while(res[0] == '0'){
            res = res.substr(1);
        }

        return res == "" ? "0":res;
    }
};


// TC: O(n+ nlgn) SC:O(n)
class Solution {
public:
    string removeKdigits(string num, int k) {
        int n = num.size();
        if(k >= n) return "0";
   
        stack<char> s;
        int count = 0;//紀錄已經pop幾次了

        //一樣的單調遞增棧套路 這次的題目概念是從前面看到後面
        for(int i = 0; i < n; i++){
            //當出現非單調遞增的狀況時
            while(!s.empty() && s.top() > num[i] && count < k){
                s.pop();
                count++;
            }
            s.push(num[i]);
        } 

        for(int i = 0; i < k-count; i++){//代表數組本身原本就是單調遞增的 or 沒有刪除完
            s.pop();
        }

        
        string ans;
        while(!s.empty()){
            ans += s.top();
            s.pop();
        }

        //考慮尾巴為0的情況 等會倒過來會變成字首有0
        while(ans.size()>0 && ans.back() == '0'){ //如果没有ans.size*()检查，当字符串为空时，ans.back() 的行为是未定义的
            ans.pop_back(); // string 也可以用vector容器的操作
        }

        while(ans == "") return "0";//如果結果都是00000 在前面就會被刪光光

        reverse(ans.begin(), ans.end());
        
        return ans;

    }
};


/*
解題思路：
解决原题的直观思路是寻找一个尽可能小的递增序列，但要满足位数的要求。
这是栈的典型应用。利用栈维护一个递增序列。当遍历的元素小于栈顶元素时，
就不断退栈直至 Stack.top()<num[i]，这样继续加入元素后仍然是一个递增序列。

需要注意的几点：
需要一个计数器count来记录退栈的数目。只有当count<k时，才进行退栈操作（即模拟删除）。
都把所有元素都遍历结束后，如果发现仍然count<k，那么就把Stack末尾的弹出，直至count==k
需要去除结果里的前导零。
*/
