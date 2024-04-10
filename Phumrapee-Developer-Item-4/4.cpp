#include <iostream>
#include <algorithm>

using namespace std;

typedef struct _People {
    int s;
    int e;
    int k;
    struct _People *next;
} People;

typedef People *NodePtr;

void addQueue(NodePtr *head, int s, int e, int k) {
    NodePtr newPeople = (NodePtr)malloc(sizeof(People));
    newPeople->s = s;
    newPeople->e = e;
    newPeople->k = k;
    newPeople->next = NULL;

    if (*head == NULL) {
        *head = newPeople;
        return;
    } 

    if (k < (*head)->k) {
        newPeople->next = *head;
        *head = newPeople;
        return;
    }

    NodePtr current = *head;
    for (; current->next != 0; current = current->next) {
        if (k >= current->k && k < (current->next)->k) {
            newPeople->next = current->next;
            current->next = newPeople;
            return;
        }
    }

    current->next = newPeople;
}

int main() {
    int m, t, s, n;
    cin >> m >> t >> s >> n;

    NodePtr init = NULL;
    
    for (int i = 0; i < n; i++) {
        int s, e, k;
        cin >> s >> e >> k;
        addQueue(&init, s, e, k);
    }

    int remaining = 0;
    int round = 0;
    int timeSpent = 0;
    int endQueue[m] = {0};

    for (int i = 1; ; i++) {
        if (init == NULL) break;
        if (remaining < m) {
            for (int j = remaining; j < m; j++) {
                if (init != NULL) {
                    endQueue[j] = init->e;
                    remaining++;
                    init = init->next;
                } else {
                    break;
                }
            }
        }

        for (int j = 0; j < m; j++) {
            sort(endQueue, endQueue+m, greater<int>());
            if (endQueue[j] == i) {
                endQueue[j] = 0;
                remaining--;
            }
        }

        if (i == s) {
            i = 0;
            round+=2;
            timeSpent += t*(s-1);
        } else {
            timeSpent += t;
        }
    }

    cout << round << " " << timeSpent << endl;

    return 0;
}