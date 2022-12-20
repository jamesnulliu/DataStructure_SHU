//#pragma once
//#include "Chain.h"
//struct Point {
//    double x;
//    double y;
//    Point(double a = 0, double b = 0) :x(a), y(b) {}
//    double operator[](int n);
//};
//
//struct PointNode
//{
//    Point coordinate;
//    PointNode* next;
//    PointNode(PointNode*n = nullptr): next(n) {};
//    PointNode(Point& p, PointNode* n = nullptr) : coordinate(p),next(n) {}
//};
//
//class PointChain2D
//{
//protected:
//    int point_number;
//    PointNode* headPoint;
//    // Initialize the head point.
//    void init();
//public:
//    // Return "point_number".
//    int size() const;
//    // Check whether the Chain is empty.
//    bool empty() const;
//    // When creating a "Point2D" object:
//    // "point_number" is set to "0",
//    // "headnode" is created and points to nullptr.
//    PointChain2D();
//    // Delete every point in the chain.
//    ~PointChain2D();
//    // Return the pointer of the first point.
//    PointNode* get_firstPoint() const;
//    // With two "const double&" parameter (as "x" and "y"),
//    // create and insert a new point after "headnode";
//    // meanwhile, increase "point_number".
//    void insert(const double&, const double&);
//
//    void insert(const PointNode*);
//    // With a "Point*" pointer and 2 "const double&" parameter (as "x" and "y"),
//    // create and insert a new point after the point;
//    // meanwhile, increase "point_number".
//    void insert(PointNode*, const double&, const double&);
//    // Return the "i"th point.
//    Point& get_point(int);
//
//    Point get_aPointIn3(Point&, Point&, Point&);
//
//    Point& collinate(PointChain2D&);
//
//};
//
