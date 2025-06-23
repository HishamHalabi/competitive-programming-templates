struct Node {
     int sz= 0  ,  //how many strings passed by this node
         ends =  0 ;  //  same but ends here
         // u may add other info that will be updated be adding or erasing but note d consider real ends mostly

      unordered_map  <char , int >  ch   ;
     int &operator[] (char c)  {
             return ch[c] ;
     }
};



struct Trie {
    vector <Node > nodes;

    int newNode  ()  {
           nodes.push_back(Node());
           return nodes.size()-1 ;
    }

    Trie() {
            newNode() ;
    }

    void update (string x  ,  int  op)  {
           int  idx  =   0 ;
           for (auto c : x) {   // node[idx] node for path for x[i-1]  , nodes[idx][c] >> idx of next node that stores c
                    if (nodes[idx][c] == 0) {
                        int nd = newNode();
                        nodes[idx][c] = nd;
                    }
                   idx   =  nodes[idx][c]   ;
                   nodes[idx].sz += op ;
           }
           nodes[idx].ends+=op ;
    }

    int cntPrefix(string pat)  {
        int ret = 0  , idx = 0;
        for (auto c  :  pat) {
            if (nodes[idx][c])  {
                idx = nodes[idx][c] ;
            }else return 0  ;
        }
        return nodes[idx].sz ;
    }

    //Mahmoud dont copy this i'll  damage u
    string cur  =  "" ;
    void print (int idx=  0 )   {
         for (int i  = 0 ; i <  nodes[idx].ends ; ++i) cout<<cur<<"\n" ;
         for (char c=  'a'  ;c<='z' ; ++c) {
                   if(nodes[idx][c]) {
                          cur+=c;
                          print(nodes[idx][c]) ;
                          cur.pop_back() ;
                    }
         }
    }

     //how many inserted String l<=s but real not prefix
     int cntLessOrEq (string s)  {
           int ret = 0   , idx =  0 ;
           for (auto c :  s)  {
                    for (auto [ch ,  i] :  nodes[idx].ch)  {
                                 if (ch   < c) ret+= nodes[i].sz  ;
                                 else if(ch == c) ret+=nodes[i].ends;
                    }

                    if (nodes[idx][c] ) {
                        idx = nodes[idx][c];
                    }else    break ;

           }
           return ret;
    }


} ;
