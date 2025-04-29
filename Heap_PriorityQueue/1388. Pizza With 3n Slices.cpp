// TC:O(nlgn) SC:O(n)
class Solution {
    struct Node {
        int value;
        Node *prev, *next;
        bool deleted;
        Node(int v) : value(v), prev(nullptr), next(nullptr), deleted(false) {}
    };
    struct Cmp {
        bool operator()(const Node* a, const Node* b) const {
            return a->value < b->value;
        }
    };

    void deleteNode(Node* node) {
        node->prev->next = node->next;
        node->next->prev = node->prev;
        node->deleted = true;
    }

public:
    int maxSizeSlices(vector<int>& slices) {
        int n = slices.size();
        if (n == 0) return 0;
        vector<Node*> nodes(n);
        for (int i = 0; i < n; i++) {
            nodes[i] = new Node(slices[i]);
        }
        for (int i = 0; i < n; i++) {
            nodes[i]->next = nodes[(i + 1) % n];
            nodes[i]->prev = nodes[(i - 1 + n) % n];
        }
    
        priority_queue<Node*, vector<Node*>, Cmp> pq;
        for (auto p : nodes) {
            pq.push(p);
        }
        
        int pickCount = n / 3;
        int result = 0;
        while (pickCount--) {
            while (!pq.empty() && pq.top()->deleted) {
                pq.pop();
            }
            Node* cur = pq.top();
            pq.pop();
            result += cur->value;
            cur->value = cur->prev->value + cur->next->value - cur->value;
            pq.push(cur);
            deleteNode(cur->prev);
            deleteNode(cur->next);
        }
        // for (auto p : nodes) {
        //     delete p;
        // }
        return result;
    }
};
