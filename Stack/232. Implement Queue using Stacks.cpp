/*
232. Implement Queue using Stacks
tc: o(n) sc:o(n)
*/

ass MyQueue {
    stack<int> s1; // 當隊尾
    stack<int> s2; //當隊頭
public:
    MyQueue() {
        
    }
    
    void push(int x) {
        s1.push(x);
    }
    
    int pop() {//把對頭元素刪除
        peek();//確保s2不為空
        int element = s2.top();
        s2.pop();
        return element;
    }
    
    int peek() {//調用隊頭元素是啥
        if(s2.empty()){
            while(!s1.empty()){
                s2.push(s1.top());
                s1.pop();
            }
        }

        return s2.top();
    }
    
    bool empty() {
        if(s1.empty() && s2.empty())
        return true;
        else return false;
    }
};

//設計兩個stack 讓他們跟queue有一樣的功能
