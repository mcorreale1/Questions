#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct NodeStruct{
    struct NodeStruct* child;
    int value;
};
typedef struct NodeStruct Node;


Node* reverse(Node* head);
void insert(Node* head, int val);
Node* newNode(int val);
int pop(Node* head);
Node* add(Node* h1, Node* h2);
Node* deepCopy(Node* list);

int main(int argc, char** argv) {
    Node* h1 = newNode(3);
    insert(h1, 5);
    insert(h1, 5);
    Node* h2 = newNode(2);
    insert(h2, 1);
    insert(h2, 1);
    int p = 0;
    //printf("%d\n", rev->value);
    //printf("%d %d %d\n", rev->value, rev->child->value, rev->child->child->value);

    Node* added = add(h1, h2);
    /*
    //while((p = pop(added)) != added->value) printf("%d\n", p);
    printf("%d\n", added->child->value);
    */

}

Node* reverse(Node* list) {
    Node* copy = deepCopy(list);
    Node* ret = newNode(pop(copy));
    while(copy->child != NULL)
        insert(ret, pop(copy));
    insert(ret, copy->value);
    //printf("Test 3%d\n", ret->child->child->value);
    return ret;
}
Node* deepCopy(Node* list) {
    Node* curr = list;
    Node* ret = newNode(curr->value);
    while(curr->child) {
        curr = curr->child;
        insert(ret, curr->value);
    }
    return ret;
}

Node* add(Node* h1, Node* h2) {
    Node* c1 = deepCopy(h1);
    Node* c2 = deepCopy(h2);
    Node* raw = NULL;
    int carry = 0;
    while(c1) {
        int p1 = pop(c1);
        int p2 = pop(c2);
        int sum = p1 + p2 + carry;
        printf("p1:%d p2:%d carry:%d sum:%d\n",p1, p2, carry, sum);
        //Check for sum overflow
        if(sum > 9) {
            carry = 1;
            sum = sum % 10;
        } else { 
            carry = 0;
        }

        //Check if list was established and insert
        if(raw == NULL) {
            raw = newNode(sum);
        } else {
           insert(raw, sum);    
        }

        //Check if end
        if(c1->child == NULL) {
            sum = c1->value + c2->value + carry;
            if(sum > 9) {
                insert(raw, sum%10);
                insert(raw, 1);
            } else {
                insert(raw, sum);
            }
            break;
        }
    }
    Node* rev = reverse(raw);
    return rev;
}

Node* newNode(int val) {
    Node* n = malloc(sizeof(Node*));
    n->value = val;
    n->child = NULL;
    return n;
}

int pop(Node* n) {
    if(n == NULL)
        return -1;
    if(n->child == NULL) {
        int ret = n->value; 
        free(n);
        return ret;
    } else if (n->child->child == NULL) {
        int ret = n->child->value;
        n->child = NULL;
        return ret;
    }
    return pop(n->child);
}


void insert(Node* n, int val) {
    if(n->child == NULL) {
        n->child=newNode(val);
        return;
    }
    insert(n->child, val);
}

void delete(Node** n) {
    free(*n);
}
