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
    vec3 n = (is_exiting) ? -same_side_normal : same_side_normal;
    
    // ambient color
    ambient = world.ambient_color*world.ambient_intensity*color_ambient;

//    if (world.enable_shadows) {
       for (auto light = world.lights.begin(); light != world.lights.end(); ++light) {
          vec3 l = ((*light)->position - intersection_point); // vector towards light
          vec3 r = ((2 * dot(l,n)) * n - l).normalized();                        // reflected vector
          vec3 c =  (world.camera.position).normalized();        // camera position
          // Shadow ray stuff
          Ray shadow_ray(intersection_point, l.normalized());
          Hit hit;
          Object* closestObject = world.Closest_Intersection(shadow_ray,hit); 
          //if (!closestObject) break;

          ////// diffuse color
          double I_d = dot(l.normalized(),n);                    // diffusion intensity
          I_d = std::max(I_d,0.0);
          vec3 light_color = (*light)->Emitted_Light(ray)/ l.magnitude_squared();        // light color
       
          diffuse = light_color *I_d * color_diffuse;

          ////// Specular
          double I_s = std::max(dot(r,c),0.0);
          I_s = std::pow(I_s,specular_power);
          specular = color_specular*light_color * I_s;
       
       color += specular+ diffuse;
//    }
    }

    color += ambient;
    return color;
}
