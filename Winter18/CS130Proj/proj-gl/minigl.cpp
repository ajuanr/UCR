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
MGLfloat front,back;

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
vector<mat4> projectionStack={identity};
vector<mat4> modelviewStack = {identity};

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
mat4& topOfStack() {
    if (currMatMode == MGL_MODELVIEW)
       return modelviewStack.back();
    if (currMatMode == MGL_PROJECTION)
       return projectionStack.back();
    MGL_ERROR("No stack, or unkown stack, referenced");
    exit(1);
}

void modifyStack(mat4 operation) {
    topOfStack() = topOfStack() * operation;
}

MGLfloat area(Vertex a, Vertex b, Vertex c) {
   MGLfloat ax, ay, bx, by, cx, cy;

   ax = a.position[0];
   ay = a.position[1]; 
   bx = b.position[0];
   by = b.position[1]; 
   cx = c.position[0];
   cy = c.position[1]; 

   return ax * (by - cy) + ay * (cx - bx) + (bx * cy - by * cx);
}

void toPixelCoord(Vertex &v, int width, int height) {
    MGLfloat x = v.position[0]/v.position[3]; // divide by w([3]) for frustum
    MGLfloat y = v.position[1]/v.position[3];
    MGLfloat i = (x + 1) * 0.5f * width;
    MGLfloat j = (y + 1) * 0.5f * height;
    i -= 0.5f;
    j -= 0.5f;

    v.position[0] = i;
    v.position[1] = j;
}

// helper function
void Raterize_Triangle(const Triangle& tri, int width, int height, MGLpixel *data) {
    Vertex A = tri.vertices.at(0);
    Vertex B = tri.vertices.at(1);
    Vertex C = tri.vertices.at(2);
    toPixelCoord(A,width,height);
    toPixelCoord(B,width,height);
    toPixelCoord(C,width,height);

    // bounding box - optimization
    int xMax = ceil(max(A.position[0],max(B.position[0],C.position[0])));
    int xMin = floor(min(A.position[0],min(B.position[0],C.position[0])));
    int yMax = ceil(max(A.position[1],max(B.position[1],C.position[1])));
    int yMin = floor(min(A.position[1],min(B.position[1],C.position[1])));

    // for clipping stuff
    if (front == 1) front = -1; 
    if (back == 0) back = 100;

    // pre-compute this before entering the loop
    MGLfloat areaABC = area(A, B, C);
    vec3 c0 = A.color*255;
    vec3 c1 = B.color*255;
    vec3 c2 = C.color*255;

    for (int x = xMin; x != xMax; ++x) {
        for (int y = yMin; y != yMax; ++y) {
	   if (x < 0 || x > width || y < 0 || y > height) break; // clipping along edges
           Vertex P;
           P.position[0] = x;
           P.position[1] = y; 

           MGLfloat areaPBC = area(P, B, C);
           MGLfloat alpha = areaPBC / areaABC;

           MGLfloat areaAPC = area(A, P, C);
           MGLfloat beta = areaAPC /areaABC;
       
           MGLfloat areaABP = area(A, B, P);
           MGLfloat gamma = areaABP /areaABC;

           if (alpha >= 0 && beta >= 0 && gamma >= 0) {
              MGLfloat z = alpha * A.position[2] + beta * B.position[2] + gamma * C.position[2];
                 if (z < zBuffer[x + y*width] ) {
                    vec3 c =  alpha*c0+beta*c1+gamma*c2;
		    if (z >= front && z <= back) // clipping along plane
                      data[x + y*width] = Make_Pixel(c[0],c[1],c[2]);
                    zBuffer[x + y*width] = A.position[2];
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
    zBuffer = vector<MGLfloat>(width*height, 10.e30f);
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

    if (currMatMode == MGL_PROJECTION) {
        projectionStack.push_back(projectionStack.back());
    }
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
    topOfStack() = identity;
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

    topOfStack() = temp;
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

    modifyStack(temp);
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
   MGLfloat denom = sqrt(x*x+y*y+z*z);

   // normalize the coordinates
   x /= denom;
   y /= denom;
   z /= denom;

   MGLfloat d = 1-c;
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

    front = near;
    back = far;
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
    front = near;
    back = far;

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
