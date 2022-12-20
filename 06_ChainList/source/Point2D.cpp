//#include "../class/Point2D.h"
//#include "../header/Errors.h"
//#include <cmath>
//
//double Point::operator[](int n) {
//    if (n == 0) {
//        return x;
//    }
//    else if (n == 1) {
//        return y;
//    }
//    else {
//        throw illegalParameterValue("Only 2D points(0,1 allowed).");
//    }
//}
//void PointChain2D::init() {
//    headPoint = new PointNode;
//    headPoint->next = nullptr;
//    point_number = 0;
//}
//int PointChain2D::size() const {
//    return point_number;
//};
//bool PointChain2D::empty() const {
//    return point_number;
//};
//PointChain2D::PointChain2D() {
//    init();
//};
//PointChain2D::~PointChain2D() {
//    PointNode* temp;
//    while (headPoint) {
//        temp = headPoint->next;
//        delete headPoint;
//        headPoint = temp;
//    }
//};
//PointNode* PointChain2D::get_firstPoint() const {
//    return headPoint->next;
//};
//void PointChain2D::insert(const double& x, const double& y) {
//    Point point(x, y);
//    point_number++;
//    PointNode* p = new PointNode(point, headPoint->next);
//    headPoint->next = p;
//};
//void PointChain2D::insert(const PointNode* p) {
//    insert(p->coordinate.x, p->coordinate.y);
//}
//void PointChain2D::insert(PointNode* loc, const double& x, const double& y) {
//    if (!loc) return;
//    Point point(x, y);
//    point_number++;
//    PointNode* p = new PointNode(point, loc->next);
//    loc->next = p;
//};
//Point& PointChain2D::get_point(int i) {
//    int j = 0;
//    PointNode* p = headPoint;
//    while (p && j < i) { p = p->next; ++j; }
//    if (!p || j != i) return;
//    else return p->coordinate;
//};
//Point PointChain2D::get_aPointIn3(Point& p1, Point& p2, Point& p3) {
//    int l1 = sqrt((p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y));
//    int l2 = sqrt((p1.x - p3.x) * (p1.x - p3.x) + (p1.y - p3.y) * (p1.y - p3.y));
//    int l3 = sqrt((p3.x - p2.x) * (p3.x - p2.x) + (p3.y - p2.y) * (p3.y - p2.y));
//    int p = l1 + l2 + l3;
//    return Point((l1 * p3.x + l2 * p2.x + l3 * p1.x) / p, (l1 * p3.y + l2 * p2.y + l3 * p1.y) / p);
//};
//
//bool whe_col(const Point& a, const Point& b, const Point& c) {
//    double vec1[2] = { a.x - b.x,a.y - b.y };
//    double vec2[2] = { a.x - c.x,a.y - c.y };
//    if (vec1[0] * vec2[1] == vec1[1] * vec2[0]) {
//        return true;
//    }
//    else {
//        return false;
//    }
//}
//
//Point& PointChain2D::collinate(PointChain2D& pointSet) {
//    if (pointSet.size() < 3) {
//        return;
//    }
//    PointNode* fPoint = pointSet.get_firstPoint();
//    PointNode* sPoint = fPoint->next;
//    PointNode* pPoint = sPoint->next;
//    while (pPoint) {
//        if (whe_col(fPoint->coordinate, sPoint->coordinate, pPoint->coordinate)) {
//            pPoint = pPoint->next;
//        }
//        else {
//            PointChain2D* res = new PointChain2D;
//            Point* p = new Point(get_aPointIn3(fPoint->coordinate,sPoint->coordinate,pPoint->coordinate));
//            return *p;
//        }
//    }
//
//}