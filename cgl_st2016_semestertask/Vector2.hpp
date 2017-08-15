//
//  Vector2.hpp
//  cgl_st2016_semestertask
//
//  Created by Utz Stauder on 28/07/16.
//  Copyright © 2016 Utz Stauder. All rights reserved.
//

#ifndef Vector2_hpp
#define Vector2_hpp

#include <stdio.h>
#include <memory>
#include <math.h>

class Vector2{
public:
    Vector2(float x = 0, float y = 0);
    ~Vector2();
    
    void Set(float x, float y);
    void SetX(float x);
    void SetY(float y);
    inline float GetX(){ return x; };
    inline float GetY(){ return y; };
    
    const static Vector2 &zero;
    const static Vector2 &one;
    const static Vector2 &left;
    const static Vector2 &right;
    const static Vector2 &up;
    const static Vector2 &down;
    
    const float Length();
    const float LengthSquared();
    
    const static float Distance(const Vector2 &v1, const Vector2 &v2);
    const static float DistanceSquared(const Vector2 &v1, const Vector2 &v2);
    
    Vector2 &Normalize();
    
    inline const bool    operator == (const Vector2 &v) { return ((x == v.x) && (y == v.y)); };
    inline const bool    operator != (const Vector2 &v) { return ((x != v.x) || (y != v.y)); };
    inline const Vector2 operator +  (const Vector2 &v) { return Vector2(x + v.x, y + v.y); };
    inline const Vector2 operator -  (const Vector2 &v) { return Vector2(x - v.x, y - v.y); };
    inline const float   operator *  (const Vector2 &v) { return (x * v.x + y * v.y); };
    inline const Vector2 operator /  (const Vector2 &v) { return Vector2(x / v.x, y / v.y); };
    inline const Vector2 operator *  (float v)          { return Vector2(x * v, y * v); };
    inline const Vector2 operator /  (float v)          { return Vector2(x / v, y / v); };
    
private:
    float x;
    float y;
};

#endif /* Vector2_hpp */
