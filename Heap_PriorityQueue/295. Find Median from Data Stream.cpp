/*
295. Find Median from Data Stream
*/


// priority_queue
class MedianFinder {
    priority_queue<int, vector<int>, less<int>> left; // max heap
    priority_queue<int, vector<int>, greater<int>> right; // min heap
public:
    MedianFinder() {
        
    }
    
    void addNum(int num) {
        //思考怎麼樣的情況要放入左邊的queue裡
        if(left.empty() || num <= left.top()){
            left.push(num);
        }
        else right.push(num);

        //這兩個queue 在什麼情況需要交換數值 1. left- right 超過2 2. right太多 大於left
        if(right.size() > left.size()){
            left.push(right.top());
            right.pop();
        }
        else if(left.size() - right.size() == 2){
            right.push(left.top());
            left.pop();
        }
    }
    
    double findMedian() {
        if(left.size() > right.size()){
            return static_cast<double>(left.top());
            
        }
        else {
            return static_cast<double>(left.top() + right.top())/2;
        }
    }
};


// muitiset
class MedianFinder {
    double result;
    multiset<int> set;
    multiset<int>::iterator iter;
public:
    MedianFinder() {
        
    }
    
    void addNum(int num) {
        set.insert(num);
        if(set.size() == 1) {
            iter = set.begin();
            result = *iter;
            return;
        }

        //原來偶數 後來加入變奇數
        if(set.size() % 2 == 1){ // ooxooo  x為iter指向位置
            if(num >= *iter){
                iter = next(iter, 1);
                result = *iter;
            }
            else { 
                result = *iter;
            }
        }
        //原來奇數 後來偶數    ooxoo
        else if(set.size()%2==0){
            if(num >= *iter){
                result = *iter*0.5 + *next(iter,1)*0.5;
            }

            else {
                iter = prev(iter,1);
                result = *iter*0.5 + *next(iter,1)*0.5;

            }
        }
    }
    
    double findMedian() {
        return result;
    }
};


 /*
 此題數據量龐大 因此最好插入刪除都可以在lgn完成 
 找到中位數最好是o(1)
 兩個方法
 1. two priority queue-> min heap max heap  
 tc: o(lgn) sc:o(1)
 2. multiset 
 set可自動幫你排好序  不容忍重複元素
 multiset 自動排序 可容忍重複元素
  tc: o(lgn) sc:o(1)
 */
