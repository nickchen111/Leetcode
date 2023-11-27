/*
1825. Finding MK Average
*/


// TC:O(nlgn) SC:O(n)
class MKAverage {
    //此題必須用三個set 因為還需要超過m個之後刪掉元素
    multiset<int> left,mid,right;
    long sum = 0;
    int m,k;
    queue<int> q;
public:
    MKAverage(int m, int k) {
        this->m = m;
        this->k = k;
    }
    void shiftLeft(multiset<int>& A,multiset<int>& B){
        A.insert(*B.begin());
        B.erase(B.begin());
    }
    void shiftRight(multiset<int>& A,multiset<int>& B){
        B.insert(*A.rbegin());
        A.erase(--A.end());
    }
    
    void addElement(int num) {
        if(q.size() < m){
            q.push(num);//需要紀錄哪些是最老的元素
            sum+=num;
            mid.insert(num);

            if(q.size() == m){
                while(left.size() < k){
                    sum-=*mid.begin();
                    shiftLeft(left,mid);//往左移
                }

                while(right.size() < k){
                    sum-=*mid.rbegin();
                    shiftRight(mid,right);
                }
            }
        }
        else if(q.size() == m){
            //看要加在哪裡
            q.push(num);
            if(!left.empty() && *left.rbegin() >= num){
                left.insert(num);
            }
            else if(!right.empty() && *right.begin() <= num){
                right.insert(num);
            }
            else{
                mid.insert(num);
                sum+=num;
            }

            if(left.size() > k){
                sum+=*left.rbegin();
                shiftRight(left,mid);
            }
            if(right.size() > k){
                sum+=*right.begin();
                shiftLeft(mid,right);
            }

            //delete old element
            int x = q.front();
            q.pop();
            if(left.find(x) != left.end()){
                left.erase(left.find(x));
            }
            else if(right.find(x) != right.end()){
                right.erase(right.find(x));
            }
            else {
                mid.erase(mid.find(x));
                sum-=x;
            }

            if(left.size() < k){
                sum-=*mid.begin();
                shiftLeft(left,mid);
            }
            if(right.size() < k){
                sum-=*mid.rbegin();
                shiftRight(mid,right);
            }

        }
    }
    
    int calculateMKAverage() {
        if(q.size() < m) return -1;
        
        return sum/(m-2*k);
    }
};
