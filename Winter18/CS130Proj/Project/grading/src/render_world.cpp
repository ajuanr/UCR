#include <limits>  // added by Juan
#include <vector>
#include "render_world.h"
#include "flat_shader.h"
#include "object.h"
#include "light.h"
#include "ray.h"


Render_World::Render_World()
    :background_shader(0),ambient_intensity(0),enable_shadows(true),
    recursion_depth_limit(3),disable_fresnel_reflection(false),disable_fresnel_refraction(false)
{}

Render_World::~Render_World()
{
    delete background_shader;
    for(size_t i=0;i<objects.size();i++) delete objects[i];
    for(size_t i=0;i<lights.size();i++) delete lights[i];
}

// Find the closest object of intersection and return the object that was
// intersected.  Record the Hit structure in hit.  If no intersection occurred,
// return NULL.  Note that in the case of a Boolean, the object returned will be
// the Boolean, but the object stored in hit will be the underlying primitive.
// Any intersection with t<=small_t should be ignored.
Object* Render_World::Closest_Intersection(const Ray& ray,Hit& hit)
{
    // DONE
    double min_t = std::numeric_limits<double>::max();
    Object* closest_object=0;
    hit.t = 0;
    for (auto obj = objects.begin(); obj != objects.end(); ++obj) {
       std::vector<Hit> hits;
       (*obj)->Intersection(ray,hits);
       for (auto h = hits.begin(); h != hits.end(); ++h) {
          if (h->t > small_t && h->t < min_t){
             closest_object = *obj;
             hit = *h;
             min_t = h->t; 
          }
       }
    } 
    return closest_object;
}

// set up the initial view ray and call
void Render_World::Render_Pixel(const ivec2& pixel_index)
{
    vec3 endPoint = camera.position;
    vec3 direction = (camera.World_Position(pixel_index) - endPoint).normalized();
    Ray ray(endPoint,direction); // DONE: set up the initial view ray here
    vec3 color=Cast_Ray(ray,1);
    camera.Set_Pixel(pixel_index,Pixel_Color(color));
}

void Render_World::Render()
{
    for(int j=0;j<camera.number_pixels[1];j++)
        for(int i=0;i<camera.number_pixels[0];i++)
            Render_Pixel(ivec2(i,j));
}

// cast ray and return the color of the closest intersected surface point,
// or the background color if there is no object intersection
vec3 Render_World::Cast_Ray(const Ray& ray,int recursion_depth)
{
    // TODO
    Hit hit;
    hit.ray_exiting = false; // default for ray in case of no objects
    vec3 color;  
    Object* closestObject = Closest_Intersection(ray,hit);
    vec3 dummy;
    vec3 intersection = ray.Point(hit.t);
    if (closestObject) {
       vec3 n = closestObject->Normal(intersection);
//       vec3 n = hit.object->Normal(intersection);
       color=closestObject->material_shader->Shade_Surface(ray,intersection, n, 1, hit.ray_exiting);
    } 
    else {
       color = background_shader->Shade_Surface(ray,intersection,dummy,1,hit.ray_exiting);
    }

    return color;
}