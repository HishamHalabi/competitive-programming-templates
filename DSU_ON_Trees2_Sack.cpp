/*+
    صل على محمد
    if (u == Abdel-Aziz Mostafa )  love u <3 ;
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

/*
          basicly we have one DS that all use   , i add my sub tree  , ans , remove it  >> this  solve same prolems as simple trick
          but only optimize data that use (escape from logs ..)

          logic
               sort chs based on sz
               leave last one
                     for ch take empty DS  , work , clear , back
                     the last work  , keep
               add other childs

               clear myself

        //complexity :  add   o(nlog) del ... delete what added  (listen to 1.20...30 from CP Circus)

*/

int n ;
int mx = 0 ;
vector <int > DS_F1(N)  , Big(N)  , DS_F2(N)  , color(N);
vector  <int> g[N]  , sz(N) ,  ans(N);

void pre(int nd , int par) {
     sz[nd] = 1;
     for (auto ch :  g[nd]) {
               if (ch ==  par)continue ;
               pre(ch ,nd) ;
               sz[nd]+=sz[ch] ;
               if (sz[ch]  >  sz[Big[nd]]) {
                         Big[nd] = ch;
               }
     }
}

void add(int nd   , int p)  { // add this sub tree info to DS
     //nd add
     int c = color[nd] ;
     if (DS_F2[DS_F1[c]]) DS_F2[DS_F1[c]]-=c ;
     DS_F1[c] ++ ;
     DS_F2[DS_F1[c]]+=c;
     if (DS_F1[c]  >  mx)  {
               mx++ ;
     }
     //
     for (auto ch  : g[nd]) {
               if (ch!=p) add(ch  ,nd) ;
     }
}


void del(int nd , int  p) {

     int c = color[nd] ;
     if (DS_F2[DS_F1[c]])DS_F2[DS_F1[c]]-=c ;
     DS_F1[c] -- ;
     DS_F2[DS_F1[c]]+=c;

     if (DS_F2[mx]  == 0)  {
               mx-- ;
     }

     for (auto ch  : g[nd]) {
               if (ch!=p) del(ch  , nd) ;
     }
}



//queries of node
void answer(int nd) {
   ans[nd]  =DS_F2[mx] ;
}


void dfs(int nd  , int par , bool keep)  {

     for (auto ch :  g[nd]) {
               if (ch==par ||  ch ==  Big[nd])  {
                      continue ;
               }
               dfs(ch , nd , false) ;
     }

     if (Big[nd]) {
            dfs(Big[nd] ,  nd , true);
     }

     //add nd info

      int c = color[nd] ;
          if (DS_F2[DS_F1[c]]) DS_F2[DS_F1[c]]-=c ;
     DS_F1[c] ++ ;
     DS_F2[DS_F1[c]]+=c;
     if (DS_F1[c]  >  mx)  {
               mx++ ;
     }


     //add childs info
     for (auto  ch : g[nd]) {
               if (ch==par ||  ch ==  Big[nd])  {
                      continue ;
               }
               add(ch , nd) ;
     }

     answer(nd)  ;
     if (!keep)  {
             del(nd , par) ;
     }
}


void testCases() {
    int n  ;
    cin >> n ;

    for(int  i =1; i<=n  ; ++i)cin>>color[i] ;

    for(int  i = 0 ; i+1  < n ; ++i) {
             int  u , v ;
             cin >> u >> v ;
             g[u].push_back(v) ;
             g[v].push_back(u) ;
    }

    pre(1, -1 ) ;
    dfs(1, -1 , 1) ;
    for (int  i =1 ; i <=n ;  ++i)cout<<ans[i] <<" ";
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


