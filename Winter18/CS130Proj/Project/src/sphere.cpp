#include <algorithm>  // added by Juan, for max 
#include "sphere.h"
#include "ray.h"

// Determine if the ray intersects with the sphere
bool Sphere::Intersection(const Ray& ray, std::vector<Hit>& hits) const
{
    // TODO
    vec3 u = ray.direction;
    vec3 v = ray.endpoint - center;
    double disc = (4 * dot(u,v) * dot(u,v))- 4 * (dot(v,v) - radius * radius);
    if (disc >= 0) {               // there is an intersection
       Hit h1,h2;
       double t;
       double a = 1;
       double b =  2 * dot(v,u);
       double c = dot(v,v) - radius*radius;


       if (disc==0) {              // one intersection
          t = -b/(2*a*c);   
          h1.t = t;
          h1.ray_exiting = false;
          hits.push_back(h1);
       }       
       else {                     // two intersections
          double t1 = (-b-sqrt(disc))/(2*a);
          double t2 = (-b+sqrt(disc))/(2*a);
          if (t1>0) {
             h1.t = t1;
             h1.ray_exiting = false;
             h2.t = t2;
             h2.ray_exiting = true;
             hits.push_back(h1);
             hits.push_back(h2);
          }
          else if (t2>0){         
             h1.t = t2;
             h1.ray_exiting = true;
             hits.push_back(h1);
          }
          else {                  // no solutions
             return false;
          }
       }
       return true;
    }
    return false;                 // no intersections
}

vec3 Sphere::Normal(const vec3& point) const
{
    vec3 normal;
    // TODO: set the normal
    vec3 pToC = point - center;
    normal = pToC/ pToC.magnitude();
    return normal;
}
