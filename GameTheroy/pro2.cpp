
#include <bits/stdc++.h>
using namespace std;

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;

template<typename T>
using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;


#define F first
#define S second
#define all(v) v.begin(), v.end()

const int N =  31;
vector <vector< int > > divs(N) ;


int a[N][N];
int prefixSum[N][N];
int getSum(int r1,int c1, int r2, int c2) {
    return prefixSum[r2][c2] - prefixSum[r1-1][c2] - prefixSum[r2][c1 - 1] + prefixSum[r1-1][c1-1];
}

int Mex(vector<int> v) {
    int n = v.size() ;
    vector <bool > exist(n)  ;

    for  (int i = 0 ; i  < n ; ++i)if(v[i]  <  n )exist[v[i]] = true ;
    for (int i = 0 ; i  < n ; ++i)  {
        if (!exist[i]) return i ;
    }
    return n  ;
}


int gr[N][N][N][N]   ;
int grundy(int r1 , int c1 , int r2 , int c2) {
    if (r1 == r2 and c1 == c2) return 0;
    if (!getSum(r1, c1, r2, c2)) return 0;

    int &ret = gr[r1][c1][r2][c2];
    if (~ret) return ret;

    vector<int> childs;
    for (int i = r1; i < r2; ++i) {
        int v1 = grundy(r1, c1, i, c2);
        int v2 = grundy(i + 1, c1, r2, c2);
        childs.push_back(v1 ^ v2);
    }

    for (int i = c1; i < c2; ++i) {
         int v1 = grundy(r1, c1, r2, i);
         int v2 = grundy(r1, i+1, r2, c2);
         childs.push_back(v1 ^ v2);
    }

    return ret =Mex(childs) ;
}


void testCases() {
    int n  ;
    cin >> n   ;

    memset(gr , -1 , sizeof gr) ;

    for (int i = 1 ; i  <= n ; ++i) {
             for (int  j =  1;  j  <= n ; ++j)  {
                       cin >>a[i][j] ;
                       if (a[i][j] == 2 ||  a[i][j] ==  3 || a[i][j] ==  5 || a[i][j] == 7) a[i][j] =0;
                       else a[i][j] = 1 ;
             }
    }

    for(int i = 1; i <= n; ++i) {
        for(int j = 1; j <= n; ++j) {
            prefixSum[i][j] = prefixSum[i][j - 1] + a[i][j];
        }
    }

    for(int j = 1; j <= n; ++j) {
        for(int i = 1; i <= n; ++i) {
            prefixSum[i][j] += prefixSum[i-1][j];
        }
    }

    if (grundy(1 , 1 , n , n)) cout <<"First\n" ;
    else cout <<"Second\n" ;




}

int32_t main() {




    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int tc;
    cin >> tc;
    while (tc--) {
        testCases() ;
    }
}
