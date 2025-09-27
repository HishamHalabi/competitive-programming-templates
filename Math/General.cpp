
///geotrical sequence           ////////////////////
sum =  a*(1 - r^n)   / (1-r)  
/////////mathmetical sequecne ///////////////
sum   = n/2(a1  + an)
////////////////////////////catlan Numbres // 
any balanced segence of len N > > full 01 tree of n+1 leafes and vice versa
n places >> max n-1 blancd segqunces

////////////////////////
The Catalan number  
$C_n$  is the solution for

Number of correct bracket sequence consisting of   
$n$  opening and  
$n$  closing brackets.     >> with n+1 places
The number of rooted full binary trees with  
$n + 1$  leaves (vertices are not numbered). A rooted binary tree is full if every vertex has either two children or no children.
The number of ways to completely parenthesize  
$n + 1$  factors.
The number of triangulations of a convex polygon with  
$n + 2$  sides (i.e. the number of partitions of polygon into disjoint triangles by using the diagonals).
The number of ways to connect the  
$2n$  points on a circle to form  
$n$  disjoint chords.
The number of non-isomorphic full binary trees with  
$n$  internal nodes (i.e. nodes having at least one son).
The number of monotonic lattice paths from point  
$(0, 0)$  to point  
$(n, n)$  in a square lattice of size  
$n \times n$ , which do not pass above the main diagonal (i.e. connecting  
$(0, 0)$  to  
$(n, n)$ ).
Number of permutations of length  
$n$  that can be stack sorted (i.e. it can be shown that the rearrangement is stack sorted if and only if there is no such index  
$i < j < k$ , such that  
$a_k < a_i < a_j$  ).
The number of non-crossing partitions of a set of  
$n$  elements.
The number of ways to cover the ladder  
$1 \ldots n$  using  
$n$  rectangles (The ladder consists of  
$n$  columns, where  
$i^{th}$  column has a height  
$i$ ).

int Cat(int n) { // nCr(2*n,n) / (n+1)
    return (long long) nCr(2 * n, n) * mod_inv(n+1) %mod; 
}

/////////////////////////////////////////////
////////////////////Pascal Triangle/////////////////////////////////////
a[r][col] =  RcCol            0baesed

Pascal triangle  diagnoals represent prefix of prefix .....

1 1 1 1 
1 2 3 4
1 3 6 10
1 4 .... 
>>
     1
   1  1
  1 2  1
 1 3 3  1
1 4 6 4  1

//////////////////////////////Fibonaci//////////////////////
Example: x6
x6 =  
(1.618034...)6 − (1−1.618034...)6
√5
 

When I used a calculator on this (only entering the Golden Ratio to 6 decimal places) I got the answer 8.00000033 , a more accurate calculation would be closer to 8.

Try n=12 and see what you get.
