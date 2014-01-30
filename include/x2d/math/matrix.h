#ifndef MATH_MATRICES_H
#define MATH_MATRICES_H

#include "vector.h"

///////////////////////////////////////////////////////////////////////////
// 2x2 matrix
///////////////////////////////////////////////////////////////////////////
class mat2
{
public:
    // constructors
    mat2();  // init with identity
    mat2(const float src[4]);
    mat2(float xx, float xy, float yx, float yy);

    void        set(const float src[4]);
    void        set(float xx, float xy, float yx, float yy);
    void        setRow(int index, const float row[2]);
    void        setRow(int index, const vec2& v);
    void        setColumn(int index, const float col[2]);
    void        setColumn(int index, const vec2& v);

    const float* get() const;
    float        getDeterminant();

    mat2&    identity();
    mat2&    transpose();                         // transpose itself and return reference
    mat2&    invert();

    // operators
    mat2     operator+(const mat2& rhs) const;    // add rhs
    mat2     operator-(const mat2& rhs) const;    // subtract rhs
    mat2&    operator+=(const mat2& rhs);         // add rhs and update this object
    mat2&    operator-=(const mat2& rhs);         // subtract rhs and update this object
    vec2     operator*(const vec2& rhs) const;    // multiplication: v' = M * v
    mat2     operator*(const mat2& rhs) const;    // multiplication: M3 = M1 * M2
    mat2&    operator*=(const mat2& rhs);         // multiplication: M1' = M1 * M2
    bool     operator==(const mat2& rhs) const;   // exact compare, no epsilon
    bool     operator!=(const mat2& rhs) const;   // exact compare, no epsilon
    float    operator[](int index) const;         // subscript operator v[0], v[1]
    float&   operator[](int index);               // subscript operator v[0], v[1]

    friend mat2 operator-(const mat2& m);                     // unary operator (-)
    friend mat2 operator*(float scalar, const mat2& m);       // pre-multiplication
    friend vec2 operator*(const vec2& vec, const mat2& m);    // pre-multiplication
    friend std::ostream& operator<<(std::ostream& os, const mat2& m);

private:
    float m[4];

};

///////////////////////////////////////////////////////////////////////////
// 3x3 matrix
///////////////////////////////////////////////////////////////////////////
class mat3
{
public:
    // constructors
    mat3();  // init with identity
    mat3(const float src[9]);
    mat3(float xx, float xy, float xz,
            float yx, float yy, float yz,
            float zx, float zy, float zz);

    void        set(const float src[9]);
    void        set(float xx, float xy, float xz,
                    float yx, float yy, float yz,
                    float zx, float zy, float zz);
    void        setRow(int index, const float row[3]);
    void        setRow(int index, const vec3& v);
    void        setColumn(int index, const float col[3]);
    void        setColumn(int index, const vec3& v);

    const float* get() const;
    float        getDeterminant();

    mat3&    identity();
    mat3&    transpose();                            // transpose itself and return reference
    mat3&    invert();

    // operators
    mat3     operator+(const mat3& rhs) const;    // add rhs
    mat3     operator-(const mat3& rhs) const;    // subtract rhs
    mat3&    operator+=(const mat3& rhs);         // add rhs and update this object
    mat3&    operator-=(const mat3& rhs);         // subtract rhs and update this object
    vec3     operator*(const vec3& rhs) const;    // multiplication: v' = M * v
    mat3     operator*(const mat3& rhs) const;    // multiplication: M3 = M1 * M2
    mat3&    operator*=(const mat3& rhs);         // multiplication: M1' = M1 * M2
    bool        operator==(const mat3& rhs) const;   // exact compare, no epsilon
    bool        operator!=(const mat3& rhs) const;   // exact compare, no epsilon
    float       operator[](int index) const;            // subscript operator v[0], v[1]
    float&      operator[](int index);                  // subscript operator v[0], v[1]

    friend mat3 operator-(const mat3& m);                     // unary operator (-)
    friend mat3 operator*(float scalar, const mat3& m);       // pre-multiplication
    friend vec3 operator*(const vec3& vec, const mat3& m); // pre-multiplication
    friend std::ostream& operator<<(std::ostream& os, const mat3& m);

protected:

private:
    float m[9];

};

///////////////////////////////////////////////////////////////////////////
// 4x4 matrix
///////////////////////////////////////////////////////////////////////////
class mat4
{
public:
    // constructors
    mat4();  // init with identity
    mat4(const float src[16]);
    mat4(float xx, float xy, float xz, float xw,
            float yx, float yy, float yz, float yw,
            float zx, float zy, float zz, float zw,
            float wx, float wy, float wz, float ww);

    void        set(const float src[16]);
    void        set(float xx, float xy, float xz, float xw,
                    float yx, float yy, float yz, float yw,
                    float zx, float zy, float zz, float zw,
                    float wx, float wy, float wz, float ww);
    void        setRow(int index, const float row[4]);
    void        setRow(int index, const vec4& v);
    void        setRow(int index, const vec3& v);
    void        setColumn(int index, const float col[4]);
    void        setColumn(int index, const vec4& v);
    void        setColumn(int index, const vec3& v);

    const float* get() const;
    const float* getTranspose();                        // return transposed matrix
    float        getDeterminant();

    mat4&    identity();
    mat4&    transpose();                            // transpose itself and return reference
    mat4&    invert();                               // check best inverse method before inverse
    mat4&    invertEuclidean();                      // inverse of Euclidean transform matrix
    mat4&    invertAffine();                         // inverse of affine transform matrix
    mat4&    invertProjective();                     // inverse of projective matrix using partitioning
    mat4&    invertGeneral();                        // inverse of generic matrix

    // transform matrix
    mat4&    translate(float x, float y, float z);   // translation by (x,y,z)
    mat4&    translate(const vec3& v);            //
    mat4&    rotate(float angle, const vec3& axis); // rotate angle(degree) along the given axix
    mat4&    rotate(float angle, float x, float y, float z);
    mat4&    rotateX(float angle);                   // rotate on X-axis with degree
    mat4&    rotateY(float angle);                   // rotate on Y-axis with degree
    mat4&    rotateZ(float angle);                   // rotate on Z-axis with degree
    mat4&    scale(float scale);                     // uniform scale
    mat4&    scale(float sx, float sy, float sz);    // scale by (sx, sy, sz) on each axis

    // operators
    mat4     operator+(const mat4& rhs) const;    // add rhs
    mat4     operator-(const mat4& rhs) const;    // subtract rhs
    mat4&    operator+=(const mat4& rhs);         // add rhs and update this object
    mat4&    operator-=(const mat4& rhs);         // subtract rhs and update this object
    vec4     operator*(const vec4& rhs) const;    // multiplication: v' = M * v
    vec3     operator*(const vec3& rhs) const;    // multiplication: v' = M * v
    mat4     operator*(const mat4& rhs) const;    // multiplication: M3 = M1 * M2
    mat4&    operator*=(const mat4& rhs);         // multiplication: M1' = M1 * M2
    bool        operator==(const mat4& rhs) const;   // exact compare, no epsilon
    bool        operator!=(const mat4& rhs) const;   // exact compare, no epsilon
    float       operator[](int index) const;            // subscript operator v[0], v[1]
    float&      operator[](int index);                  // subscript operator v[0], v[1]

    friend mat4 operator-(const mat4& m);                     // unary operator (-)
    friend mat4 operator*(float scalar, const mat4& m);       // pre-multiplication
    friend vec3 operator*(const vec3& vec, const mat4& m); // pre-multiplication
    friend vec4 operator*(const vec4& vec, const mat4& m); // pre-multiplication
    friend std::ostream& operator<<(std::ostream& os, const mat4& m);

protected:

private:
    float       getCofactor(float m0, float m1, float m2,
                            float m3, float m4, float m5,
                            float m6, float m7, float m8);

    float m[16];
    float tm[16];                                       // transpose m

};

///////////////////////////////////////////////////////////////////////////
// inline functions for mat2
///////////////////////////////////////////////////////////////////////////
inline mat2::mat2()
{
    // initially identity matrix
    identity();
}

inline mat2::mat2(const float src[4])
{
    set(src);
}

inline mat2::mat2(float xx, float xy, float yx, float yy)
{
    set(xx, xy, yx, yy);
}

inline void mat2::set(const float src[4])
{
    m[0] = src[0];  m[1] = src[1];  m[2] = src[2];  m[3] = src[3];
}

inline void mat2::set(float xx, float xy, float yx, float yy)
{
    m[0]= xx;  m[1] = xy;  m[2] = yx;  m[3]= yy;
}



inline void mat2::setRow(int index, const float row[2])
{
    m[index*2] = row[0];  m[index*2 + 1] = row[1];
}

inline void mat2::setRow(int index, const vec2& v)
{
    m[index*2] = v.x;  m[index*2 + 1] = v.y;
}

inline void mat2::setColumn(int index, const float col[2])
{
    m[index] = col[0];  m[index + 2] = col[1];
}

inline void mat2::setColumn(int index, const vec2& v)
{
    m[index] = v.x;  m[index + 2] = v.y;
}

inline const float* mat2::get() const
{
    return m;
}

inline mat2& mat2::identity()
{
    m[0] = m[3] = 1.0f;
    m[1] = m[2] = 0.0f;
    return *this;
}

inline mat2 mat2::operator+(const mat2& rhs) const
{
    return mat2(m[0]+rhs[0], m[1]+rhs[1], m[2]+rhs[2], m[3]+rhs[3]);
}

inline mat2 mat2::operator-(const mat2& rhs) const
{
    return mat2(m[0]-rhs[0], m[1]-rhs[1], m[2]-rhs[2], m[3]-rhs[3]);
}

inline mat2& mat2::operator+=(const mat2& rhs)
{
    m[0] += rhs[0];  m[1] += rhs[1];  m[2] += rhs[2];  m[3] += rhs[3];
    return *this;
}

inline mat2& mat2::operator-=(const mat2& rhs)
{
    m[0] -= rhs[0];  m[1] -= rhs[1];  m[2] -= rhs[2];  m[3] -= rhs[3];
    return *this;
}

inline vec2 mat2::operator*(const vec2& rhs) const
{
    return vec2(m[0]*rhs.x + m[1]*rhs.y,  m[2]*rhs.x + m[3]*rhs.y);
}

inline mat2 mat2::operator*(const mat2& rhs) const
{
    return mat2(m[0]*rhs[0] + m[1]*rhs[2],  m[0]*rhs[1] + m[1]*rhs[3],
                   m[2]*rhs[0] + m[3]*rhs[2],  m[2]*rhs[1] + m[3]*rhs[3]);
}

inline mat2& mat2::operator*=(const mat2& rhs)
{
    *this = *this * rhs;
    return *this;
}

inline bool mat2::operator==(const mat2& rhs) const
{
    return (m[0] == rhs[0]) && (m[1] == rhs[1]) && (m[2] == rhs[2]) && (m[3] == rhs[3]);
}

inline bool mat2::operator!=(const mat2& rhs) const
{
    return (m[0] != rhs[0]) || (m[1] != rhs[1]) || (m[2] != rhs[2]) || (m[3] != rhs[3]);
}

inline float mat2::operator[](int index) const
{
    return m[index];
}

inline float& mat2::operator[](int index)
{
    return m[index];
}

inline mat2 operator-(const mat2& rhs)
{
    return mat2(-rhs[0], -rhs[1], -rhs[2], -rhs[3]);
}

inline mat2 operator*(float s, const mat2& rhs)
{
    return mat2(s*rhs[0], s*rhs[1], s*rhs[2], s*rhs[3]);
}

inline vec2 operator*(const vec2& v, const mat2& rhs)
{
    return vec2(v.x*rhs[0] + v.y*rhs[2],  v.x*rhs[1] + v.y*rhs[3]);
}

#ifdef DEPRICATED
inline std::ostream& operator<<(std::ostream& os, const mat2& m)
{
    os << "(" << m[0] << ",\t" << m[1] << ")\n"
       << "(" << m[2] << ",\t" << m[3] << ")\n";
    return os;
}
#endif

///////////////////////////////////////////////////////////////////////////
// inline functions for mat3
///////////////////////////////////////////////////////////////////////////
inline mat3::mat3()
{
    // initially identity matrix
    identity();
}



inline mat3::mat3(const float src[9])
{
    set(src);
}

inline mat3::mat3(float xx, float xy, float xz,
                        float yx, float yy, float yz,
                        float zx, float zy, float zz)
{
    set(xx, xy, xz,  yx, yy, yz,  zx, zy, zz);
}

inline void mat3::set(const float src[9])
{
    m[0] = src[0];  m[1] = src[1];  m[2] = src[2];
    m[3] = src[3];  m[4] = src[4];  m[5] = src[5];
    m[6] = src[6];  m[7] = src[7];  m[8] = src[8];
}

inline void mat3::set(float xx, float xy, float xz,
                         float yx, float yy, float yz,
                         float zx, float zy, float zz)
{
    m[0] = xx;  m[1] = xy;  m[2] = xz;
    m[3] = yx;  m[4] = yy;  m[5] = yz;
    m[6] = zx;  m[7] = zy;  m[8] = zz;
}

inline void mat3::setRow(int index, const float row[3])
{
    m[index*3] = row[0];  m[index*3 + 1] = row[1];  m[index*3 + 2] = row[2];
}

inline void mat3::setRow(int index, const vec3& v)
{
    m[index*3] = v.x;  m[index*3 + 1] = v.y;  m[index*3 + 2] = v.z;
}

inline void mat3::setColumn(int index, const float col[3])
{
    m[index] = col[0];  m[index + 3] = col[1];  m[index + 6] = col[2];
}

inline void mat3::setColumn(int index, const vec3& v)
{
    m[index] = v.x;  m[index + 3] = v.y;  m[index + 6] = v.z;
}

inline const float* mat3::get() const
{
    return m;
}

inline mat3& mat3::identity()
{
    m[0] = m[4] = m[8] = 1.0f;
    m[1] = m[2] = m[3] = m[5] = m[6] = m[7] = 0.0f;
    return *this;
}

inline mat3 mat3::operator+(const mat3& rhs) const
{
    return mat3(m[0]+rhs[0], m[1]+rhs[1], m[2]+rhs[2],
                   m[3]+rhs[3], m[4]+rhs[4], m[5]+rhs[5],
                   m[6]+rhs[6], m[7]+rhs[7], m[8]+rhs[8]);
}

inline mat3 mat3::operator-(const mat3& rhs) const
{
    return mat3(m[0]-rhs[0], m[1]-rhs[1], m[2]-rhs[2],
                   m[3]-rhs[3], m[4]-rhs[4], m[5]-rhs[5],
                   m[6]-rhs[6], m[7]-rhs[7], m[8]-rhs[8]);
}

inline mat3& mat3::operator+=(const mat3& rhs)
{
    m[0] += rhs[0];  m[1] += rhs[1];  m[2] += rhs[2];
    m[3] += rhs[3];  m[4] += rhs[4];  m[5] += rhs[5];
    m[6] += rhs[6];  m[7] += rhs[7];  m[8] += rhs[8];
    return *this;
}

inline mat3& mat3::operator-=(const mat3& rhs)
{
    m[0] -= rhs[0];  m[1] -= rhs[1];  m[2] -= rhs[2];
    m[3] -= rhs[3];  m[4] -= rhs[4];  m[5] -= rhs[5];
    m[6] -= rhs[6];  m[7] -= rhs[7];  m[8] -= rhs[8];
    return *this;
}

inline vec3 mat3::operator*(const vec3& rhs) const
{
    return vec3(m[0]*rhs.x + m[1]*rhs.y + m[2]*rhs.z,
                   m[3]*rhs.x + m[4]*rhs.y + m[5]*rhs.z,
                   m[6]*rhs.x + m[7]*rhs.y + m[8]*rhs.z);
}

inline mat3 mat3::operator*(const mat3& rhs) const
{
    return mat3(m[0]*rhs[0] + m[1]*rhs[3] + m[2]*rhs[6],  m[0]*rhs[1] + m[1]*rhs[4] + m[2]*rhs[7],  m[0]*rhs[2] + m[1]*rhs[5] + m[2]*rhs[8],
                   m[3]*rhs[0] + m[4]*rhs[3] + m[5]*rhs[6],  m[3]*rhs[1] + m[4]*rhs[4] + m[5]*rhs[7],  m[3]*rhs[2] + m[4]*rhs[5] + m[5]*rhs[8],
                   m[6]*rhs[0] + m[7]*rhs[3] + m[8]*rhs[6],  m[6]*rhs[1] + m[7]*rhs[4] + m[8]*rhs[7],  m[6]*rhs[2] + m[7]*rhs[5] + m[8]*rhs[8]);
}

inline mat3& mat3::operator*=(const mat3& rhs)
{
    *this = *this * rhs;
    return *this;
}

inline bool mat3::operator==(const mat3& rhs) const
{
    return (m[0] == rhs[0]) && (m[1] == rhs[1]) && (m[2] == rhs[2]) &&
           (m[3] == rhs[3]) && (m[4] == rhs[4]) && (m[5] == rhs[5]) &&
           (m[6] == rhs[6]) && (m[7] == rhs[7]) && (m[8] == rhs[8]);
}

inline bool mat3::operator!=(const mat3& rhs) const
{
    return (m[0] != rhs[0]) || (m[1] != rhs[1]) || (m[2] != rhs[2]) ||
           (m[3] != rhs[3]) || (m[4] != rhs[4]) || (m[5] != rhs[5]) ||
           (m[6] != rhs[6]) || (m[7] != rhs[7]) || (m[8] != rhs[8]);
}

inline float mat3::operator[](int index) const
{
    return m[index];
}

inline float& mat3::operator[](int index)
{
    return m[index];
}

inline mat3 operator-(const mat3& rhs)
{
    return mat3(-rhs[0], -rhs[1], -rhs[2], -rhs[3], -rhs[4], -rhs[5], -rhs[6], -rhs[7], -rhs[8]);
}

inline mat3 operator*(float s, const mat3& rhs)
{
    return mat3(s*rhs[0], s*rhs[1], s*rhs[2], s*rhs[3], s*rhs[4], s*rhs[5], s*rhs[6], s*rhs[7], s*rhs[8]);
}

inline vec3 operator*(const vec3& v, const mat3& m)
{
    return vec3(v.x*m[0] + v.y*m[3] + v.z*m[6],  v.x*m[1] + v.y*m[4] + v.z*m[7],  v.x*m[2] + v.y*m[5] + v.z*m[8]);
}

#ifdef DEPRICATED
inline std::ostream& operator<<(std::ostream& os, const mat3& m)
{
    os << "(" << m[0] << ",\t" << m[1] << ",\t" << m[2] << ")\n"
       << "(" << m[3] << ",\t" << m[4] << ",\t" << m[5] << ")\n"
       << "(" << m[6] << ",\t" << m[7] << ",\t" << m[8] << ")\n";
    return os;
}
#endif

///////////////////////////////////////////////////////////////////////////
// inline functions for mat4
///////////////////////////////////////////////////////////////////////////
inline mat4::mat4()
{
    // initially identity matrix
    identity();
}

inline mat4::mat4(const float src[16])
{
    set(src);
}

inline mat4::mat4(float xx, float xy, float xz, float xw,
                        float yx, float yy, float yz, float yw,
                        float zx, float zy, float zz, float zw,
                        float wx, float wy, float wz, float ww)
{
    set(xx, xy, xz, xw,  yx, yy, yz, yw,  zx, zy, zz, zw,  wx, wy, wz, ww);
}

inline void mat4::set(const float src[16])
{
    m[0] = src[0];  m[1] = src[1];  m[2] = src[2];  m[3] = src[3];
    m[4] = src[4];  m[5] = src[5];  m[6] = src[6];  m[7] = src[7];
    m[8] = src[8];  m[9] = src[9];  m[10]= src[10]; m[11]= src[11];
    m[12]= src[12]; m[13]= src[13]; m[14]= src[14]; m[15]= src[15];
}

inline void mat4::set(float xx, float xy, float xz, float xw,
                         float yx, float yy, float yz, float yw,
                         float zx, float zy, float zz, float zw,
                         float wx, float wy, float wz, float ww)
{
    m[0] = xx;  m[1] = xy;  m[2] = xz;  m[3] = xw;
    m[4] = yx;  m[5] = yy;  m[6] = yz;  m[7] = yw;
    m[8] = zx;  m[9] = zy;  m[10]= zz;  m[11]= zw;
    m[12]= wx;  m[13]= wy;  m[14]= wz;  m[15]= ww;
}

inline void mat4::setRow(int index, const float row[4])
{
    m[index*4] = row[0];  m[index*4 + 1] = row[1];  m[index*4 + 2] = row[2];  m[index*4 + 3] = row[3];
}

inline void mat4::setRow(int index, const vec4& v)
{
    m[index*4] = v.x;  m[index*4 + 1] = v.y;  m[index*4 + 2] = v.z;  m[index*4 + 3] = v.w;
}

inline void mat4::setRow(int index, const vec3& v)
{
    m[index*4] = v.x;  m[index*4 + 1] = v.y;  m[index*4 + 2] = v.z;
}

inline void mat4::setColumn(int index, const float col[4])
{
    m[index] = col[0];  m[index + 4] = col[1];  m[index + 8] = col[2];  m[index + 12] = col[3];
}

inline void mat4::setColumn(int index, const vec4& v)
{
    m[index] = v.x;  m[index + 4] = v.y;  m[index + 8] = v.z;  m[index + 12] = v.w;
}

inline void mat4::setColumn(int index, const vec3& v)
{
    m[index] = v.x;  m[index + 4] = v.y;  m[index + 8] = v.z;
}

inline const float* mat4::get() const
{
    return m;
}

inline const float* mat4::getTranspose()
{
    tm[0] = m[0];   tm[1] = m[4];   tm[2] = m[8];   tm[3] = m[12];
    tm[4] = m[1];   tm[5] = m[5];   tm[6] = m[9];   tm[7] = m[13];
    tm[8] = m[2];   tm[9] = m[6];   tm[10]= m[10];  tm[11]= m[14];
    tm[12]= m[3];   tm[13]= m[7];   tm[14]= m[11];  tm[15]= m[15];
    return tm;
}

inline mat4& mat4::identity()
{
    m[0] = m[5] = m[10] = m[15] = 1.0f;
    m[1] = m[2] = m[3] = m[4] = m[6] = m[7] = m[8] = m[9] = m[11] = m[12] = m[13] = m[14] = 0.0f;
    return *this;
}

inline mat4 mat4::operator+(const mat4& rhs) const
{
    return mat4(m[0]+rhs[0],   m[1]+rhs[1],   m[2]+rhs[2],   m[3]+rhs[3],
                   m[4]+rhs[4],   m[5]+rhs[5],   m[6]+rhs[6],   m[7]+rhs[7],
                   m[8]+rhs[8],   m[9]+rhs[9],   m[10]+rhs[10], m[11]+rhs[11],
                   m[12]+rhs[12], m[13]+rhs[13], m[14]+rhs[14], m[15]+rhs[15]);
}

inline mat4 mat4::operator-(const mat4& rhs) const
{
    return mat4(m[0]-rhs[0],   m[1]-rhs[1],   m[2]-rhs[2],   m[3]-rhs[3],
                   m[4]-rhs[4],   m[5]-rhs[5],   m[6]-rhs[6],   m[7]-rhs[7],
                   m[8]-rhs[8],   m[9]-rhs[9],   m[10]-rhs[10], m[11]-rhs[11],
                   m[12]-rhs[12], m[13]-rhs[13], m[14]-rhs[14], m[15]-rhs[15]);
}

inline mat4& mat4::operator+=(const mat4& rhs)
{
    m[0] += rhs[0];    m[1] += rhs[1];    m[2] += rhs[2];    m[3] += rhs[3];
    m[4] += rhs[4];    m[5] += rhs[5];    m[6] += rhs[6];    m[7] += rhs[7];
    m[8] += rhs[8];    m[9] += rhs[9];    m[10] += rhs[10];  m[11] += rhs[11];
    m[12] += rhs[12];  m[13] += rhs[13];  m[14] += rhs[14];  m[15] += rhs[15];
    return *this;
}

inline mat4& mat4::operator-=(const mat4& rhs)
{
    m[0] -= rhs[0];    m[1] -= rhs[1];    m[2] -= rhs[2];    m[3] -= rhs[3];
    m[4] -= rhs[4];    m[5] -= rhs[5];    m[6] -= rhs[6];    m[7] -= rhs[7];
    m[8] -= rhs[8];    m[9] -= rhs[9];    m[10] -= rhs[10];  m[11] -= rhs[11];
    m[12] -= rhs[12];  m[13] -= rhs[13];  m[14] -= rhs[14];  m[15] -= rhs[15];
    return *this;
}

inline vec4 mat4::operator*(const vec4& rhs) const
{
    return vec4(m[0]*rhs.x  + m[1]*rhs.y  + m[2]*rhs.z  + m[3]*rhs.w,
                   m[4]*rhs.x  + m[5]*rhs.y  + m[6]*rhs.z  + m[7]*rhs.w,
                   m[8]*rhs.x  + m[9]*rhs.y  + m[10]*rhs.z + m[11]*rhs.w,
                   m[12]*rhs.x + m[13]*rhs.y + m[14]*rhs.z + m[15]*rhs.w);
}

inline vec3 mat4::operator*(const vec3& rhs) const
{
    return vec3(m[0]*rhs.x + m[1]*rhs.y + m[2]*rhs.z,
                   m[4]*rhs.x + m[5]*rhs.y + m[6]*rhs.z,
                   m[8]*rhs.x + m[9]*rhs.y + m[10]*rhs.z);
}

inline mat4 mat4::operator*(const mat4& n) const
{
    return mat4(m[0]*n[0]  + m[1]*n[4]  + m[2]*n[8]  + m[3]*n[12],   m[0]*n[1]  + m[1]*n[5]  + m[2]*n[9]  + m[3]*n[13],   m[0]*n[2]  + m[1]*n[6]  + m[2]*n[10]  + m[3]*n[14],   m[0]*n[3]  + m[1]*n[7]  + m[2]*n[11]  + m[3]*n[15],
                   m[4]*n[0]  + m[5]*n[4]  + m[6]*n[8]  + m[7]*n[12],   m[4]*n[1]  + m[5]*n[5]  + m[6]*n[9]  + m[7]*n[13],   m[4]*n[2]  + m[5]*n[6]  + m[6]*n[10]  + m[7]*n[14],   m[4]*n[3]  + m[5]*n[7]  + m[6]*n[11]  + m[7]*n[15],
                   m[8]*n[0]  + m[9]*n[4]  + m[10]*n[8] + m[11]*n[12],  m[8]*n[1]  + m[9]*n[5]  + m[10]*n[9] + m[11]*n[13],  m[8]*n[2]  + m[9]*n[6]  + m[10]*n[10] + m[11]*n[14],  m[8]*n[3]  + m[9]*n[7]  + m[10]*n[11] + m[11]*n[15],
                   m[12]*n[0] + m[13]*n[4] + m[14]*n[8] + m[15]*n[12],  m[12]*n[1] + m[13]*n[5] + m[14]*n[9] + m[15]*n[13],  m[12]*n[2] + m[13]*n[6] + m[14]*n[10] + m[15]*n[14],  m[12]*n[3] + m[13]*n[7] + m[14]*n[11] + m[15]*n[15]);
}

inline mat4& mat4::operator*=(const mat4& rhs)
{
    *this = *this * rhs;
    return *this;
}

inline bool mat4::operator==(const mat4& n) const
{
    return (m[0] == n[0])   && (m[1] == n[1])   && (m[2] == n[2])   && (m[3] == n[3]) &&
           (m[4] == n[4])   && (m[5] == n[5])   && (m[6] == n[6])   && (m[7] == n[7]) &&
           (m[8] == n[8])   && (m[9] == n[9])   && (m[10] == n[10]) && (m[11] == n[11]) &&
           (m[12] == n[12]) && (m[13] == n[13]) && (m[14] == n[14]) && (m[15] == n[15]);
}

inline bool mat4::operator!=(const mat4& n) const
{
    return (m[0] != n[0])   || (m[1] != n[1])   || (m[2] != n[2])   || (m[3] != n[3]) ||
           (m[4] != n[4])   || (m[5] != n[5])   || (m[6] != n[6])   || (m[7] != n[7]) ||
           (m[8] != n[8])   || (m[9] != n[9])   || (m[10] != n[10]) || (m[11] != n[11]) ||
           (m[12] != n[12]) || (m[13] != n[13]) || (m[14] != n[14]) || (m[15] != n[15]);
}

inline float mat4::operator[](int index) const
{
    return m[index];
}

inline float& mat4::operator[](int index)
{
    return m[index];
}

inline mat4 operator-(const mat4& rhs)
{
    return mat4(-rhs[0], -rhs[1], -rhs[2], -rhs[3], -rhs[4], -rhs[5], -rhs[6], -rhs[7], -rhs[8], -rhs[9], -rhs[10], -rhs[11], -rhs[12], -rhs[13], -rhs[14], -rhs[15]);
}

inline mat4 operator*(float s, const mat4& rhs)
{
    return mat4(s*rhs[0], s*rhs[1], s*rhs[2], s*rhs[3], s*rhs[4], s*rhs[5], s*rhs[6], s*rhs[7], s*rhs[8], s*rhs[9], s*rhs[10], s*rhs[11], s*rhs[12], s*rhs[13], s*rhs[14], s*rhs[15]);
}

inline vec4 operator*(const vec4& v, const mat4& m)
{
    return vec4(v.x*m[0] + v.y*m[4] + v.z*m[8] + v.w*m[12],  v.x*m[1] + v.y*m[5] + v.z*m[9] + v.w*m[13],  v.x*m[2] + v.y*m[6] + v.z*m[10] + v.w*m[14], v.x*m[3] + v.y*m[7] + v.z*m[11] + v.w*m[15]);
}

inline vec3 operator*(const vec3& v, const mat4& m)
{
    return vec3(v.x*m[0] + v.y*m[4] + v.z*m[8],  v.x*m[1] + v.y*m[5] + v.z*m[9],  v.x*m[2] + v.y*m[6] + v.z*m[10]);
}
#ifdef DEPRICATED
inline std::ostream& operator<<(std::ostream& os, const mat4& m)
{
    os << "(" << m[0]  << ",\t" << m[1]  << ",\t" << m[2]  <<  ",\t" << m[3] << ")\n"
       << "(" << m[4]  << ",\t" << m[5]  << ",\t" << m[6]  <<  ",\t" << m[7] << ")\n"
       << "(" << m[8]  << ",\t" << m[9]  << ",\t" << m[10] <<  ",\t" << m[11] << ")\n"
       << "(" << m[12] << ",\t" << m[13] << ",\t" << m[14] <<  ",\t" << m[15] << ")\n";
    return os;
}
#endif
#endif