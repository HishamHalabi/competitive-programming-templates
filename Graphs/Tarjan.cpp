/*
   صل عل محمد
   if (u == Abdel-Aziz Mostafa )   love u <3 ;
  دايما احلم ربنا المنان

*/
#include<bits/stdc++.h>
using namespace std  ;

#define int long long           //TLE
#define F first
#define S second


const int N =  3e5+3;


stack <int >  st;
stack <pair<int,int> >  edges;
int timer  =  0  , m , n ;
int Tin[N] ,   lowlink[N]  ,  instack[N]  , vis[N] , head[N];
vector<vector<int> >  g(N)  ,  comp(N)  ;

/*

   SCC for dir , undir
   
   art , bridges    ,  biconnected for undir

   biconnected commponet >> compenent that they can reach others ... i think


*/

int ans = 0 ;
void bridge (int v , int to){
        ans++ ;
}
void art_point(int u){  // repeated nodes
}


vector<vector<pair<int,int> >> bi_comps (N);
void bi_con(pair<int,int>  e , int nd){
           bi_comps[nd].push_back(e)  ;
}


void tarjan(int nd  , int par  =  -1 /* undirected*/) {

        st.push(nd);
        instack[nd]  = 1;
        vis[nd]  =  1;
        lowlink[nd] = Tin[nd]= timer++;


        int children = 0 ;
        for (auto &ch  :  g[nd]){
                if (ch==par)
                     continue ;

                if (!vis[ch]){

                        edges.push({nd,  ch}) ;
                        tarjan(ch  , nd) ;
                        lowlink[nd] =  min (lowlink[nd]  , lowlink[ch]);

                        if (lowlink[ch]  > Tin[nd])
                                  bridge(nd ,ch);

                        if (lowlink[ch]  >= Tin[nd]){
                                 if (par!=-1)
                                        art_point(nd)  ;

                                 while(edges.top()!=make_pair(nd,ch)){
                                        bi_con(edges.top() , ch) ;
                                       edges.pop();
                                 }
                                 bi_con(edges.top() , ch) ;
                                 edges.pop();


                        }

                       children++;
                }
                else if (instack[ch]){
                    lowlink[nd]   =min(lowlink[nd]  , Tin[ch]) ;
                    edges.push({nd,ch});
                }

        }

        if (par==-1 and children  >1 )
                art_point(nd);

        if (lowlink[nd] ==  Tin[nd]){
                while(st.top()!= nd){
                        comp[nd].push_back(st.top());
                        instack[st.top()] = 0;
                        head[st.top()]   =  nd;
                        st.pop();
                }
                instack[nd] = 0 ;
                comp[nd].push_back(nd) ;
                st.pop();
                head[nd]  =  nd;
        }




}


void SCC() {

        timer= 0 ;
        for (int nd = 0 ; nd <=n  ; ++nd){
                 vis[nd]   =  0 ;
                 comp[nd] .clear() , g[nd].clear() ;
        }
             // input graph

          for (int  i = 0 ; i  < m ;  ++i){
                    int  u  , v  ;
                    cin>> u >>  v;



                    g[u].push_back(v)  ,  g[v].push_back(u);
          }

        for(int  i = 1; i <= n  ; ++i){
                 if (!vis[i])
                        tarjan(i ,-1);
        }


}


vector<vector<int> >  compgraph(){         // consider each comp as a node and connect eedges  on this
        vector<vector<int>  >   res(n+2);
        for (int   u =1  ; u <=n ; ++u)
                   for (auto &v : g[u]){
                              int U =  head[u]   ,  V=head[v] ;     // if u use u this affects loop

                              if(U!=V){
                                      res[U].push_back(V);
                             }

                    }

         return res;

}



void lets_start_as_we_never_failed() {



          cin >>n>>  m ;

          ans  = 0 ;

          SCC();

        cout<<ans<<"\n";

}
// 2 :14
signed main() {

    ios_base::sync_with_stdio(0);
    cin.tie(0);      cout.tie(0);

    int tc ;
    cin>>tc;

    while(tc--)
        lets_start_as_we_never_failed();

}
