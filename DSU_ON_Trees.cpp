

/*+
                 The trivial Small to large trick basicly for each node include infoOF subtree nodes and u have this only chance to answer your queryies , DS[nd] only change when it's father its cacled either
                 it's the right info
*/
#include <bits/stdc++.h>
using namespace std;

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;

template<typename T>
using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

#define int long long
#define F first
#define S second
#define all(v) v.begin(), v.end()

const int N = 3e5 + 7, mod = 1e9 + 7 , m = mod  , inf = -2e16;


int n ;
set<int > DS[N] ;    //info of sub of node
vector  <int> g[N]  , color(N) , ans(N);

//queries of node
void answer(int nd) {
      ans[nd] =  DS[nd].size() ;
}

void dfs(int nd  , int par)  {

     //ND insertion
     DS[nd].insert(color[nd]) ;
     for (auto ch :  g[nd]) {
               if (ch==par)  {
                      continue ;
               }

               dfs(ch , nd) ;
               if (DS[ch].size()    > DS[nd].size()) {
                        swap(DS[ch]  , DS[nd]) ;
               }

               //merge with ch
               for (auto col  : DS[ch]) {
                         DS[nd].insert(col) ;
               }
     }

     answer(nd)  ;
}


void testCases() {
     cin >> n ;
     for (int  i = 1 ; i <= n ; ++i) {
               cin >> color[i];
     }

     for (int  i = 0 ; i+1  < n;  ++i) {
               int  u , v;
               cin >> u >> v;
               g[u].push_back(v) ;
               g[v].push_back(u) ;
     }

     dfs(1, -1)  ;

     for(int   i =1; i <=n ; ++i)cout<<ans[i] <<" " ;
     cout<<"\n";
}

int32_t main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);



    int tc = 1;
    //cin >> tc;
    while (tc--) {
        testCases();
    }
}



