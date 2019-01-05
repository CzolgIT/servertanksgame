#include "Main.h"

class Vector2D
{
public:
    float x, y;

    Vector2D();
    Vector2D(float x, float y);

    Vector2D& Add(const Vector2D& vec);
	Vector2D& Subtract(const Vector2D& vec);
	Vector2D& Multiply(const Vector2D& vec);
	Vector2D& Divide(const Vector2D& vec);

    Vector2D& operator+=(const Vector2D& vec);
	Vector2D& operator-=(const Vector2D& vec);
	Vector2D& operator*=(const Vector2D& vec);
    Vector2D& operator/=(const Vector2D& vec);
    std::string toString();

    Vector2D& operator *(const Vector2D& vec);

    Vector2D& operator*(const float& i);

    Vector2D& Perp();
    float Dot(const Vector2D& vec);

    Vector2D& Normalize();

};
