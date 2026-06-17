#include <bits/stdc++.h>
using namespace std;


#include <algorithm>
#define int long long
#define ld long  double
typedef ld T;
typedef complex < T>  pt ;
#define x real()
#define y imag()
const ld EPS = 1e-6 ;
/*
  ideas
   pararellel  >> same slope
   get angles from sides  >>a^2 + b^2 - 2*abcos   = c^2

*/

/*
 >>use atan2

# asin(x): inverse sine
# Domain: [-1, 1]
# Range: [-π/2, π/2]   # returns angles between -90° and 90°

# acos(x): inverse cosine
# Domain: [-1, 1]
# Range: [0, π]        # returns angles between 0° and 180°

# atan(x): inverse tangent          >> tan(o) = -tan(180-o)  =  -tan(360-o)
//only know ratio  so angle is angle or (360 -  angle)
# Domain: (-∞, ∞)
# Range: (-π/2, π/2)   # returns angles between -90° and 90°, not including ±90°

atan2(y ,  x)
>> know the exact angle from x axis
>>range [-pi  .. pi]
*/


const ld M_PI= 3.14159265358979323846;

/*
 *(x2-x1)^2  +  (y2 -  y1)^2  = r1
 *(x2-x0)^2  +  (y2 -  y0)^2  = r0
 * x2*(x1+x0)  * 2   -  y2*(y1+y0) *2 =r1-r0   -(x1^2   + y1^2+x0^2  + y1^2)
 *
 *
 *
 *   (x2-x1)  * (x0-x1)  +  (y2 - y1) * (y0-y1)  =  cross
 *
 *
 *       (x0-x1)  * x2    +(y0-y1) * y2    = cross  + x1 * (x0  - x1)  +  y1 * (y0  - y1)
 *        x2*(x1+x0)  * 2   -  y2*(y1+y0) *2 =r1-r0   -(x1^2   + y1^2+x0^2  + y1^2)
 *
 */

int sgn(T val )  {
   if (val  >EPS) return 1 ;
   if(val < -EPS)  return -1;
   return  0 ;
}

int quarter(pt p) {
   if (sgn(p.x)  ==  1) {
             return sgn(p.y) >  0  ? 1: 4;
   }
   return sgn(p.y )  >  0  ? 2:3;
}


//magin^2  || |V|^2
T sq (pt  p)  {
    return p.x*p.x  +  p.y  *  p.y;
}


//|v|   * |w| * cos(O)
//cos(x) =  cos(360  - x)
T dot (pt v ,  pt w)  {
     return v.x  * w.x +  v.y *w.y;
}

//|v|   * |w| * sin(O)
//sin(x) =  -sin(360  - x)  >> sin(O)    = sin(180 - O)
T cross  (pt v , pt w) {
      return v.x   * w.y   - v.y   * w.x ;
}



bool isPrep (pt v , pt w)  {
      return sgn(cross(v,  w))   == 0;
}

pt prep(pt p){
    return {-p.y, p.x};
}


//-----------------------------------------
pt translate (pt v , pt w)  {
   return {v.x + w.x , v.y  + w.y} ;
}

pt scale(pt v , T sc)  {
    return {v.x*sc ,  v.y  *sc}  ;
}


pt rot(pt p, pt c, ld a){
    pt v = p - c;
    pt rotate = {cos(a), sin(a)};
    return c + rotate * v;
}

pt linearTransfo(pt p, pt q, pt r, pt fp, pt fq) {
    return fp + (r-p) * (fq-fp) / (q-p);
}
//----------------------------------
//ab   ,  ac   >>  cross btw them
T orient (pt a , pt b , pt c)  {
        return cross(b-a  ,  c-a);
}



//get the angle from 0  to pi >> postive angle || one of the two possible
T angle(pt v , pt w) {
    T a1   = atan2(w.y, w.x);
    T a2   = atan2(v.y, v.x);
    T ang =   fabs(a1 -a2)  ;
    return ang =  min(ang    , 2*M_PI  - ang) ;

    /*
     *  T c = dot(v,w)/(abs(v)*abs(w));  //more errors
      c = max((T)-1.0,min((T)1.0,c));
      return acos(c);
*/

}

//u need angle from ba  to ca  >> dot gives u 2 choices >> based on direction pick the right one
//returns postive angle   , neg O  = 360 - O  >> [0....2*pi]
T orientedAngle(pt a , pt b , pt c)  {
   T ang = angle(b-a , c-a) ;

   if(sgn(orient(a , b, c)) ==1)  {
             return ang;
   }
   return 2*M_PI -  ang;
}

//ang deg   , len : dis from origin
//ang from 0axis to the vector
pair < T, T > getPoint(T ang  ,  T len)
{
        if (ang  < 0 )
               ang  = 2 * M_PI  + ang   ;
        T dot = len  *  cos(ang) ;
        T cross =  len  * sin(ang);
        T x1 = dot ;
        T y1 =cross;
        return {x1  , y1} ;
}

//same as above but it's like giving -O here and 360-O above
T angleTravelled(pt a, pt b, pt c){ //exact angle +=[0...pi]
    T ampli = angle(b - a, c - a);
    if(orient(a, b, c) > 0) return ampli;
    else return -ampli;
}


T angleFromX(pt p1) { //exact
    pt org(0 , 0) ;
    pt p2(3 , 0) ;
    T angle =  orientedAngle(org , p2 , p1) ;
    if (fabs(angle - 2*M_PI) <=EPS)angle = 0 ;
    return angle ;
}


//if p is in angle from ba to  ca
bool inAngle (pt a , pt b , pt c , pt p)  {
    T abc = orient( a , b ,  c) ;
    T abp = orient(a, b,p) , acp = orient(a,c,p) ;
    if(abc  < 0)swap(abp , acp) ;
    if (abp>=0  and acp <=0)   {
           return true;
    }
    return false;
}

bool half(pt p) { // true if in blue half
    assert(p.x != 0 || p.y != 0); // the argument of (0,0) is undefined
    return p.y > 0 || (p.y == 0 && p.x < 0);
}

//sort points according how is smaller angle from x axis
void polarSort(vector<pt> &v) {
    sort(v.begin(), v.end(), [](pt v, pt w) {
         return make_tuple(half(v), 0) <
          make_tuple(half(w), cross(v,w));
    });
}

/*
  line >> from point p  to point q
    ----------------------------------
    ax +  by   =  c
    vector on line from left (a,b)
    vector of line  (b,-a)

    (a,b) dot (x,y) = c = ax+by  even point not on line
    (b,  -a) cross (x,y) = c    = ax+by  >> even for point not on line
   ------------------------------------
   positve side is wacking from the end of line to left
   negative is to the right

   to check
    ax+by  - real c > 0 pos , <0 neg ,
    fun fact abs((ax+ by - c) / |v|)  distance from the point to the line

    multipying vector of line by another vector   = ax+by  for the the line containg point moving from line by this vector

    for same line  a,b,c are unique if a are same i.e make a =1 ,divide b/a ,c/a now this unique for this line
    for parrallel a,b are unique with same method as above
    but note using b as unique  ,  b,c   >> this will not be valid when a = 0   >> i think we can make a = EPS or -EPS
    but anyway for integer cordinates  >>a ,b,c are int and u can divide by gc and make a pos and (a,b,c) unique line  , (a,b)  un parrallel
   ------------------------------------
*/
struct line{
    pt v; T c;

    line(pt v, T c) : v(v), c(c) {}

    // from equation ax+by = c
    line(T a, T b, T _c){
        v = {-b, a};
        c = _c;
    }

    //line from two points
    line(pt p, pt q){
        v = q - p;
        c = cross(v, p);
    }

    T side(pt p) {return cross(v,p)-c;}
    ld dist(pt p) {return abs(side(p)) / abs(v);}
    double sqDist(pt p) {return side(p)*side(p) / (T)sq(v);}

    //getting line that's perp with me and pass by point p
    line prepThrought(pt p){
        return {p, p + prep(v)};
    }

    //which point appears in line first
    bool cmpProj(pt p, pt q){
        return dot(v, p) < dot(v, q);
    }

    //translaing line by vector t >> the idea that v of new line is same  , we only need the new c
    line translate(pt t) {
        return {v, c + cross(v,t)};
    }


    line shiftLeft(T dist) {
        return {v, c + dist*abs(v)};
    }

    pt proj(pt p) {
        return p - prep(v)*side(p)/sq(v);
    }

    pt refl(pt p) {
        return p - prep(v) * (T)2.0 * side(p)/sq(v);
    }
};

bool inter(line l1, line l2, pt &out) {
        T d = cross(l1.v, l2.v);
        if (d == 0) return false;
        out = (l2.v*l1.c - l1.v*l2.c) / d; // requires floating-point coordinates
        return true;
}

//line that divide angle btw 2 lines equaly >> line divide in same direction is interior =1  , else  = 0 or vice i dont rem
line bisector(line l1, line l2, bool interior){
    T cr = cross(l1.v, l2.v);

    if (fabs(cr) < EPS)
        throw runtime_error("Parallel lines");

    T n1 = abs(l1.v);
    T n2 = abs(l2.v);

    T s = interior ? 1 : -1;

    pt A = l2.v / n2 + (l1.v / n1) * s;

    T C = l2.c / n2 + (l1.c / n1) * s;

    return line(A, C);
}

//////////////////Segments/////////////////////

////////////////circle with a-b
bool inDisk(pt a, pt b, pt p) {
    return dot(a-p, b-p) <= EPS;
}

bool onSegment(pt a, pt b, pt c){
    return orient(a, b, c) == 0 && inDisk(a, b, c);
}


//get the unique intersection btw 2 lines
bool properInter(pt a, pt b, pt c, pt d, pt &out) {
    T oa = orient(c,d,a),
            ob = orient(c,d,b),
            oc = orient(a,b,c),
            od = orient(a,b,d);
// Proper intersection exists iff opposite signs
    if (sgn(oa)*sgn(ob) < 0 && sgn(oc)*sgn(od) < 0) {
        out = (a*ob - b*oa) / (ob-oa);
        return true;
    }
    return false;
}

//as two ss may have range of intersections
set<pair<ld,ld>> inters(pt a, pt b, pt c, pt d) {
    set<pair<ld,ld>> s;
    pt out;
    if(a == c || a == d){
        s.insert(make_pair(a.x, a.y));
    }
    if(b == c || b == d){
        s.insert(make_pair(b.x, b.y));
    }
    if(s.size()) return s;

    if (properInter(a,b,c,d,out)) return {make_pair(out.x, out.y)};
    if (onSegment(c,d,a)) s.insert(make_pair(a.x, a.y));
    if (onSegment(c,d,b)) s.insert(make_pair(b.x, b.y));
    if (onSegment(a,b,c)) s.insert(make_pair(c.x, c.y));
    if (onSegment(a,b,d)) s.insert(make_pair(d.x, d.y));

    return s;
}

ld segPoint(pt a, pt b, pt p) {
    if (a != b) {
        line l(a,b);
        if (l.cmpProj(a,p) && l.cmpProj(p,b)) // if closest to projection
            return l.dist(p); // output distance to line
    }
    return min(abs(p-a), abs(p-b)); // otherwise distance to A or B
}

//distance from seg to seg [enough to pick one of endpoints
ld segSeg(pt a, pt b, pt c, pt d) {
    pt dummy;
    if (properInter(a,b,c,d,dummy))
        return 0;
    return min({segPoint(a,b,c), segPoint(a,b,d),
                segPoint(c,d,a), segPoint(c,d,b)});
}

bool above(pt a, pt p) {
    return p.y >= a.y;
}
// check if [PQ] crosses ray from A
//read it from book , but so far it checks intersection from one side of line  (making it always above)
bool crossesRay(pt a, pt p, pt q) {
    return (above(a,q)- above(a,p)) * orient(a,p,q) > 0;
}
//check if point projection is on ray
bool pointOnRay(ld X, ld Y, ld a, ld b, ld c, ld d){
    pt p(X,Y), A(a,b), B(c,d);
    return dot(p-A, B-A) >= -EPS;
}
//point dist to ray
T  pointRay(ld X,  ld Y , ld a , ld b , ld c, ld d) {
      line l({a,b}  , {c ,d}) ;
     pt p(X,Y) ;
     pt proj = l.proj(p) ;

     bool out =
        ((c != a && (proj.x - a) * (c - a) < -EPS)) ||
        ((d != b && (proj.y - b) * (d - b) < -EPS));
     if ( out )   {
           ld dx = (X -a) , dy = (Y -b);
           ld dist = sqrt(dx* dx + dy * dy);
           return dist ;
     }else return l.dist(p)  ;
}

bool pointOnRay(pt p, pt a, pt b){
    return dot(p-a, b-a) >= -EPS;
}

bool collinearRays(pt a, pt b, pt c, pt d){
    return fabsl(orient(a,b,c)) < EPS &&
           fabsl(orient(a,b,d)) < EPS;
}
//distance
ld rayRay(pt a, pt b, pt c, pt d){
    line l1(a,b), l2(c,d);

    // parallel
    if(fabsl(cross(l1.v,l2.v)) < EPS){

        // different lines
        if(!collinearRays(a,b,c,d))
            return min(pointRay(c.x,c.y,a.x,a.y,b.x,b.y),
                       pointRay(a.x,a.y,c.x,c.y,d.x,d.y));

        // same supporting line
        if(pointOnRay(c,a,b) || pointOnRay(a,c,d))
            return 0;

        return min(abs(a-c), abs(a-d));
    }

    // non-parallel
    pt p;
    inter(l1,l2,p);

    if(pointOnRay(p,a,b) && pointOnRay(p,c,d))
        return 0;

    return min(pointRay(c.x,c.y,a.x,a.y,b.x,b.y),
               pointRay(a.x,a.y,c.x,c.y,d.x,d.y));
}
//////////////////////////////////////////  CIRCLES   //////////////////////////////////////////
 
pair<pt, T> circumCircle(pt a, pt b, pt c) {
    b = b-a, c = c-a; // consider coordinates relative to A
    assert(cross(b,c) != 0); // no circumcircle if A,B,C aligned
    return {a + perp(b*sq(c) - c*sq(b))/cross(b,c)/(T)2, abs(perp(b*sq(c) - c*sq(b))/cross(b,c)/(T)2)};
}
 //circle line inters
int circleLine(pt o, double r, line l, pair<pt,pt> &out) {
    double h2 = r*r - l.sqDist(o);
    if (h2 >= 0) { // the line touches the circle
        pt p = l.proj(o); // point P
        pt h = l.v* (T)(sqrt(h2)/abs(l.v)); // vector parallel to l, of length h
        out = {p-h, p+h};
    }
    return 1 + sgn(h2);
}

//intersection
int circleCircle(pt o1, T r1, pt o2, T r2, pair<pt,pt> &out) {
    pt d=o2-o1; T d2=sq(d);
    if (d2 == 0) {assert(r1 != r2); return 0;} // concentric circles
    T pd = (d2 + r1*r1 - r2*r2)/2; // = |O_1P| * d
    T h2 = r1*r1 - pd*pd/d2; // = hˆ2
    if (h2 >= 0) {
        pt p = o1 + d*pd/d2, h = perp(d)*sqrt(h2/d2);
        out = {p-h, p+h};
    }
    return 1 + sgn(h2);
}

//tangent points to 2 circles  (if u need  point and circle make r =  0 )
int tangents(pt o1, T r1, pt o2, T r2, bool inner, vector<pair<pt,pt>> &out) {
    if (inner) r2 = -r2;
    pt d = o2-o1;
    T dr = r1-r2, d2 = sq(d), h2 = d2-dr*dr;
    if (d2 == 0 || h2 < 0) {assert(h2 != 0); return 0;}
    for (T sign : {-1,1}) {
        pt v = (d*dr + perp(d)*sqrt(h2)*sign)/d2;
        out.push_back({o1 + v*r1, o2 + v*r2});
    }
    return 1 + (h2 > 0);
}

//////////////////////////////////////PolyGons//////////////////////////////////////
ld areaPolygon(vector<pt> p) {
    ld area = 0.0;
    for (int i = 0, n = p.size(); i < n; i++) {
        area += cross(p[i], p[(i+1)%n]); // wrap back to 0 if i == n - 1
    }
    return abs(area) / 2.0;
}

bool isConvex(vector<pt> p) {
    bool hasPos=false, hasNeg=false;
    for (int i=0, n=p.size(); i<n; i++) {
        int o = orient(p[i], p[(i+1)%n], p[(i+2)%n]);
        if (o > 0) hasPos = true;
        if (o < 0) hasNeg = true;
    }
    return !(hasPos && hasNeg);
}
 
ld areaTriangle(pt a, pt b, pt c) {
    return abs(cross(b-a, c-a)) / 2.0;
}
 
ld areaPolygon(vector<pt> p) {
    ld area = 0.0;
    for (int i = 0, n = p.size(); i < n; i++) {
        area += cross(p[i], p[(i+1)%n]); // wrap back to 0 if i == n - 1
    }
    return abs(area) / 2.0;
}
 
// true if P at least as high as A
bool above(pt a, pt p) {
    return p.y >= a.y;
}
 
// if strict, returns false when A is on the boundary O(n)  (convex or not convex)
bool inPolygon(vector<pt> p, pt a, bool strict = true) {
    int numCrossings = 0;
    for (int i = 0, n = p.size(); i < n; i++) {
        if (onSegment(p[i], p[(i+1)%n], a))
            return !strict;
        numCrossings += crossesRay(a, p[i], p[(i+1)%n]);
    }
    return numCrossings & 1; // inside if odd number of crossings
}
// maximum distance from a convex polygon to another convex polygon
double maximum_dist_from_polygon_to_polygon(vector<PT> &u, vector<PT> &v){ //O(n)
    int n = (int)u.size(), m = (int)v.size();
    double ans = 0;
    if (n < 3 || m < 3) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) ans = max(ans, dist2(u[i], v[j]));
        }
        return sqrt(ans);
    }
    if (u[0].x > v[0].x) swap(n, m), swap(u, v);
    int i = 0, j = 0, step = n + m + 10;
    while (j + 1 < m && v[j].x < v[j + 1].x) j++ ;
    while (step--) {
        if (cross(u[(i + 1)%n] - u[i], v[(j + 1)%m] - v[j]) >= 0) j = (j + 1) % m;
        else i = (i + 1) % n;
        ans = max(ans, dist2(u[i], v[j]));
    }
    return sqrt(ans);
}
////////////////////////////////mostly here about convex///////////////////////////////////////////
bool cw(pt a, pt b, pt c, bool include_collinear) {
    int o = sgn(orient(a, b, c));
    return o < 0 || (include_collinear && o == 0);
}

bool collinear(pt a, pt b, pt c) { return sgn(orient(a, b, c)) == 0; }

//O(nlog)    >> min area convex shape ,  min perim so far
//input  : random ordered points  ,  ouput   : counter clock wise
void convex_hull(vector<pt>& a, bool include_collinear = false) {
    pt p0 = *min_element(a.begin(), a.end(), [](pt a, pt b) {
        return make_pair(a.y, a.x) < make_pair(b.y, b.x);
    });
    sort(a.begin(), a.end(), [&p0](const pt& a, const pt& b) {
        int o = sgn(orient(p0, a, b));
        if (o == 0)
            return (p0.x-a.x)*(p0.x-a.x) + (p0.y-a.y)*(p0.y-a.y)
                   < (p0.x-b.x)*(p0.x-b.x) + (p0.y-b.y)*(p0.y-b.y);
        return o < 0;
    });
    if (include_collinear) {
        int i = (int)a.size()-1;
        while (i >= 0 && collinear(p0, a[i], a.back())) i--;
        reverse(a.begin()+i+1, a.end());
    }

    vector<pt> st;
    for (int i = 0; i < (int)a.size(); i++) {
        while (st.size() > 1 && !cw(st[st.size()-2], st.back(), a[i], include_collinear))
            st.pop_back();
        if(st.empty() || a[i] != st.back())
            st.push_back(a[i]);
    }

    if (include_collinear == false && st.size() == 2 && st[0] == st[1])
        st.pop_back();

    a = st;
}



//////////////////////////////////////////////////////////////////////////////////////////////
//reorder counter clock wise
void reorder_polygon(vector<pt> & P){
    size_t pos = 0;
    for(size_t i = 1; i < P.size(); i++){
        if(P[i].y < P[pos].y || (P[i].y == P[pos].y && P[i].x < P[pos].x))
            pos = i;
    }
    rotate(P.begin(), P.begin() + pos, P.end());
}

//p must be counter clockwise
//polygon out from summing eacy two points from  p ,q where p ,q are convex and  ouput will be convex hull
//in  : ccw  , out : ccw
vector<pt> minkowski(vector<pt> P, vector<pt> Q){
    // the first vertex must be the lowest
    reorder_polygon(P);
    reorder_polygon(Q);
    // we must ensure cyclic indexing
    P.push_back(P[0]);
    P.push_back(P[1]);
    Q.push_back(Q[0]);
    Q.push_back(Q[1]);
    // main part
    vector<pt> result;
    size_t i = 0, j = 0;
    while(i < P.size() - 2 || j < Q.size() - 2){
        result.push_back(P[i] + Q[j]);
        auto cross = (P[i + 1] - P[i]).cross(Q[j + 1] - Q[j]);
        if(cross >= 0 && i < P.size() - 2)
            ++i;
        if(cross <= 0 && j < Q.size() - 2)
            ++j;
    }
    return result;
}

//////////////////////////////////////////////////////////////////////////////////////////////

// Basic half-plane struct.
struct Halfplane {

    // 'p' is a passing point of the line and 'pq' is the direction vector of the line.
    pt p, pq;
    long double angle;

    Halfplane() {}
    Halfplane(const pt& a, const pt& b) : p(a), pq(b - a) {
        angle = atan2l(pq.y, pq.x);
    }

    // Check if point 'r' is outside this half-plane.
    // Every half-plane allows the region to the LEFT of its line.
    bool out(const pt& r) {
        return cross(pq, r - p) < -EPS;
    }

    // Comparator for sorting.
    bool operator < (const Halfplane& e) const {
        return angle < e.angle;
    }

    // Intersection point of the lines of two half-planes. It is assumed they're never parallel.
    friend pt inter(const Halfplane& s, const Halfplane& t) {
        long double alpha = cross((t.p - s.p), t.pq) / cross(s.pq, t.pq);
        return s.p + (s.pq * alpha);
    }
};


vector<pt> hp_intersect(vector<Halfplane>& H) {
    const int inf = 1e9;
    pt box[4] = {  // Bounding box in CCW order
            pt(inf, inf),
            pt(-inf, inf),
            pt(-inf, -inf),
            pt(inf, -inf)
    };

    for(int i = 0; i<4; i++) { // Add bounding box half-planes.
        Halfplane aux(box[i], box[(i+1) % 4]);
        H.push_back(aux);
    }

    // Sort by angle and start algorithm
    sort(H.begin(), H.end());
    deque<Halfplane> dq;
    int len = 0;
    for(int i = 0; i < int(H.size()); i++) {

        // Remove from the back of the deque while last half-plane is redundant
        while (len > 1 && H[i].out(inter(dq[len-1], dq[len-2]))) {
            dq.pop_back();
            --len;
        }

        // Remove from the front of the deque while first half-plane is redundant
        while (len > 1 && H[i].out(inter(dq[0], dq[1]))) {
            dq.pop_front();
            --len;
        }

        // Special case check: Parallel half-planes
        if (len > 0 && fabsl(cross(H[i].pq, dq[len-1].pq)) < EPS) {
            // Opposite parallel half-planes that ended up checked against each other.
            if (dot(H[i].pq, dq[len-1].pq) < 0.0)
                return vector<pt>();

            // Same direction half-plane: keep only the leftmost half-plane.
            if (H[i].out(dq[len-1].p)) {
                dq.pop_back();
                --len;
            }
            else continue;
        }

        // Add new half-plane
        dq.push_back(H[i]);
        ++len;
    }

    // Final cleanup: Check half-planes at the front against the back and vice-versa
    while (len > 2 && dq[0].out(inter(dq[len-1], dq[len-2]))) {
        dq.pop_back();
        --len;
    }

    while (len > 2 && dq[len-1].out(inter(dq[0], dq[1]))) {
        dq.pop_front();
        --len;
    }

    // Report empty intersection if necessary
    if (len < 3) return vector<pt>();

    // Reconstruct the convex polygon from the remaining half-planes.
    vector<pt> ret(len);
    for(int i = 0; i+1 < len; i++) {
        ret[i] = inter(dq[i], dq[i+1]);
    }
    ret.back() = inter(dq[len-1], dq[0]);
    return ret;
}
////////////////////////////////////////////////////////////////////////////////////////

vector<pair<int, int>> all_anti_podal(int n, vector<pt> &p) {
    vector<pair<int, int>> result;

    auto nx = [&](int i){return (i+1)%n;};
    auto pv = [&](int i){return (i-1+n)%n;};

    // parallel edges should't be visited twice
    vector<bool> vis(n, false);

    for (int p1 = 0, p2 = 0; p1 < n; ++p1) {
        // the edge that we are going to consider in this iteration
        // the datatype is Point, but it acts as a vector
        pt base = p[nx(p1)] - p[p1];

        // the last condition makes sure that the cross products don't have the same sign
        while (p2 == p1 || p2 == nx(p1) || sgn(cross(base, p[nx(p2)] - p[p2])) == sgn(cross(base, p[p2] - p[pv(p2)]))) {
            p2 = nx(p2);
        }

        if (vis[p1]) continue;
        vis[p1] = true;

        result.push_back({p1, p2});
        result.push_back({nx(p1), p2});

        // if both edges from p1 and p2 are parallel to each other
        if (sgn(cross(base, p[nx(p2)] - p[p2])) == 0) {
            result.push_back({p1, nx(p2)});
            result.push_back({nx(p1), nx(p2)});
            vis[p2] = true;
        }
    }

    return result;
}


/////////////////////////////////////////////////////////////////////////////

void testCase() {
      T a,  b;
      cin >> a>> b;

      T c = sqrt(a *  a    +  b*b) ;

      T B =  asin(b  / c);
      T A =  asin(  a   / c);
    //  cout <<A<<" "<<B<<"\n";


      for  (int xx=  1  ; xx<=1000 ;  ++xx) {
         for  (int  yy   =  1 ; yy<=1000 ; ++yy ) {
                if (xx  *xx +  yy*yy!= a*a)continue;
                T ang  = asin((T)yy  /  a) ;
                if(fabs(ang - B) <EPS  || fabs(ang   -  M_PI/2.0)  <EPS  || ang <EPS) continue  ;

                pair < T , T > point ;
                point   = getPoint(ang - B , c) ;
                int f = INT(point.first) ,  s = INT(point.second);
                if (f == 0 || s == 0)
                       continue;
                int dx = f - xx , dy = s - yy ;
                if (dx  *dx   + dy  * dy !=  b  * b)continue;
                if (f  * f + s* s !=a*a + b*b)continue;
                cout <<"YES\n";
                cout <<  0 <<" "<< 0  <<"\n";
                cout <<xx<<" "<<yy<<"\n";
                cout << point.first <<" "<<point.second <<"\n";
                return ;
         }
      }
      cout << "NO\n" ;
}

int32_t main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    testCase();
}
