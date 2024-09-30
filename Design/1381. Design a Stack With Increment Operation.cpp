/*
1381. Design a Stack With Increment Operation
*/

// TC:O(n) SC:O(n)
class CustomStack {
    vector<int> arr;
    int idx;
public:
    CustomStack(int maxSize) {
        arr.resize(maxSize);
        idx = 0;
    }
    
    void push(int x) {
        if(idx == arr.size()) return;
        arr[idx] = x;
        idx += 1;
    }
    
    int pop() {
        if(idx == 0) return -1;
        int tmp = arr[idx-1];
        idx -= 1;

        return tmp;
    }
    
    void increment(int k, int val) {
        for(int i = 0; i < min(k, idx); i++){
            arr[i] += val;
        }
    }
};

/**
 * Your CustomStack object will be instantiated and called as such:
 * CustomStack* obj = new CustomStack(maxSize);
 * obj->push(x);
 * int param_2 = obj->pop();
 * obj->increment(k,val);
 */
