/*
641. Design Circular Deque
*/

// TC:O(1) SC:O(1000)
class MyCircularDeque {
    int q[1000];
    int k, front, back, len;
    
public:
    MyCircularDeque(int k): k(k), front(0), back(k-1), len(0){}
    
    bool insertFront(int value) {
        if(len == k) return false;
        front = (front == 0) ? k-1 : front-1;
        q[front] = value;
        len ++;
        return true;
    }
    
    bool insertLast(int value) {
        if(len == k) return false;
        back = (back == k-1) ? 0 : back + 1;
        q[back] = value;
        len ++;

        return true;
    }
    
    bool deleteFront() {
        if(len == 0) return false;
        front = (front == k-1) ? 0 : front + 1;
        len --;

        return true;
    }
    
    bool deleteLast() {
        if(len == 0) return false;
        back = (back == 0) ? k-1 : back-1;
        len--;

        return true;
    }
    
    int getFront() {
        return ((len == 0) ? -1 : q[front]);
    }
    
    int getRear() {
        return ((len == 0) ? -1 : q[back]);
    }
    
    bool isEmpty() {
        return len == 0;
    }
    
    bool isFull() {
        return len == k;
    }
};
