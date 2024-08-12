struct Point {  
    double x; // 横坐标  
    double y; // 纵坐标
	Point(){}  
	Point(double x = 0, double y = 0) :x(x), y(y) {}
	Point(const Point &p) : x(p.x), y(p.y) {}
};  

typedef Point Vector;

Vector operator + (Vector A, Vector B) { return Vector(A.x + B.x, A.y + B.y); }  
Vector operator - (Point A, Point B) { return Vector(A.x - B.y, A.y - B.y); }  
Vector operator * (Vector A, double p) { return Vector(A.x*p, A.y*p); }  
Vector operator / (Vector A, double p) { return Vector(A.x / p, A.y*p); }  

double Dot(Vector A, Vector B) { return A.x*B.x + A.y*B.y; } // 向量点乘  
double Length(Vector A) { return sqrt(Dot(A, A)); }  // 向量模长  
double Angle(Vector A, Vector B) { return acos(Dot(A, B) / Length(A) / Length(B)); }  // 向量之间夹角  

double Cross(Vector A, Vector B) { // 叉积计算 公式  
    return A.x*B.y - A.y*B.x;  
}  

Vector Rotate(Vector A, double rad) // 向量旋转 公式  
{  
    return Vector(A.x*cos(rad) - A.y*sin(rad), A.x*sin(rad) + A.y*cos(rad));  
}  

Point getLineIntersection(Point P, Vector v, Point Q, Vector w) { // 两直线交点t1 t2计算公式   
    Vector u = P - Q;   
    double t = Cross(w, u) / Cross(v, w);  // 求得是横坐标  
    return P + v*t;  // 返回一个点  
}  

node G[maxn];  
int n;  

int getS()  //求多边形面积，std输入输出
{  
    while (scanf("%d", &n) != EOF && n) {  
        for (int i = 0; i < n; i++)   
            scanf("%lf %lf", &G[i].x, &G[i].y);  
        double sum = 0;  
        G[n].x = G[0].x;  
        G[n].y = G[0].y;  
        for (int i = 0; i < n; i++) {   
                sum += Cross(G[i], G[i + 1]);  
        }  
        // 或者  
            //for (int i = 0; i < n; i++) {  
                //sum += fun(G[i], G[（i + 1）% n]);  
            //}  
        sum = sum / 2.0;  
        printf("%.1f\n", sum);  
    }  
    return 0;  
}

/*
    判断线段相交
*/

Point P[35][105];     

double Cross_Prouct(Point A,Point B,Point C) {     //  计算BA叉乘CA     
    return (B.x-A.x)*(C.y-A.y)-(B.y-A.y)*(C.x-A.x);      
}      
bool Intersect(Point A,Point B,Point C,Point D)  {  //  通过叉乘判断线段是否相交；           
    if(min(A.x,B.x)<=max(C.x,D.x)&&         //  快速排斥实验；      
       min(C.x,D.x)<=max(A.x,B.x)&&      
       min(A.y,B.y)<=max(C.y,D.y)&&      
       min(C.y,D.y)<=max(A.y,B.y)&&      
       Cross_Prouct(A,B,C)*Cross_Prouct(A,B,D)<0&&      //  跨立实验；      
       Cross_Prouct(C,D,A)*Cross_Prouct(C,D,B)<0)       //  叉乘异号表示在两侧；      
       return true;      
    else return false;      
}    

/*
   求三角形外心
*/

Point circumcenter(const Point &a, const Point &b, const Point &c) { //返回三角形的外心        
    Point ret;  
    double a1 = b.x - a.x, b1 = b.y - a.y, c1 = (a1*a1 + b1*b1) / 2;  
    double a2 = c.x - a.x, b2 = c.y - a.y, c2 = (a2*a2 + b2*b2) / 2;  
    double d = a1*b2 - a2*b1;  
    ret.x = a.x + (c1*b2 - c2*b1) / d;  
    ret.y = a.y + (a1*c2 - a2*c1) / d;  
    return ret;  
}  


/*
	按照极角排序
*/

double cross(point p1, point p2, point q1, point q2) {  // 叉积计算   
    return (q2.y - q1.y)*(p2.x - p1.x) - (q2.x - q1.x)*(p2.y - p1.y);  
}  
bool cmp(point a, point b)  {  
    point o;  
    o.x = o.y = 0;  
    return cross(o, b, o, a) < 0; // 叉积判断  
}  
sort(convex + 1, convex + cnt, cmp); // 按角排序, 从小到大 