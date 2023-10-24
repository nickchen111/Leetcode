/*
自己實作linked list
*/

#include<iostream>
using std::cout;
using std::endl;
//用這兩個就好

class LinkedList;

class ListNode{
private:
    // int size;                // size是用來記錄Linked list的長度, 非必要  
    int data;
    ListNode *next;
public:
    ListNode(): data(0),next(0){};
    ListNode(int a): data(a), next(0){};

    friend class LinkedList;
};

class LinkedList{
private:
    ListNode *first;
public:
    LinkedList():first(0){};

    void printList();
    void push_front(int x);
    void push_back(int x);
    void Delete(int x); //這個要用大寫去跟delete做區隔
    void clear();
    void reverse();
};

void LinkedList::printList(){
    //重點：遍歷去印他
    if(first == nullptr) {
        cout << "this is enpty list"<<endl;
        return;
    }

    ListNode *current = first;
    while(current != nullptr){
        cout << current->data<< " ";
        current = current->next;
    }
    cout << endl;
}

void LinkedList::push_front(int x){
    ListNode *newnode = new ListNode(x);
    newnode->next = first;
    first = newnode;
    return;
}

void LinkedList::push_back(int x){
    ListNode *newnode = new ListNode(x);
    if(first == nullptr){
        first = newnode;
        return;
    }

    ListNode *current = first;
    while(current->next != nullptr){
        current = current->next;
    }
    current->next = newnode;
    return;
}

void LinkedList::Delete(int x){
    ListNode *current = first;
    ListNode *previous = nullptr;
    while(current != nullptr && current->data != x){//會跳出的情況為找到 or first為空 or 沒找到後current為空
        previous = current;
        current = current->next;
    }

    if(current == nullptr){
        cout << "there is no" << x << "in list"<<endl;
        return;
    }
    else if(current == first){ // 要刪除的點剛好在開頭
        first = current->next;
        delete current;
        current = nullptr;
        return;
    }
    else{        //其餘情況 list中有想刪除的node
        previous->next = current->next;
        delete current;
        current = nullptr;
        return;
        
    }
}

void LinkedList::clear(){
    while(first != nullptr){   // Traversal
        ListNode *current = first;
        first = first->next;
        delete current;
        current =nullptr;
    }
}

void LinkedList::reverse(){
    if(first == nullptr || first->next == nullptr){
        return;
    }
    //用三指針完成這件事
    ListNode *previous = nullptr;
    ListNode *current = first;
    ListNode *preceding = first->next;

    while(preceding != nullptr){
        current->next = previous; // 把current->next轉向
        previous = current;  // previous往後挪
        current = preceding; // current往後挪
        preceding = preceding->next; // preceding往後挪
    }                                // preceding更新成NULL即跳出while loop

    current->next = previous; // 此時current位於最後一個node, 將current->next轉向
    first = current;     // 更新first為current

}

int main() {

    LinkedList list;     // 建立LinkedList的object
    list.printList();    // 目前list是空的
    list.Delete(4);      // list是空的, 沒有4
    list.push_back(5);   // list: 5
    list.push_back(3);   // list: 5 3
    list.push_front(9);  // list: 9 5 3
    list.printList();    // 印出:  9 5 3
    list.push_back(4);   // list: 9 5 3 4
    list.Delete(9);      // list: 5 3 4
    list.printList();    // 印出:  5 3 4
    list.push_front(8);  // list: 8 5 3 4
    list.printList();    // 印出:  8 5 3 4
    list.reverse();      // list: 4 3 5 8
    list.printList();    // 印出:  4 3 5 8
    list.clear();        // 清空list
    list.printList();    // 印出: List is empty.

    return 0;
}
