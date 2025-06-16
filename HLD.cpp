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

//dont GO For HLD before think LCA , ..
/*
   dealing with edges will be same but
       make node keep info of it's (pr ..nd) edge 
       when reaching case  u , v and u is lca make u down so don't take edge of parent  
              if (Head[u]  ==  Head[v])  {     //one is LCA
                         if(depth[u]  > depth[v])  swap(u , v) ;
                         res.push_back({Tin[u]+1 ,  Tin[v]}) ; 
                         return res ;
      }
*/

#define item int
struct segtree{
    vector<item> val;

    int sz =1;
    segtree(int n){
        while(sz<n)sz*=2;
        val.resize(2*sz);
    }

    item  NEUTRAl_ElEMENT = 0    ;
    item merge(item& m1 ,item& m2 , int x=-1){
          return max(m1, m2) ;
    }
    item single(int v){
        return v ;
    }
    void Set(int i  ,int v,int x , int lx  ,int rx){
        if (rx-lx==1){
            val[x] =  single(v) ;
            return  ;
        }
        int md  = (lx+rx)/2;
        if (i<md)
            Set(i  ,v ,  2*x+1 ,lx, md);
        else
            Set(i , v, 2*x+2 , md  , rx);

        val[x] =merge(val[2*x+1] ,val[2*x+2], x) ;
    }
    void Set(int i  ,int v){
        Set(i , v,  0 , 0 ,sz);
    }
    item calc(int  l , int r , int x , int lx , int rx ){
          if (lx>=r ||rx<=l)
            return NEUTRAl_ElEMENT;
          if (lx>=l and rx<=r){
            return val[x];
          }
          int md  = (lx+rx)/2;
          item c1 =calc(l ,r  ,2*x+1  , lx  , md)  ,
          c2 =calc(l ,r  ,2*x+2  ,md  , rx) ;
        return merge(c1 ,
             c2);


    }
    int calc(int l , int r   ){
        return calc(l,r  , 0 , 0,sz);
    }


};

struct  HLD {


    vector  <int > a ,info  ;
    segtree sg  ;
    vector  <int >  Big , sz , par , Tin  , Head , depth;
    vector < vector  <int > > g ;

    void pre(int nd) {         //big childs ,sz
         sz[nd]  = 1;
         for (auto &ch  :g[nd])  {
                   if (ch == par[nd]) continue ;

                   par[ch] = nd ;
                   depth[ch]   =  depth[nd]+1;
                   pre(ch) ;
                   sz[nd]+=sz[ch] ;

                   if (Big[nd] ==  0   ||  sz[ch]>sz[Big[nd]]) {
                              Big[nd] = ch ;
                   }
         }
    }


    int timer  = 0 ;                      //visiting big first and flat tree
    void flatten(int nd)  {
         Tin[nd] = timer++  ;
         a[Tin[nd]] =  info[nd] ;
         if (Big[nd]) {
                    Head[Big[nd]] =  Head[nd] ;
                    flatten(Big[nd]) ;

         }

         for (auto &ch  : g[nd]) {
                   if (ch ==  par[nd]  ||  ch ==  Big[nd]) continue ;
                   Head[ch] = ch ;
                   flatten(ch) ;
         }
    }

    HLD (int n , vector  <int >  info ,  vector  < vector  <int >   > & g)  : sg(n+1), Big(n+1), sz(n+1), par(n+1), Tin(n+1), Head(n+1), depth(n+1), a(n+1) {

         this->g =  g;
         this->info = info ;
         pre(1) ;

         Head[1] = 1;
         flatten(1) ;

         //Range Quries
         for  (int  i = 0 ; i  <  n  ;  ++i)  {
                    sg.Set(i ,  a[i])  ;
         }



    }

vector < pair <int, int > > path  (int  u , int v  , bool query_of_type_nodes)  {
          vector < pair < int, int >  > res ;
          while(true)  {

                  if (Head[u]  ==  Head[v])  {     //one is LCA
                         if(depth[u]  > depth[v])  swap(u , v) ;
                         if (query_of_type_nodes)res.push_back({Tin[u] ,  Tin[v]}) ;
                         else  res.push_back({Tin[u]+1 ,  Tin[v]}) ;
                         return res ;
                  }

                  //assume v is the one that's not on the comp of LCA
                  if (depth[Head[u]]  >  depth[Head[v]]) swap( u , v) ;
                  res.push_back({Tin[Head[v]] ,  Tin[v]}) ;
                  v = par[Head[v]] ;
          }
    }


    vector <vector  <int > >   getOrderdPath( int u , int v , int  k )  {   // segs orderd by apperance in u >>  v path
           vector < pair < int,int > > segs =  path(u , v  , 1 )   ;

           map < int  , int > st ;       //log(log)
           for (auto[ l ,r ] : segs)   st[r] = l  ;



           int cur = Tin[u]  , lf = 0 ;
           deque < pair< int , int >   > lft ,  rght    ;
           vector <pair < int, int > > ret;

           while((lft.size()    +rght.size())  != segs.size()) {

                        if(st.find(cur)==st.end()) {
                                  lf  = 1;
                                  cur =  Tin[v] ;
                        }

                        if (!lf) lft.push_back({st[cur], cur})  ;
                        else rght.push_front({st[cur],  cur}) ;


                        cur =st[cur]  ;
                        int  u =  nds[cur] ;
                        if  (par[u])  cur = Tin[par[u]]  ;
                        else cur   = -1 ;
           }

           for (auto pr  :  lft)   ret.push_back(pr) ;
           for (auto pr  :  rght)   ret.push_back(pr) ;
           //return ret;
          
        
         return ret; 

    }


    void change (int u , int val)  {
           int idx =  Tin[u] ;
           a[idx] =  val ;
           sg.Set(idx , val) ;
    }


    //answering queryis know imagine u have array a  for nodes by same order we follow here
    //for path (u , v) i'll give u some L , R on this array merge this segs

    //app;y for ex  segtree on array and u can use it's internal merge to merge your segs
    // u can do segtree for each heavy path as opt
    int query (int   u  ,int  v )  {

           vector < pair < int,int > > segs =  path(u , v   ,1 )   ;

           item ret   =  0 ;
           for (auto [l  , r]   : segs)  {
                     item rett =  sg.calc( l , r+1) ;
                     ret = sg.merge(ret ,  rett) ;
           }
           return ret;
    }

};


void testCases() {
    int  n  , q;
    cin >> n  >> q;

    vector < int > info(n+1)   ;
    for (int  i =1; i <=n ;  ++i)  {
              cin >>  info[i] ;
    }

    vector <vector  <int >>  g(n+1) ;
    for (int  i = 0 ; i+1 < n ; ++i) {
              int  u  , v ;
              cin >> u >> v;
              g[u].push_back(v) ;
              g[v].push_back(u) ;
    }


    HLD H(n ,   info  , g) ;

    for (int i = 0 ; i<q ;++i) {
             int  k   , u  ,v  ;
             cin >> k >>  u >> v;

             if (k == 1) {
                    H.change(u , v) ;
             }else cout<<H.query(u , v) <<" ";
    }
    cout<<"\n";



}

int32_t main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);



    int tc = 1;
   // cin >> tc;
    while (tc--) {
        testCases();
    }
}
