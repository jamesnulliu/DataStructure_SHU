#include<iostream>
using namespace std;

const int maxx = 100000;
int n, m, p, q, f[maxx], e[maxx];
char c;

int find(int x)
{
    if (x != f[x])
        f[x] = find(f[x]);
    return f[x];
}

void mix(int x, int y)
{
    int f1 = find(x);
    int f2 = find(y);
    f[f1] = f2;
}

//int main()
//{
//    cin >> n >> m;
//    for (int i = 1; i <= n; i++)
//        f[i] = i;
//    for (int i = 1; i <= m; i++) {
//        cin >> c >> p >> q;
//        if (c == 'F')
//            mix(p, q);
//        else {
//            if (e[p] == 0) e[p] = find(q);
//            else
//                mix(e[p], q);
//            if (e[q] == 0) e[q] = find(p);
//            else
//                mix(e[q], p);
//        }
//    }
//    int ans = 0;
//    for (int i = 1; i <= n; i++)
//        if (f[i] == i)
//            ans++;
//    cout << ans;
//    return 0;
//}