// TC:O(nlgn) SC:O(n)
class NumberContainers {
    unordered_map<int, set<int>> nm2idx;
    unordered_map<int,int> idx2nm;
public:
    NumberContainers() {

    }
    
    void change(int index, int number) {
        if(idx2nm.count(index)) {
            int prevNumber = idx2nm[index];
            nm2idx[prevNumber].erase(index);
            if(nm2idx[prevNumber].empty()) nm2idx.erase(prevNumber);
        }
        idx2nm[index] = number;
        nm2idx[number].insert(index);
    }
    
    int find(int number) {
        if(nm2idx.count(number)) return *nm2idx[number].begin();
        return -1;
    }
};

/*
number -> index 可以有很多種
如果被取代了一個 該如何維護下一個
*/

/**
 * Your NumberContainers object will be instantiated and called as such:
 * NumberContainers* obj = new NumberContainers();
 * obj->change(index,number);
 * int param_2 = obj->find(number);
 */
