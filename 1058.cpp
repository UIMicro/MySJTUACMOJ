#include <iostream>
#include <cstdio>
using namespace std;

namespace LIST
{
    size_t size = 0;

    struct NODE {
        int val;
        NODE* next;
    };

    NODE* head = nullptr;
    int len = 0;

    void init() {
        // TODO
    }
    NODE* move(int i) {
        return nullptr;
    }
    void insert(int i, int x) {
        if (size == 0) {
            head = new NODE;
            head->next = head;
            head->val = x;
            ++size;
        }
        else {
            if (i == 0) {
                NODE* bef_head = head, * tmp = head;
                head = new NODE;
                head->next = tmp;
                head->val = x;
                while (tmp->next != bef_head) {
                    tmp = tmp->next;
                }
                tmp->next = head;
            }
            else {
                NODE* n = head;
                while (i-- > 1) n = n->next;
                NODE* tmp = new NODE;
                tmp->next = n->next;
                tmp->val = x;
                n->next = tmp;
            }
            ++size;
        }
    }
    void remove(int i) {
        if (i == 0) {
            if (size == 1) {
                delete head;
                head = nullptr;
            }
            else {
                NODE* tmp = head, *tmp1 = head;
                head = head->next;
                while (tmp1->next != tmp) tmp1 = tmp1->next;
                tmp1->next = head;
                delete tmp;
            }
        }
        else {
            NODE* tmp = head;
            while (i-- > 1) tmp = tmp->next;
            NODE* tmp1 = tmp->next;
            tmp->next = tmp->next->next;
            delete tmp1;
        }
        --size;
    }
    void remove_insert(int i) {
        int x;
        if (i == 0) {
            if (size == 1) {
                x = head->val;
                delete head;
                head = nullptr;
            }
            else {
                NODE* tmp = head, * tmp1 = head;
                head = head->next;
                while (tmp1->next != tmp) tmp1 = tmp1->next;
                tmp1->next = head;
                x = tmp->val;
                delete tmp;
            }
        }
        else {
            NODE* tmp = head;
            while (i-- > 1) tmp = tmp->next;
            NODE* tmp1 = tmp->next;
            tmp->next = tmp->next->next;
            x = tmp1->val;
            delete tmp1;
        }
        --size;
        insert(size, x);
    }
    void get_length() {
        cout << size << endl;
    }
    void query(int i) {
        if (i >= size) {
            cout << -1 << endl;
            return;
        }
        NODE* tmp = head;
        while (i-- > 0) tmp = tmp->next;
        cout << tmp->val << endl;
    }
    void get_max() {
        if (size == 0) {
            cout << -1 << endl;
            return;
        }
        int max = head->val;
        NODE* tmp = head;
        while (tmp->next != head) {
            tmp = tmp->next;
            if (tmp->val > max) max = tmp->val;
        }
        cout << max << endl;
    }
    void clear() {
        if (head == nullptr) return;
        NODE* tmp = head, *tmp1;
        while (tmp->next != head) {
            tmp1 = tmp->next;
            delete tmp;
            tmp = tmp1;
        }
        delete tmp;
        size = 0;
    }

}
int n;
int main()
{
    cin >> n;
    int op, x, p;
    LIST::init();
    for (int _ = 0; _ < n; ++_)
    {

        cin >> op;
        switch (op) {
        case 0:
            LIST::get_length();
            break;
        case 1:
            cin >> p >> x;
            LIST::insert(p, x);
            break;
        case 2:
            cin >> p;
            LIST::query(p);
            break;
        case 3:
            cin >> p;
            LIST::remove(p);
            break;
        case 4:
            cin >> p;
            LIST::remove_insert(p);
            break;
        case 5:
            LIST::get_max();
            break;
        }
    }
    LIST::clear();
    return 0;
}