/*
use   int nd = newNode();    nodes[idx][c] = nd;  not !!!!!!!!!! nodes[idx][..] = newNode()
    */

struct Node {
    int sz = 0   ,  ends = 0 ;
    int ch[2]{};

    int &operator[]  (int  i) {
        return ch[i];
    }
};


struct Trie {
    vector <Node > nodes;

    int mxBits  ;
    int newNode  ()  {
        nodes.push_back(Node());
        return nodes.size()-1 ;
    }

    Trie(int mxBits =  31) {
        newNode() ;
        this->mxBits = mxBits;
    }

    void update (int num  ,  int  op)  {
        int idx = 0 ;
        for   (int  i = mxBits ; i >= 0 ; i--) {
            int bit = ((1LL << i )&num) ?1 : 0;
            if (!nodes[idx][bit] {
                
                  int nd = newNode();
                   nodes[idx][c] = nd;
                
            }
            idx = nodes[idx][bit]  ;
            nodes[idx].sz+=op   ;
        }
        nodes[idx].ends+=op ;
    }

    int min_xor(int val)  { //  assuming there are values that u must choose one of them >>  as we walk full path
        int idx= 0 , ret = 0   ;
        for (int i = mxBits ; i>=0 ; --i) {
            int bit = ((1LL << i )&val) ?1 : 0;
            int mv = nodes[idx][bit] ;
            if (nodes[idx][bit] and nodes[mv].sz)  {  // bit^bit
                idx= mv;
            }else   {
                idx = nodes[idx][1-bit] ;
                ret+= (1LL << i ) ;
            }

        }
        return ret ;
    }
    int max_xor(int val)  { //  assuming there are values that u must choose one of them >>  as we walk full path
        int idx= 0 , ret = 0   ;
        for (int i = mxBits ; i>=0 ; --i) {
            int bit = ((1LL << i )&val) ?1 : 0;
            int mv = nodes[idx][1-bit] ;
 
            if (nodes[idx][1-bit] and nodes[mv].sz)  {  // bit^bit
                idx= mv;
                ret+= (1LL << i ) ;
            }else   {
                idx = nodes[idx][bit] ;
            }
 
        }
        return ret ;
    }

} ;



