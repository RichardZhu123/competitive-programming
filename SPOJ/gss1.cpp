
#include <bits/stdc++.h>

#define MAXN 50004

using namespace std;

struct node {
    int lsum, rsum, total, ans;

    node() {}

    node(node l, node r) {
        lsum = max(l.lsum, l.total + r.lsum);
        rsum = max(l.rsum + r.total, r.rsum);
        total = l.total + r.total;
        ans = max(lsum, rsum);
        ans = max(ans, max(l.ans, r.ans));
        ans = max(ans, l.rsum + r.lsum);
    }

    void print() {
        printf("sums: %d, %d, total: %d, ans = %d\n\n", lsum, rsum, total, ans);
    }
} T[MAXN * 4];

int N, Q, A[MAXN];

void build(int idx, int left, int right) {
    if (left == right) {
        T[idx].total = T[idx].lsum = T[idx].rsum = T[idx].ans = A[left];
        return;
    }

    int mid = (left + right) / 2;
    build(idx * 2, left, mid);
    build(idx * 2 + 1, mid + 1, right);

    T[idx].lsum = max(T[idx * 2].lsum, T[idx * 2].total + T[idx * 2 + 1].lsum);
    T[idx].rsum = max(T[idx * 2].rsum + T[idx * 2 + 1].total, T[idx * 2 + 1].rsum);
    T[idx].total = T[idx * 2].total + T[idx * 2 + 1].total;
    T[idx].ans = max(T[idx].lsum, T[idx].rsum);
    T[idx].ans = max(T[idx].ans, max(T[idx * 2].ans, T[idx * 2 + 1].ans));
    T[idx].ans = max(T[idx].ans, T[idx * 2].rsum + T[idx * 2 + 1].lsum);
}

node query(int idx, int left, int right, int qleft, int qright) {
    if (qleft <= left && qright >= right) return T[idx];

    int mid = (left + right) / 2;

    if (qright <= mid) {
        return query(idx * 2, left, mid, qleft, qright);
    } else if (qleft > mid) {
        return query(idx * 2 + 1, mid + 1, right, qleft, qright);
    } else {
        return node(query(idx * 2, left, mid, qleft, qright), query(idx * 2 + 1, mid + 1, right, qleft, qright));
    }
}

int main() {
    scanf("%d", &N);
    for (int i = 0; i < N; i++) scanf("%d", &A[i]);

    build(1, 0, N - 1);

    scanf("%d", &Q);
    for (int i = 0, l, r; i < Q; i++) {
        scanf("%d%d", &l, &r);
        l--, r--;

        printf("%d\n", query(1, 0, N - 1, l, r).ans);
    }
}
