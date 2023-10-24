/*
155. Min Stack
*/


class MinStack {
    stack<int> s;
    stack<int> minS;//維護一個單調遞減棧
public:
    MinStack() {
        
    }
    
    void push(int val) {
        if(minS.empty() || val <= minS.top()){
            minS.push(val);
        }
        s.push(val);
    }
    
    void pop() {
        if(minS.top() == s.top()){
            minS.pop();
        }
        s.pop();
    }
    
    int top() {
        return s.top();
    }
    
    int getMin() {
        return minS.top();
    }
};
