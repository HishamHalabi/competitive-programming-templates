
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


#define F first
#define S second
#define all(v) v.begin(), v.end()
#define int long long


const int N =  3e5 +  7 , M =  20 ;
vector < int >  removed(N)    , sz(N)   ,  g[N] ,  centroid[N] , parentCen(N) ;

void update_sz(int nd   , int par)  {
    sz[nd]  =   1;
    for(auto ch   : g[nd])  {
             if(ch ==  par ||  removed[ch])  continue   ;
             update_sz(ch , nd)  ;
             sz[nd]+=sz[ch] ;
    }
}

//imagine removed[ch]  >> fake edge btw (nd , ch)
int getCentroid  (int nd , int pr , int total) {
     for (auto ch  :  g[nd]) {
               if (ch ==  pr ||  removed[ch]) continue ;
               if (sz[ch]*2  >  total)
                          return getCentroid(ch  ,  nd , total) ;
     }
     return nd ;
}


int cnt[1<<M]  , value[N] ;

void add_info(int nd  ,  int  par  , int path_mask) {
       path_mask^= value[nd] ;
       cnt[path_mask] ++ ;

       for (auto ch  :  g[nd])  {
                if (removed[ch]  ||  ch ==  par) continue ;
                add_info(ch , nd , path_mask) ;
       }
}

void del_info(int nd  ,  int  par  , int path_mask) {
       path_mask^= value[nd] ;
       cnt[path_mask] --  ;
       for (auto ch  :  g[nd])  {
                if (removed[ch]  ||  ch ==  par) continue ;
                del_info(ch , nd , path_mask) ;
       }
}


vector  <int > ansMe(N) ,  ansfromUp(N) ;
int get(int nd    , int pr , int msk)  {
      msk^=value[nd] ;
      int ret = 0 ;
      for (int i = -1 ; i  < M ; ++i) ret+= cnt[msk ^      (~i ?  (1<<i)  :  0 )] ;

      for (auto ch  : g[nd])  {
                if (ch ==  pr ||  removed[ch]) continue ;
                ret+= get(ch  , nd , msk) ;
      }
      ansfromUp[nd]+= ret ;
      return ret;
}


//note not all parent in function cALLS ARE TRUE BUT REMOVED HANDLE IT
/*
       in centroid tree  :  if LCA(u , v)   = lc  >>>  real path pass by lc
                             note2  :  any path from subtree of curCen to any node up from cent in real pass by this

       considering paths overall  >> enough to consider what pass from nd to it's sub  or two nodes in dif childs
       considering paths for pass by node  >>  consider this example and note 2  ( it's about calcing your normal paths   , adding them to childs assoicate with)
*/
void decompose  (int nd , int pr_cen = -1)  {

    /*
         state  :  i have  tree  >> start from nd as root considering only real edges  now this your tree before any new modifications

    */

     update_sz(nd  , nd) ;
     nd  =    getCentroid(nd   , nd   , sz[nd])  ;
     /*
            rotate tree at cen which we store again at node
            save info from cen (nd) to all vertices in the real subtree and answer queries if needed hre

     */



     add_info(nd , nd , 0  ) ;
     ansMe[nd]  =  1 ;    //picking yourself
     for (int  i = -1 ; i  < M ; ++i) ansMe[nd]  += cnt[~i?(1<<i) :  0] ;   //path from nd to u  in it's subtree

     //cen to u and consider valid  paths (nd to v)
     int add  = 0 ;
     for (auto ch  : g[nd]) {
               if (removed[ch])  continue ;
               del_info(ch , nd ,  value[nd])  ;
               add+= get(ch , nd  , 0) ;
               add_info(ch  , nd , value[nd]) ;
     }
     ansMe[nd]+=add ;

     del_info(nd , nd , 0 ) ;

     //get centroid  , delete edges (became fake edges) >> removed[nd] = 1;
     removed[nd] = 1 ;
     if (~pr_cen)  {
             centroid[pr_cen].push_back(nd)  ;
     }
     parentCen[nd] = pr_cen ;
     for (auto ch  : g[nd]) {
               if (removed[ch])  continue ;
               decompose(ch ,  nd) ;
     }
}


void testCases() {
    int n;
    cin >> n;
    for (int i = 0; i < n - 1; ++i) {
        int u, v;
        cin >> u >> v;
        u--, v--;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    for (int i = 0; i < n; ++i) {
        char c;
        cin >> c;
        value[i] = 1 << (c - 'a');
    }
    decompose(0, 0);
    for (int i = 0; i < n; ++i) {
        cout << ansMe[i]/2 + ansfromUp[i] << " ";
    }


}




int32_t main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

//    train() ;

    int tc = 1;
   // cin >> tc;
    while (tc--) {
        testCases();
    }
}
