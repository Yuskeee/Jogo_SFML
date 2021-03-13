#ifndef _VECTOR2D_H
#define _VECTOR2D_H

class Vector2D{

private:
    float x;
    float y;

public:

    Vector2D();
    Vector2D(float x, float y);
    ~Vector2D();

    void setX(float x);
    void setY(float y);

    float getX() const; 
    float getY() const;

    void operator=(const Vector2D& vec);
    void operator+=(const Vector2D& vec);
    void operator-=(const Vector2D& vec);

};

Vector2D operator+(const Vector2D& vec1, const Vector2D& vec2);
Vector2D operator-(const Vector2D& vec1, const Vector2D& vec2);


#endif
