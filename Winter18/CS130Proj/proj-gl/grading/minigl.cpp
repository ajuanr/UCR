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


// MODES
MGLpoly_mode currMode;
MGLmatrix_mode currMatMode;

// Global Variables
vec3 color; 	// stores the color
vec4 vertices;
mat4 identity = {{1.f,0.f,0.f,0.f, 0.f,1.f,0.f,0.f, 0.f,0.f,1.f,0.f, 0.f,0.f,0.f,1.f}};
vector<MGLfloat> zBuffer;

// Structures
struct Vertex {
    vec3 color;
    vec4 position;
};

struct Triangle {
  vector<Vertex> vertices;
};

// Lists
vector<Vertex> verticesList;
vector<Triangle> triangleList;
vector<mat4> projectionStack;
vector<mat4> modelviewStack;


/**
 * Standard macro to report errors
 */
inline void MGL_ERROR(const char* description) {
    printf("%s\n", description);
    exit(1);
}

// helper function
//
//
void modifyStack(mat4 operation) {
    if (currMatMode == MGL_MODELVIEW)
       modelviewStack.back() = modelviewStack.back() * operation;
    if (currMatMode == MGL_PROJECTION)
       projectionStack.back() = projectionStack.back() * operation;
}

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

    MGLfloat x = A.position[0]/A.position[3]; // divide by w([3]) for frustum
    MGLfloat y = A.position[1]/A.position[3];
    MGLfloat i = (x + 1) * 0.5f * width;
    MGLfloat j = (y + 1) * 0.5f * height;
    i -= 0.5f;
    j -= 0.5f;

    A.position[0] = i;
    A.position[1] = j;

    Vertex B = tri.vertices.at(1);

    x = B.position[0]/B.position[3];
    y = B.position[1]/B.position[3];
    i = (x + 1) * 0.5f * width;
    j = (y + 1) * 0.5f * height;
    i -= 0.5f;
    j -= 0.5f;

    B.position[0] = i;
    B.position[1] = j;

    Vertex C = tri.vertices.at(2);

    x = C.position[0]/C.position[3];
    y = C.position[1]/C.position[3];
    i = (x + 1) * 0.5f * width;
    j = (y + 1) * 0.5f * height;
    i -= 0.5f;
    j -= 0.5f;

    C.position[0] = i;
    C.position[1] = j;

    // bounding box - optimization
    int xMax = ceil(max(A.position[0],max(B.position[0],C.position[0])));
    int xMin = floor(min(A.position[0],min(B.position[0],C.position[0])));
    int yMax = ceil(max(A.position[1],max(B.position[1],C.position[1])));
    int yMin = floor(min(A.position[1],min(B.position[1],C.position[1])));

    for (int x = xMin; x != xMax; ++x) {
        for (int y = yMin; y != yMax; ++y) {
           Vertex I;
           I.position[0] = x;
           I.position[1] = y; 
           I.color = color;

           MGLfloat areaABC = getArea(A, B, C);

           MGLfloat areaPBC = getArea(I, B, C);
           MGLfloat alpha = areaPBC / areaABC;

           MGLfloat areaAPC = getArea(A, I, C);
           MGLfloat beta = areaAPC /areaABC;
       
           MGLfloat areaABP = getArea(A, B, I);
           MGLfloat gamma = areaABP /areaABC;
        
           if (alpha > 0 && beta > 0 && gamma > 0) {
              vec3 newColor = A.color*255;
              if (zBuffer[x+y*width] > A.position[2]) {
                 data[x + y*width] = Make_Pixel(newColor[0],newColor[1],newColor[2]);
                 zBuffer[x+y*width] = A.position[2];
              }
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
    zBuffer = vector<MGLfloat>(width*height, 10.e6f);
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
       for (unsigned int vertex = 0; vertex < verticesList.size();vertex +=3 ) {
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

           t1.vertices.push_back(verticesList.at(bottomLeft));
           t1.vertices.push_back(verticesList.at(bottomRight));
           t1.vertices.push_back(verticesList.at(topRight));
        
           t2.vertices.push_back(verticesList.at(bottomLeft));
           t2.vertices.push_back(verticesList.at(topRight));
           t2.vertices.push_back(verticesList.at(topLeft));

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
    Position.color = color;  // assign current color to Position vertex
    vec4 position4d={x,y,z,1};
    
    Position.position = projectionStack.back()*(modelviewStack.back()*position4d);

    verticesList.push_back(Position);
}

/**
 * Set the current matrix mode (modelview or projection).
 */
void mglMatrixMode(MGLmatrix_mode mode)
{
    currMatMode = mode;
}

/**
 * Push a copy of the current matrix onto the stack for the
 * current matrix mode.
 */
void mglPushMatrix()
{
    if (currMatMode == MGL_MODELVIEW) 
        modelviewStack.push_back(modelviewStack.back());

    if (currMatMode == MGL_PROJECTION) 
        projectionStack.push_back(projectionStack.back());
}

/**
 * Pop the top matrix from the stack for the current matrix
 * mode.
 */
void mglPopMatrix()
{
    if (currMatMode == MGL_MODELVIEW) { 
        if (modelviewStack.empty()) MGL_ERROR("Can't pop from empty modelview stack");
        modelviewStack.pop_back();
    }
    if (currMatMode == MGL_PROJECTION) {
        if (projectionStack.empty()) MGL_ERROR("Can't pop from empty projection stack");
        projectionStack.pop_back();
    }
}

/**
 * Replace the current matrix with the identity.
 */
void mglLoadIdentity()
{
 if (currMatMode ==  MGL_PROJECTION)  {
     if (projectionStack.empty()) projectionStack.push_back(identity);
     else  projectionStack.back() = identity;
 }
 if (currMatMode ==  MGL_MODELVIEW) ;
     if (modelviewStack.empty()) modelviewStack.push_back(identity);
     else modelviewStack.back() = identity;
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
    mat4 temp = identity;
    for (int i = 0; i < 4; ++i)
        for (int j = 0; j <4; ++j)
            temp(i,j) = matrix[i+j*4];
    if (currMatMode == MGL_MODELVIEW)
       modelviewStack.back() = temp;

    if (currMatMode == MGL_PROJECTION)
       projectionStack.back() = temp;
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
    mat4 temp = identity;
    for (int i = 0; i < 4; ++i)
        for (int j = 0; j <4; ++j)
            temp(i,j) = matrix[i+j*4];
    if (currMatMode == MGL_MODELVIEW)
       modelviewStack.back() = modelviewStack.back() * temp;

    if (currMatMode == MGL_PROJECTION)
       projectionStack.back() = projectionStack.back() * temp;
}

/**
 * Multiply the current matrix by the translation matrix
 * for the translation vector given by (x, y, z).
 */
void mglTranslate(MGLfloat x,
                  MGLfloat y,
                  MGLfloat z)
{
   mat4 translate = {{1.f, 0.f, 0.f, 0.f,
                      0.f, 1.f, 0.f, 0.f,
                      0.f, 0.f, 1.f, 0.f,
                      x, y, z, 1.f}};
   modifyStack(translate);
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
   angle = angle/180*M_PI;
   MGLfloat c = cos(angle);
   MGLfloat s = sin(angle);
   vec3 normalized = {x,y,z}; 
   normalized.normalized();
   MGLfloat denom = sqrt(x*x+y*y+z*z);

   // normalize the coordinates
   x /= denom;
   y /= denom;
   z /= denom;

   MGLfloat d= 1-c;
   mat4 rotate = {{x*x*d+c, y*x*d+z*s, x*z*d-y*s, 0.f,
                   x*y*d-z*s, y*y*d+c, y*z*d+x*s, 0.f,
                   x*z*d+y*s, y*z*d-x*s, z*z*d+c, 0.f,
                   0.f, 0.f, 0.f, 1.f}};
   modifyStack(rotate);
}

/**
 * Multiply the current matrix by the scale matrix
 * for the given scale factors.
 */
void mglScale(MGLfloat x,
              MGLfloat y,
              MGLfloat z)
{
   mat4 scaleMatrix = {{x, 0.f, 0.f, 0.f,
                        0.f, y, 0.f, 0.f,
                        0.f, 0.f, z, 0.f,
                        0.f,0.f, 0.f, 1.f}};

   modifyStack(scaleMatrix);
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
    MGLfloat A = (right + left) / (right - left);
    MGLfloat B = (top + bottom) / (top - bottom);  
    MGLfloat C = -((far + near)  / (far - near));
    MGLfloat D = -((2.f * far * near) / (far - near));

    mat4 frust= {{(2.f*near/(right-left)), 0.f,0.f,0.f,
                    0.f, (2.f*near/(top-bottom)), 0.f,0.f,
                    A, B, C, -1.f,
                    0.f, 0.f, D, 0.f}}; 

    modifyStack(frust);
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
    MGLfloat rl = right - left;
    MGLfloat tb = top - bottom;
    MGLfloat fn = far - near;

    MGLfloat tx = -(right+left)/rl;
    MGLfloat ty = -(top+bottom)/tb;
    MGLfloat tz = -(far+near)/fn;

    mat4 ortho=  {{2.f/rl,0.f,0.f,0.f,
                0.f,2.f/tb,0.f,0.f,
                0.f,0.f,-2.f/fn,0.f,
                tx, ty, tz, 1.f}};

   modifyStack(ortho);
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
