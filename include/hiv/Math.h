#pragma once

#include <string.h>
#include <math.h>

#define PI_F 3.14159265358979323846
#define PI_L 3.141592653589793238462643383279502884L

static float hiv_ToRadiansF(float angle) { return angle * PI_F/180.0f; }
static float hiv_ToDegreesF(float angle) { return angle * 180/PI_F;    }

static double hiv_ToRadiansD(double angle) { return angle * PI_L/180.0; }
static double hiv_ToDegreesD(double angle) { return angle * 180/PI_L;    }

#define hiv_ToRadians(angle) _Generic((angle), float:  hiv_ToRadiansF(angle), \
                                               double: hiv_ToRadiansD(angle))
#define hiv_ToDegree(angle)  _Generic((angle), float:  hiv_ToDegreeF(angle), \
                                               double: hiv_ToDegreeD(angle))

typedef struct hiv_Vec2_t { union 
{
    struct { float x, y; };
    struct { float w, h; };

    float elements[2];
}; } hiv_Vec2;

typedef struct hiv_Vec3_t { union 
{
    struct { float x, y, z; };
    struct { float r, g, b; };

    float elements[3];
}; } hiv_Vec3;

typedef struct hiv_Vec4_t { union
{
    struct { float x, y, z, w; };
    struct { float r, g, b, a; };

    float elements[4];
}; } hiv_Vec4;

typedef struct hiv_Mat4_t { union
{
    hiv_Vec4 vecs[4];
    float raw[4 * 4];
}; } hiv_Mat4;

static hiv_Mat4 hiv_Mat4_Identity()
{
    hiv_Mat4 res = {0};

    for (int i = 0; i < 4; i++)
        res.raw[i] = 0.0f;

    res.raw[0 + 0 * 4] = 1.0f; 
    res.raw[1 + 1 * 4] = 1.0f; 
    res.raw[2 + 2 * 4] = 1.0f; 
    res.raw[3 + 3 * 4] = 1.0f; 

    return res;
}

static hiv_Mat4 hiv_Mat4_Ortho(float l, float r, float b, float t, float n, float f)
{
    hiv_Mat4 res = hiv_Mat4_Identity();

    res.raw[0 + 0 * 4] = 2.0f  / (r-l);
    res.raw[1 + 1 * 4] = 2.0f  / (t-b);
    res.raw[2 + 2 * 4] = 2.0f  / (n-f);
    res.raw[0 + 3 * 4] = (l+r) / (l-r);
    res.raw[1 + 3 * 4] = (b+t) / (b-t);
    res.raw[2 + 3 * 4] = (f+n) / (f-n);

    return res;
}

static hiv_Mat4 hiv_Mat4_TranslateVec2(hiv_Vec2 translation)
{
    hiv_Mat4 res = hiv_Mat4_Identity();
    res.raw[0 + 3 * 4] = translation.x;
    res.raw[1 + 3 * 4] = translation.y;
    return res;
}

static hiv_Mat4 hiv_Mat4_TranslateVec3(hiv_Vec3 translation)
{
    hiv_Mat4 res = hiv_Mat4_Identity();
    res.raw[0 + 3 * 4] = translation.x;
    res.raw[1 + 3 * 4] = translation.y;
    res.raw[2 + 3 * 4] = translation.z;
    return res;
}

static hiv_Mat4 hiv_Mat4_TranslateVec4(hiv_Vec4 translation)
{
    hiv_Mat4 res = hiv_Mat4_Identity();
    res.raw[0 + 3 * 4] = translation.x;
    res.raw[1 + 3 * 4] = translation.y;
    res.raw[2 + 3 * 4] = translation.z;
    res.raw[3 + 3 * 4] = translation.w;
    return res;
}

static hiv_Mat4 hiv_Mat4_Rotate(float angle)
{
    hiv_Mat4 res = hiv_Mat4_Identity();
    res.raw[0 + 0 * 4] =  cos(angle);
    res.raw[1 + 0 * 4] =  sin(angle);
    res.raw[0 + 1 * 4] = -sin(angle);
    res.raw[1 + 1 * 4] =  cos(angle);
    return res;
}

static hiv_Mat4 hiv_Mat4_Mult(hiv_Mat4 rh, hiv_Mat4 lh)
{
    float data[4 * 4];

    for (int row = 0; row < 4; row++)
        for (int col = 0; col < 4; col++)
        {
            float sum = 0.0f;
            for (int element = 0; element < 4; element++)
                sum += rh.raw[element + row * 4] * 
                       lh.raw[col + element * 4];
            data[col + row * 4] = sum;
        }

    memcpy(rh.raw, data, 4 * 4 * sizeof(float));
	return rh;
}

static hiv_Vec2 hiv_AddVec2(hiv_Vec2 rh, hiv_Vec2 lh)
{
    return (hiv_Vec2) { rh.x + lh.x,
                        rh.y + lh.y };
}

static hiv_Vec3 hiv_AddVec3(hiv_Vec3 rh, hiv_Vec3 lh)
{
    return (hiv_Vec3) { rh.x + lh.x,
                        rh.y + lh.y,
                        rh.z + lh.z };
}

static hiv_Vec4 hiv_AddVec4(hiv_Vec4 rh, hiv_Vec4 lh)
{
    return (hiv_Vec4) { rh.x + lh.x,
                        rh.y + lh.y,
                        rh.z + lh.z,
                        rh.w + lh.w };
}

static hiv_Vec2 hiv_SubVec2(hiv_Vec2 rh, hiv_Vec2 lh)
{
    return (hiv_Vec2) { rh.x - lh.x,
                        rh.y - lh.y };
}

static hiv_Vec3 hiv_SubVec3(hiv_Vec3 rh, hiv_Vec3 lh)
{
    return (hiv_Vec3) { rh.x - lh.x,
                        rh.y - lh.y,
                        rh.z - lh.z };
}

static hiv_Vec4 hiv_SubVec4(hiv_Vec4 rh, hiv_Vec4 lh)
{
    return (hiv_Vec4) { rh.x - lh.x,
                        rh.y - lh.y,
                        rh.z - lh.z,
                        rh.w - lh.w };
}

static hiv_Vec2 hiv_MulVec2(hiv_Vec2 rh, hiv_Vec2 lh)
{
    return (hiv_Vec2) { rh.x * lh.x,
                        rh.y * lh.y };
}

static hiv_Vec3 hiv_MulVec3(hiv_Vec3 rh, hiv_Vec3 lh)
{
    return (hiv_Vec3) { rh.x * lh.x,
                        rh.y * lh.y,
                        rh.z * lh.z };
}

static hiv_Vec4 hiv_MulVec4(hiv_Vec4 rh, hiv_Vec4 lh)
{
    return (hiv_Vec4) { rh.x * lh.x,
                        rh.y * lh.y,
                        rh.z * lh.z,
                        rh.w * lh.w };
}

static hiv_Vec2 hiv_DivVec2(hiv_Vec2 rh, hiv_Vec2 lh)
{
    return (hiv_Vec2) { rh.x / lh.x,
                        rh.y / lh.y };
}

static hiv_Vec3 hiv_DivVec3(hiv_Vec3 rh, hiv_Vec3 lh)
{
    return (hiv_Vec3) { rh.x / lh.x,
                        rh.y / lh.y,
                        rh.z / lh.z };
}

static hiv_Vec4 hiv_DivVec4(hiv_Vec4 rh, hiv_Vec4 lh)
{
    return (hiv_Vec4) { rh.x / lh.x,
                        rh.y / lh.y,
                        rh.z / lh.z,
                        rh.w / lh.w };
}
