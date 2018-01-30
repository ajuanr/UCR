#include "reflective_shader.h"
#include "ray.h"
#include "render_world.h"

vec3 Reflective_Shader::
Shade_Surface(const Ray& ray,const vec3& intersection_point,
    const vec3& same_side_normal,int recursion_depth,bool is_exiting) const
{
    
    vec3 color;
    vec3 N = same_side_normal;
    vec3 shaderColor = world.background_shader->Shade_Surface(ray, intersection_point, N, recursion_depth, is_exiting);
    color = shaderColor;
    if (recursion_depth <= world.recursion_depth_limit) {
       shaderColor = shader->Shade_Surface(ray,intersection_point, N, recursion_depth, is_exiting);
       vec3 L = ray.direction; 
       vec3 R = (L - 2 * dot(N, L) * N ).normalized(); 
       Ray reflectedRay(intersection_point, R);
       vec3 reflectedColor;
       reflectedColor += world.Cast_Ray(reflectedRay, ++recursion_depth);
       color = reflectedColor * reflectivity + (1 - reflectivity) * shaderColor;
    }
    return color;
}
