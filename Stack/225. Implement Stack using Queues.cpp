/*
225. Implement Stack using Queues
tc: o(n) sc:o(n)
*/

class MyStack {
    queue<int> q;
    int top_element;
public:
    MyStack() {
        
    }
    
    void push(int x) {
        q.push(x);
        top_element = x;
    }
    
    int pop() {
        int size = q.size();
        while(size > 2){
            q.push(q.front());
            q.pop();
            size--;
        }

        top_element = q.front();
        q.pop();
        q.push(top_element);
        int temp = q.front();
        q.pop();

        return temp;
    }
    
    int top() {
        return top_element;
    }
    
    bool empty() {
        return q.empty();
    }
};
