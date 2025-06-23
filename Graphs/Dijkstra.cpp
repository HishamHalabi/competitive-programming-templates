  priority_queue<pair < int, pair<int , int  > >  ,vector < pair < int, pair<int , int  > > >  , greater<> > pq;
    pq.push({ 0 ,{so , k}})  ;


    while(!pq.empty()) {
        int nd = (pq.top()).S.F ;
        long long  w =  (pq.top()).F ;
        int  rest_k =  (pq.top()).S.S ;
        pq.pop();


        if (calc[nd][rest_k ]  !=inf){

            continue ;
        }


        calc[nd][rest_k]  = w ;

        for (auto &[ch ,we]  : g[nd]) {
            if (w + (we*1LL) <  calc[ch][rest_k])
                 pq.push({w+  get_cost(we ,  0),{ ch , rest_k}}) ;
            if (rest_k and w + (we*1LL)*1LL<calc[ch][rest_k-1])
                 pq.push({w+  get_cost(we , 1)*1LL,{ch  , rest_k-1}}) ;
        }
    }
///////////////////////////////////////////////
class dijkstara{
public : 
vector<vii> adj(sz);
int so,d,so1;
vector<int> dis(sz,-1);
vector<int> p(sz);
void dijkstra (){  //minuimum path at w graph one to one || many to many or ... at any graph (co or not )
    set<pii>  s;
    s.insert({0,so});
    //s.insert({0,so1});   many to many minimum path what ever th source to all nodes
//    dis[so]=0;   dont make this line
    while(!s.empty()){
       pii p =*(s.begin());
       int node=p.second , c_node=p.first;
       s.erase(p);
      if(dis[node]!=-1) continue;
      dis[node]=c_node;
    //  p[node]= p.second .second; construct path but u need pr (w, (node , parent of node)) 
      for (auto &child : adj[node]){
          if (dis[child.first]==-1){
              s.insert({child.second+c_node,child.first});
          }
      }

    }
}

};
/////////////////////////////////faster imle i don't know it good////////////////////////

make sure that dis intialized to largest possible val
 vector<int> dist(1 << n, INT_MAX);
        dist[s] = 0;
        set<pair<int, int>> q = {{0, s}};
        while (!q.empty()) {
            auto [d, v] = *q.begin();
            q.erase(q.begin());
            for (int i = 0; i < m; i++) {
                int to = v & edges[i].first.first;
                to |= edges[i].first.second;
                if (dist[to] > d + edges[i].second) {
                    q.erase({dist[to], to});
                    dist[to] = d + edges[i].second;
                    q.insert({dist[to], to});
                }
            }
        }
        if (dist[0] == INT_MAX) dist[0] = -1;
        cout << dist[0] << '\n';






/////////////////////
