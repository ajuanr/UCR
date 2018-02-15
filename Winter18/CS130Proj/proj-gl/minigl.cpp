/**
 * minigl.cpp
 * -------------------------------
 * Implement miniGL here.
 *
 * You may include minigl.h and any of the standard C++ libraries.
 * No other includes are permitted.  Other preprocessing directives
 * are also not permitted.  These requirements are strictly
 * enforced.  Be sure to run a test grading to make sure your file
 * passes the sanity tests.
 *
 * The behavior of the routines your are implenting is documented here:
 * https://www.opengl.org/sdk/docs/man2/
 * Note that you will only be implementing a subset of this.  In particular,
 * you only need to implement enough to pass the tests in the suite.
 */

#include "minigl.h"
#include "vec.h"
#include "mat.h"
#include <algorithm>
#include <cassert>
#include <cmath>
#include <vector>
#include <cstdio>

using namespace std;

/**
 * Useful data types
 */
typedef mat<MGLfloat,4,4> mat4; //data structure storing a 4x4 matrix, see mat.h
typedef mat<MGLfloat,3,3> mat3; //data structure storing a 3x3 matrix, see mat.h
typedef vec<MGLfloat,4> vec4;   //data structure storing a 4 dimensional vector, see vec.h
typedef vec<MGLfloat,3> vec3;   //data structure storing a 3 dimensional vector, see vec.h
typedef vec<MGLfloat,2> vec2;   //data structure storing a 2 dimensional vector, see vec.h


vec3 color;
vec4 vertices;

struct Vertex {
    vec3 color;
    vec4 position;
};

vector<Vertex> verticesList;

MGLpoly_mode currMode; // for GLbegin

struct Triangle {
//  Triangle() {vertices.reserve(3);}
  vector<Vertex> vertices;

};
vector<Triangle> triangleList;


/**
 * Standard macro to report errors
 */
inline void MGL_ERROR(const char* description) {
    printf("%s\n", description);
    exit(1);
}

// helper function
MGLfloat getArea(Vertex a, Vertex b, Vertex c) {
   MGLfloat ax, ay, bx, by, cx, cy;

   ax = a.position[0];
   ay = a.position[1]; 
   bx = b.position[0];
   by = b.position[1]; 
   cx = c.position[0];
   cy = c.position[1]; 

   return ax * (by - cy) + ay * (cx - bx) + (bx * cy - by * cx);
}

// helper function
void Raterize_Triangle(const Triangle& tri, int width, int height, MGLpixel *data) {
    Vertex A = tri.vertices.at(0);

    MGLfloat x = A.position[0];
    MGLfloat y = A.position[1];
    MGLfloat i = (x + 1) * 0.5 * width;
    MGLfloat j = (y + 1) * 0.5 * height;
    i -= 0.5;
    j -= 0.5;

    A.position[0] = i;
    A.position[1] = j;

    Vertex B = tri.vertices.at(1);

    x = B.position[0];
    y = B.position[1];
    i = (x + 1) * 0.5 * width;
    j = (y + 1) * 0.5 * height;
    i -= 0.5;
    j -= 0.5;

    B.position[0] = i;
    B.position[1] = j;

    Vertex C = tri.vertices.at(2);

    x = C.position[0];
    y = C.position[1];
    i = (x + 1) * 0.5 * width;
    j = (y + 1) * 0.5 * height;
    i -= 0.5;
    j -= 0.5;

    C.position[0] = i;
    C.position[1] = j;

    for (int x = 0; x != width; ++x) {
        for (int y = 0; y != height; ++y) {
           Vertex I;
           I.position[0] = x;
           I.position[1] = y; 

           MGLfloat areaABC = getArea(A, B, C);

           MGLfloat areaPBC = getArea(I, B, C);
           MGLfloat alpha = areaPBC / areaABC;

           MGLfloat areaAPC = getArea(A, I, C);
           MGLfloat beta = areaAPC /areaABC;
       
           MGLfloat areaABP = getArea(A, B, I);
           MGLfloat gamma = areaABP /areaABC;
//std::cout << "alpha " << alpha << " beta " << beta << " gamma " << gamma << std::endl;
           if (alpha > 0 && beta > 0 && gamma > 0) {
              data[x + y*width] = Make_Pixel(255,255,255);
           } 
       }
   }
}

/**
 * Read pixel data starting with the pixel at coordinates
 * (0, 0), up to (width,  height), into the array
 * pointed to by data.  The boundaries are lower-inclusive,
 * that is, a call with width = height = 1 would just read
 * the pixel at (0, 0).
 *
 * Rasterization and z-buffering should be performed when
 * this function is called, so that the data array is filled
 * with the actual pixel values that should be displayed on
 * the two-dimensional screen.
 */
void mglReadPixels(MGLsize width,
                   MGLsize height,
                   MGLpixel *data)
{
    for (unsigned int i = 0; i != width; ++i) {
       for (unsigned int j = 0; j != height; ++j) {
          data[i+j*width] = Make_Pixel(0, 0, 0);
       }
    }
    for (auto triangle : triangleList) {
        Raterize_Triangle(triangle, width, height, data);
    }
    triangleList.clear();
}

/**
 * Start specifying the vertices for a group of primitives,
 * whose type is specified by the given mode.
 */
void mglBegin(MGLpoly_mode mode)
{
     currMode = mode;
}


/**
 * Stop specifying the vertices for a group of primitives.
 */
void mglEnd()
{
    if (currMode == MGL_TRIANGLES) {
       for (unsigned int vertex = 0; vertex < verticesList.size();vertex +=3 ) {// incremented in loop
           Triangle triangle;
           triangle.vertices.push_back(verticesList.at(vertex));     
           triangle.vertices.push_back(verticesList.at(vertex+1));
           triangle.vertices.push_back(verticesList.at(vertex+2));
           triangleList.push_back(triangle);
       }
    }

    if (currMode == MGL_QUADS) {
        for (unsigned int i = 0; i < verticesList.size(); i += 4) {
        Triangle t1,t2;
        unsigned int bottomLeft, topLeft, bottomRight, topRight;
	bottomLeft = i;
        bottomRight = i + 1;
        topRight = i + 2;
        topLeft = i + 3;

        t1.vertices[0] = verticesList.at(bottomLeft);
        t1.vertices[0] = verticesList.at(topRight);
        t1.vertices[0] = verticesList.at(topLeft);
        
        t2.vertices[0] = verticesList.at(bottomLeft);
        t2.vertices[0] = verticesList.at(bottomRight);
        t2.vertices[0] = verticesList.at(topRight);

        triangleList.push_back(t1);
        triangleList.push_back(t2);
        }
    }
    verticesList.clear();
}

/**
 * Specify a two-dimensional vertex; the x- and y-coordinates
 * are explicitly specified, while the z-coordinate is assumed
 * to be zero.  Must appear between calls to mglBegin() and
 * mglEnd().
 */
void mglVertex2(MGLfloat x,
                MGLfloat y)
{
   mglVertex3(x,y,0);
}

/**
 * Specify a three-dimensional vertex.  Must appear between
 * calls to mglBegin() and mglEnd().
 */
void mglVertex3(MGLfloat x,
                MGLfloat y,
                MGLfloat z)
{
    Vertex Position;
    vec4 position4d;
    position4d[0] = x;
    position4d[1] = y;
    position4d[2] = z;
    position4d[3] = 1;
    Position.position = position4d;

    verticesList.push_back(Position);
}

/**
 * Set the current matrix mode (modelview or projection).
 */
void mglMatrixMode(MGLmatrix_mode mode)
{
}

/**
 * Push a copy of the current matrix onto the stack for the
 * current matrix mode.
 */
void mglPushMatrix()
{
}

/**
 * Pop the top matrix from the stack for the current matrix
 * mode.
 */
void mglPopMatrix()
{
}

/**
 * Replace the current matrix with the identity.
 */
void mglLoadIdentity()
{
}

/**
 * Replace the current matrix with an arbitrary 4x4 matrix,
 * specified in column-major order.  That is, the matrix
 * is stored as:
 *
 *   ( a0  a4  a8  a12 )
 *   ( a1  a5  a9  a13 )
 *   ( a2  a6  a10 a14 )
 *   ( a3  a7  a11 a15 )
 *
 * where ai is the i'th entry of the array.
 */
void mglLoadMatrix(const MGLfloat *matrix)
{
}

/**
 * Multiply the current matrix by an arbitrary 4x4 matrix,
 * specified in column-major order.  That is, the matrix
 * is stored as:
 *
 *   ( a0  a4  a8  a12 )
 *   ( a1  a5  a9  a13 )
 *   ( a2  a6  a10 a14 )
 *   ( a3  a7  a11 a15 )
 *
 * where ai is the i'th entry of the array.
 */
void mglMultMatrix(const MGLfloat *matrix)
{
}

/**
 * Multiply the current matrix by the translation matrix
 * for the translation vector given by (x, y, z).
 */
void mglTranslate(MGLfloat x,
                  MGLfloat y,
                  MGLfloat z)
{
}

/**
 * Multiply the current matrix by the rotation matrix
 * for a rotation of (angle) degrees about the vector
 * from the origin to the point (x, y, z).
 */
void mglRotate(MGLfloat angle,
               MGLfloat x,
               MGLfloat y,
               MGLfloat z)
{
}

/**
 * Multiply the current matrix by the scale matrix
 * for the given scale factors.
 */
void mglScale(MGLfloat x,
              MGLfloat y,
              MGLfloat z)
{
}

/**
 * Multiply the current matrix by the perspective matrix
 * with the given clipping plane coordinates.
 */
void mglFrustum(MGLfloat left,
                MGLfloat right,
                MGLfloat bottom,
                MGLfloat top,
                MGLfloat near,
                MGLfloat far)
{
}

/**
 * Multiply the current matrix by the orthographic matrix
 * with the given clipping plane coordinates.
 */
void mglOrtho(MGLfloat left,
              MGLfloat right,
              MGLfloat bottom,
              MGLfloat top,
              MGLfloat near,
              MGLfloat far)
{
}

/**
 * Set the current color for drawn shapes.
 */
void mglColor(MGLfloat red,
              MGLfloat green,
              MGLfloat blue)
{
	color[0] = red;
	color[1] = green;
	color[2] = blue;
}