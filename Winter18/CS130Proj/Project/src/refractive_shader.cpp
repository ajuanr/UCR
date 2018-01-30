#include <cmath>
#include "refractive_shader.h"
#include "ray.h"
#include "render_world.h"

vec3 Refractive_Shader::
Shade_Surface(const Ray& ray, const vec3& intersection_point,
        const vec3& same_side_normal, int recursion_depth,bool is_exiting) const
{
    //Hints: Use REFRACTIVE_INDICES::AIR for air refractive_index
    //       Use is_exiting to decide the refractive indices on the ray and transmission sides
    vec3 reflection_color;
    vec3 refraction_color;
    double reflectance_ratio=-1;

    vec3 D = ray.direction.normalized();
    vec3 N = same_side_normal.normalized();

    if(!world.disable_fresnel_refraction)
    {
        //TODO (Test 27+): Compute the refraction_color:
        double n_i = (is_exiting) ? refractive_index : REFRACTIVE_INDICES::AIR;        
        double n_r = (is_exiting) ? REFRACTIVE_INDICES::AIR : refractive_index;
        double cos_i = dot(D,N);
        if (cos_i < 0) cos_i = -cos_i;
        else N = -N;
        double underRoot = 1 - (((n_i/n_r)*(n_i/n_r)) * (1 - cos_i * cos_i));
        vec3 left = (n_i/n_r) * (D - dot(D,N) * N);
        double cos_r = sqrt(underRoot); 

        // - Check if it is total internal reflection. 
        if (underRoot < 0) {
        //      If so update the reflectance_ratio for total internal refraction
           reflectance_ratio = 1;
        }
        //      else, follow the instructions below
        else {
        //        (Test 28+): Update the reflectance_ratio 
            double numerParallel = n_r * cos_i - n_i * cos_r;
            double denomParallel = n_r * cos_i + n_i * cos_r;
            double R_parallel = pow((numerParallel/denomParallel),2); 
            double numerPerpen = n_i * cos_i - n_r * cos_r;
            double denomPerpen = n_i * cos_i + n_r * cos_r;
            double R_perpen = pow(numerPerpen/denomPerpen,2);
            reflectance_ratio = (R_parallel + R_perpen)/2;

        //        (Test 27+): Cast the refraction ray and compute the refraction_color
        vec3 T = (left - (cos_r * N)).normalized();
        Ray refractionRay(intersection_point, T);
        refraction_color = world.Cast_Ray(refractionRay, ++recursion_depth);
        } // end else
    }

    if(!world.disable_fresnel_reflection){
        //TODO:(Test 26+): Compute reflection_color:
        // - Cast Reflection Ray and get color
        vec3 R = (D - 2 * dot(N, D) * N ).normalized();
        Ray reflectedRay(intersection_point, R);
        reflection_color = world.Cast_Ray(reflectedRay, ++recursion_depth);
    }

    Enforce_Refractance_Ratio(reflectance_ratio);

    vec3 color;
    // TODO: (Test 26+) Compute final 'color' by blending reflection_color and refraction_color using 
    //                  reflectance_ratio
    color = (reflectance_ratio * reflection_color) + ((1 - reflectance_ratio) * refraction_color);
    return color;
}

void Refractive_Shader::
Enforce_Refractance_Ratio(double& reflectance_ratio) const
{
    if(world.disable_fresnel_reflection) reflectance_ratio=0;
    else if(world.disable_fresnel_refraction) reflectance_ratio=1;
}

