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
<<<<<<< HEAD
    vec3 N = (is_exiting) ? -same_side_normal : same_side_normal;
=======
    vec3 N = same_side_normal;// = (is_exiting) ? -same_side_normal : same_side_normal;
    
>>>>>>> 277c684ffa71ff6d6e4b050fb7f85992def941c0
    vec3 C =  (ray.endpoint - intersection_point).normalized();        // camera position

    // ambient color
    ambient = world.ambient_color * world.ambient_intensity * color_ambient;

    // Calculate specular and diffuse compononent for each light source
    for (auto &light : world.lights) {
       // Light source stuff
       vec3 l = light->position - intersection_point;                     // vector towards light
       vec3 L = l.normalized();

       ////// diffuse color
       double I_d = std::max(dot(L,N),0.0);                                    // diffusion intensity
       vec3 light_color = light->Emitted_Light(ray)/ l.magnitude_squared(); // light color
       diffuse = light_color * I_d * color_diffuse;

       ////// Specular color
       vec3 R = ((2 * dot(L,N)) * N - L).normalized();                         // reflected vector
       double I_s = std::pow(std::max(dot(R,C),0.0), specular_power);
       specular = light_color * color_specular * I_s;
       

       if (world.enable_shadows) {                         // shadows enabled
          // Shadow ray stuff
          Ray shadowRay(intersection_point, L);           // ray towards light source
          Hit hit;
          Object* closestObj = world.Closest_Intersection(shadowRay,hit); 

          vec3 closestObjVec = shadowRay.Point(hit.t) - intersection_point; // distance to closest object
          if (closestObj) {
             if (closestObjVec.magnitude() > l.magnitude()) color += specular + diffuse;
          }
          else
             color += specular + diffuse;

       } // end enable shadows
       else	
          color += specular + diffuse; 	

       } // end for
    color += ambient;
    return color;
}
