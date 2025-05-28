
/*
   صل عل محمد
   if (u == Abdel-Aziz Mostafa )   love u <3 ;
  دايما احلم ربنا المنان

*/

#include <bits/stdc++.h>
using namespace std;
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

#define F first
#define S second

/*
         note n is globaly
         FT , data that depend on idx on mo  >> 2 *  n +1 
         sqrt
         idx int Work for query but idx in add ,del .. is time
         each usage of MO set timer =  0 


         Have Updates !!!
              consider the array itself [  ]       , adding value and versa   , answering  from  u  to lc . .. lc to v (to detect the people with odd (path)  first or second appear )
*/

const int N  = 3e5 +7 , sq= 350 , mxlog = 20  ;

vector<int > g[N]  ;
int dp[N][mxlog+5]   , depth[N] , n , Tin[N]  , Tout[N] , FT[N]   ,  timer= 0   ;

void dfs (int nd  , int par){      // prelca call this func
        FT[timer] =  nd ;
        Tin[nd]  =  timer++  ;

        for (auto &ch  : g[nd]) {
                  if(ch ==par)
                         continue ;
                  depth[ch]  =  depth[nd]+1 ;
                  dp[ch][0] = nd;
                  dfs(ch , nd) ;
        }

        FT[timer] =  nd  ;
        Tout[nd]  = timer++  ;
}


int lca (int  u ,  int v) {  // O(logn)

        if (depth[u]   < depth[v])
                  swap( u , v) ;

        for (int  k  =mxlog ; k>=0 ; k--){
                  if (dp[u][k]!=-1 and  depth[dp[u][k]] >=depth[v]){
                           u =  dp[u][k]  ;
                  }
        }

        if (u == v)
               return   u  ;


        for (int  k  =  mxlog ; k>=0 ; k--){
                  if (dp[u][k]!=dp[v][k]){
                           u =dp[u][k] ;
                           v =dp[v][k];
                  }
        }

        return dp[u][0] ;
}

void pre_lca(int root) {
          for (int  i = 1 ; i  <=n ; ++i){
                    for (int k =    0 ; k<=mxlog ; ++k )
                             dp[i][k] = -1  ;
          }

          depth[root] =   0 ;

          dfs(root ,  -1) ;
          for (int  k =1 ; k <=mxlog ; ++k){
                    for (int u = 1 ; u<=n ; ++u){
                             dp[u][k]  = (dp[u][k-1]==-1)  ?  -1  :  dp[dp[u][k-1]][k-1] ;
                    }
          }
}


struct  query  {
       int  l ,  r, idx , lc_case ,lc;  // lc here rep time input of lca i.e FT[lc]   = lca
       bool operator< (query& other)  {
               if(other.l/sq  != l/sq)
                       return    l  < other.l ;
               return  ((l/sq)&1) ?  r > other.r  :  r<other.r;
       }
};

int weight[N]   ;
vector  < int > freq(N)  , INFO(N);

#define  item int
struct MO  {
       int sz , l = 0 , r=-1  , res = 0 ,cnt = 0 /*empty*/;
       vector   <query > qu ;
       vector <int > ans;
       vector < int > cur ;
       vector < int> take;

       MO (int n  , vector <query >  qu) {
               sz = 2*n+5  ;      ///  nodes visited twice
               take.resize(sz+1) ;
               this->qu =  qu ;
               ans.resize(qu.size()) ;
               sort(this->qu.begin() , this->qu.end()) ;
               work() ;
       }


       void add(int idx)   {     /// note this is idx not value
             int nd =  FT[idx] ;
             if (++freq[weight[nd]] ==  1)
                                res++ ;
       }

       void del(int idx)  {
            int nd =  FT[idx] ;
            if (--freq[weight[nd]] == 0)
                                res-- ;
       }

       void push (int idx )  {
             int nd =FT[idx]  ;
             take[nd]^=1 ;
             take[nd]?   add(idx)  : del(idx)  ;
       }

       void pop (int idx)  {
            int nd =  FT[idx] ;
            take[nd]^=1 ;
            take[nd]  ?  add(idx) :  del(idx) ;
       }
       int calc  (int idx) {
             return freq[INFO[idx]];
       }

       void work()  {

              for (auto &[lq,rq , idx , lc_case , lc] : qu) {
                         while(r<rq)      push(++r)  ;
                         while(l > lq)    push(--l) ;
                         while(l  < lq)   pop(l++) ;
                         while(r  > rq)   pop(r--) ;
                         if (!lc_case){
                                  add(lc) ;
                                  ans[idx]  =      calc(idx) ;
                                  del(lc) ;
                         }
                         else  {
                                 ans[idx] =  calc(idx) ;
                         }
              }
       }

       int Query(int idx)  {
             return ans[idx] ;
       }

};

// n is global
void  ICPC ()  {
    int  q  ;
    cin >> n  >>   q ;

    vector < int >  compressed ;

    for (int i =1; i  <=n  ;  ++i) {
             cin>> weight[i] ;

    }

    for (int  i = 0 ; i+1  < n ; ++i)  {
              int  u , v ;
              cin >> u >> v;
              g[u].push_back(v) ;
              g[v].push_back(u) ;
    }

     pre_lca(1) ;


    vector < query >  qu ;

    for (int  i = 0 ; i <q;  ++i)  {
              int  u , v   ,c;
              cin >>  u >> v >> c;

              if (depth[u]  >depth[v])  {
                     swap(u ,  v) ;
              }

              int lc =  lca(u , v)   , l  , r ;

              if (lc ==  u )  {
                        l =   Tin[u]  , r = Tin[v] ;
                        qu.push_back({l , r, i ,1 , Tin[lc]}) ;
              }
              else  {
                        if (Tout[u]  > Tout[v] ) {
                                   swap(u , v) ;
                        }
                        l =  Tout[u]  , r= Tin[v] ;
                        qu.push_back({l , r, i , 0 ,Tin[lc]}) ;

              }
              INFO[i] = c ;

    }

    MO ob(n ,  qu)  ;

    for (int  i = 0 ; i  < q ; ++i)  {
              cout<<(ob.Query(i) ? "Find"  :"NotFind" )<<"\n";
    }

    cout<<"\n";

}


int32_t main(){

     //cout<<"hh\n";


    int tc=1;
    while(tc--)  {
        // cout<<"Case #"<<i++<<": ";
        ICPC() ;
    }


}
/////////////////////////////////////using euler to calc LCA  dont forget to use LG[r-l+1] in mi query//////////////
/*
   صل عل محمد
   if (u == Abdel-Aziz Mostafa )   love u <3 ;
  دايما احلم ربنا المنان

*/

#include <bits/stdc++.h>
using namespace std;
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

#define F first
#define S second

/*
         note n is globaly
         FT , data that depend on idx on mo  >> 2 *  n +1
         sqrt
*/

const int N  = 1e5 +7 , sq= 350 , mxlog = 18 ;

vector <vector  <int  > >  st;
vector<int > g[N]  ;
int    E[2*N+5]  , fst[N]  , indx = -1   ;
int depth[N] , n , Tin[N]  , Tout[N] , FT[2*N+5]   ,  timer= 0   ;

void dfs (int nd  , int par){      // prelca call this func
        FT[timer] =  nd ;
        Tin[nd]  =  timer++  ;
        E[++indx]  =  nd ;
        fst[nd]  =  indx ;

        for (auto &ch  : g[nd]) {
                  if(ch ==par)
                         continue ;
                  depth[ch]  =  depth[nd]+1 ;
                  dfs(ch , nd) ;
                  E[++indx]   =  nd ;
        }

        FT[timer] =  nd  ;
        Tout[nd]  = timer++  ;
}

int calc (int v1 , int v2){
      if (fst[v1]  <=fst[v2])
            return v1;
      return v2;
}


int   mi_query(int  l , int r ){
       int  k   = log2(r-l+1) ;
       return calc(st[l][k]  , st[r-(1<<k)+1][k]) ;
}



void pre   ( int root =1){
       indx =-1 ;

       dfs(root ,-1) ;

       int len =  2* n -1  ;
       for (int  i =   0 ; i  <len ;  ++i){
                 st[i][0]  =  E[i] ;
       }

       for (int k =1 ;  k  <=  mxlog ;  ++k){
                for (int  i  =0 ;  i  + (1 << k) -1  < len  ; ++i){
                           st[i][k]  = calc(st[i][k-1] , st[i +(1 << k-1)][k-1]) ;
                }
       }


}
int lca  (int u  ,int v)  {
     int L  = fst[u]  , R=  fst[v]   ;
     if ( L > R)
          swap( L ,R)  ;
     return mi_query(L , R)  ;


}

struct  query  {
       int  l ,  r, idx , lc_case ,lc;  // lc here rep time input of lca i.e FT[lc]   = lca
       bool operator< (query& other)  {
               if(other.l/sq  != l/sq)
                       return    l  < other.l ;
               return  ((l/sq)&1) ?  r > other.r  :  r<other.r;
       }
};

int weight[N]  ,  freq[N]  , INFO[2*N+1] ,take[N] , ans[2*N];

#define  item int
struct MO  {
        int sz , l = 0 , r=-1  , res = 0 ,cnt = 0 /*empty*/;
        vector   <query > qu ;


       MO (int n  , vector <query >  qu) {
               sz = 2*n+5  ;
               this->qu =  qu ;
               sort(this->qu.begin() , this->qu.end()) ;
               work() ;
       }


       void add(int idx)   {     /// note this is idx not value
             int nd =  FT[idx] ;
             if (++freq[weight[nd]] ==  1)
                                res++ ;
       }

       void del(int idx)  {
            int nd =  FT[idx] ;
            if (--freq[weight[nd]] == 0)
                                res-- ;
       }

       void push (int idx )  {
             int nd =FT[idx]  ;
             take[nd]^=1 ;
             take[nd]?   add(idx)  : del(idx)  ;
       }

       void pop (int idx)  {
            int nd =  FT[idx] ;
            take[nd]^=1 ;
            take[nd]  ?  add(idx) :  del(idx) ;
       }
       int calc  (int idx) {
             return freq[INFO[idx]];
       }

       void work()  {

              for (auto &[lq,rq , idx , lc_case , lc] : qu) {
                         while(r<rq)      push(++r)  ;
                         while(l > lq)    push(--l) ;
                         while(l  < lq)   pop(l++) ;
                         while(r  > rq)   pop(r--) ;
                         if (!lc_case){
                                  add(lc) ;
                                  ans[idx]  =      calc(idx) ;
                                  del(lc) ;
                         }
                         else  {
                                 ans[idx] =  calc(idx) ;
                         }
              }
       }

       int Query(int idx)  {
             return ans[idx] ;
       }

};

// n is global
void  ICPC ()  {
    int  q  ;
   while( cin >> n  >>   q ){


            st= vector  <vector  <int > >  (2*n+1,  vector   < int >  (mxlog+2)) ;

            freq[0] = take[0] =  ans[0] = 0 ;
            for (int i =1; i  <=n  ;  ++i) {
                     cin>> weight[i] ;
                     g[i].clear() ;
                     freq[i] = take[i] =  ans[i] = 0 ;

            }

            for (int  i = 0 ; i+1  < n ; ++i)  {
                      int  u , v ;
                      cin >> u >> v;
                      g[u].push_back(v) ;
                      g[v].push_back(u) ;
            }

            timer= 0  ;
            indx =-1 ;

             pre(1) ;


            vector < query >  qu ;

            for (int  i = 0 ; i <q;  ++i)  {
                      int  u , v   ,c;
                      cin >>  u >> v >> c;

                      if (depth[u]  >depth[v])  {
                             swap(u ,  v) ;
                      }

                      int lc =  lca(u , v)   , l  , r ;

                      if (lc ==  u )  {
                                l =   Tin[u]  , r = Tin[v] ;
                                qu.push_back({l , r, i ,1 , Tin[lc]}) ;
                      }
                      else  {
                                if (Tout[u]  > Tout[v] ) {
                                           swap(u , v) ;
                                }
                                l =  Tout[u]  , r= Tin[v] ;
                                qu.push_back({l , r, i , 0 ,Tin[lc]}) ;

                      }
                      INFO[i] = c ;

            }

            MO ob(n ,  qu)  ;

            for (int  i = 0 ; i  < q ; ++i)  {
                      cout<<(ob.Query(i) ? "Find"  :"NotFind" )<<"\n";
            }

            cout<<"\n";
            //break;
   }
}


int32_t main(){

     //cout<<"hh\n";

     ios_base::sync_with_stdio(0) ;
     cin.tie(0) ;
     cout.tie(0);


    int tc=1;
    while(tc--)  {
        // cout<<"Case #"<<i++<<": ";
        ICPC() ;
    }


}

