//
//  TransformComponent.hpp
//  cgl_st2016_semestertask
//
//  Created by Utz Stauder on 28/07/16.
//  Copyright © 2016 Utz Stauder. All rights reserved.
//

#ifndef TransformComponent_hpp
#define TransformComponent_hpp

#include "IComponent.hpp"
#include "Vector2.hpp"

class TransformComponent : public IComponent{
public:
    TransformComponent(const Vector2 &p = Vector2::zero, const Vector2 &s = Vector2::one, float r = 0);
    ~TransformComponent();
    virtual void Update();
    
    inline Vector2 GetPosition() { return position; };
    void SetPosition(float x, float y);
    void SetPosition(const Vector2 &v);
    void Move(const Vector2 &v);
    
    inline Vector2 GetScale() { return scale; };
    void SetScale(float x, float y);
    void SetScale(const Vector2 &v);
    void Scale(const Vector2 &v);
    void Scale(float s);
    
    inline float GetRotation() { return rotation; };
    void SetRotation(float r);
    void Rotate(float r);
    
    // TODO: relative direction vectors
    //Vector2 forward { };
    //Vector2 back    { };
    //Vector2 left    { };
    //Vector2 right   { };
    
private:
    Vector2 position;
    Vector2 scale;
    float rotation;
    
    // TODO: implement hierarchy, something like this:
    // TransformComponent *parent;
    // vector<TransformComponent> *children;
};

#endif /* TransformComponent_hpp */
