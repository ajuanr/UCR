#include <algorithm>
#include <cmath>
#include "light.h"
#include "phong_shader.h"
#include "ray.h"
#include "render_world.h"
#include "object.h"

vec3 Phong_Shader::
Shade_Surface(const Ray& ray,const vec3& intersection_point,
    const vec3& same_side_normal,int recursion_depth,bool is_exiting) const 
{
    vec3 color;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
                          // ray pointing in : ray pointing out
    vec3 N = (is_exiting) ? -same_side_normal : same_side_normal;
    
//    vec3 C =  (world.camera.position - intersection_point).normalized();        // camera position
    vec3 C =  (ray.endpoint - intersection_point).normalized();        // camera position

    // ambient color
    ambient = world.ambient_color * world.ambient_intensity * color_ambient;

    //if (world.enable_shadows) return color;
    for (auto light = world.lights.begin(); light != world.lights.end(); ++light) {
       // Light source stuff
       vec3 l = ((*light)->position - intersection_point); // vector towards light
       vec3 L = l.normalized();

       ////// diffuse color
       double I_d = std::max(dot(L,N),0.0);                    // diffusion intensity
       vec3 light_color = (*light)->Emitted_Light(ray)/ l.magnitude_squared();        // light color
       diffuse = light_color * I_d * color_diffuse;

       ////// Specular color
       vec3 R = ((2 * dot(L,N)) * N - L).normalized();                        // reflected vector
       double I_s = std::pow(std::max(dot(R,C),0.0), specular_power);
       specular = light_color *color_specular * I_s ;
       
       // Shadow ray stuff
       Ray shadow_ray(intersection_point, L);
       Hit hit;
       Object* closestObject = world.Closest_Intersection(shadow_ray,hit); 
       
       double closestIntersectionDistance = shadow_ray.Point(hit.t).magnitude();

       if (world.enable_shadows) {                           // shadows enabled
          if (closestObject) {                               // intersected an object
            if (closestIntersectionDistance > l.magnitude()) 
               continue;                                     // object was behind light 
          }
            if (!closestObject){                             // shadow ray did not hit object
                  color += specular + diffuse;               // add components
            }
       }
       else {                                               // shadows not enabled
               color += specular + diffuse;                  // add the specular and diffuse
       }
    }
    color += ambient;
    return color;
}
