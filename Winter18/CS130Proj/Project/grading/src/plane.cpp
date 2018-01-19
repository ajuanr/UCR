#include "plane.h"
#include "ray.h"
#include <cfloat>


// Intersect with the half space defined by the plane.  The plane's normal
// points outside.  If the ray starts on the "inside" side of the plane, be sure
// to record a hit with t=0 as the first entry in hits.
bool Plane::
Intersection(const Ray& ray, std::vector<Hit>& hits) const
{
    // TODO
    double denominator = dot(normal, ray.direction);
    if (denominator) {
       Hit hit;
       double t1 = dot((x1- ray.endpoint),normal)/denominator; 
       hit.t = t1;
       hit.ray_exiting = false;
       hits.push_back(hit);
       return true;
    }
    return false;
}

vec3 Plane::
Normal(const vec3& point) const
{
    return normal;
}
