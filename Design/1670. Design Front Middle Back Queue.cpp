/*
1670. Design Front Middle Back Queue
*/

// TC:O(1) SC:O(n)
class FrontMiddleBackQueue {
    list<int> List;
    list<int>::iterator mid;
    int n;
public:
    FrontMiddleBackQueue() {
        n = 0;
    }
    
    void pushFront(int val) {
        List.push_front(val);
        //如果原本是奇數個多加一個mid要往前移一位
        if(n == 0){
            mid = List.begin();
        }
        else if(n%2 == 1){
            mid = prev(mid);
        }
        n++;
    }
    
    void pushMiddle(int val) {
        
        if(n == 0){
            List.push_back(val);
            mid = List.begin();
        }
        else if(n%2 == 0){
            List.insert(next(mid),val);
            mid = next(mid); // O O X O O 
        }
        else {
            List.insert(mid,val);//O O X O O O 
            mid = prev(mid);
        }
        n++;
    }
    
    void pushBack(int val) {
        List.push_back(val);
        if(n == 0){
            mid = List.begin();
        }
        else if(n%2 == 0){
            mid = next(mid);
        }
        n++;
    }
    
    int popFront() {
        if(List.empty()) return -1;
        int res=List.front();
        if(n%2 == 0){
            mid = next(mid);//O O O O 
        }
        List.erase(List.begin());
        n--;
        return res;
    }
    
    int popMiddle() {
        if(List.empty()) return -1;
        int res = *mid;
        auto mid_new = mid;
        if(n%2 == 0){
            // O O O O
            mid_new = next(mid);
        }
        else if(n%2 == 1){
            // O O O 
            mid_new = prev(mid);
        }
        List.erase(mid);
        n--;
        mid = mid_new;
        return res;
    }
    
    int popBack() {
        if(List.empty()) return -1;
        int res = List.back();
        if(n%2 == 1){
            // O O 
            mid = prev(mid);
        }
        List.pop_back();
        n--;
        return res;
    }
};
