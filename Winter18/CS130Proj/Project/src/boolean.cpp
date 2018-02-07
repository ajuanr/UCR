#include "boolean.h"


// Determine if the ray intersects with the boolean of A and B.
bool Boolean::Intersection(const Ray& ray, std::vector<Hit>& hits) const
{
    if (type == Type::type_intersection) {
        std::vector<Hit> vecA;
        std::vector<Hit> vecB;
        std::vector<Hit> both;
        bool ret = false;
        if (A->Intersection(ray,vecA)) {
            for (auto h : vecA) {
                if (h.t > small_t) {
                   both.push_back(h); 
                }
            } 
            ret= true;
        }
        if (B->Intersection(ray,vecB)) { 
            ret= true;
            for (auto h : vecB) {
                if (h.t > small_t) {
                   both.push_back(h); 
                }
            } 
        }
        if (ret){
            int smaller = std::min(vecA.size(), vecB.size());
            for (int i = 0; i != smaller; ++i  ){
              Hit hit = (vecA[i].t < vecB[i].t)? vecA[i] : vecB[i];
              if (hit.t > small_t)
               hits.push_back(hit); 
              }
        return ret;
           }
        return false;
    }
    
    return false;
}

// This should never be called.
vec3 Boolean::Normal(const vec3& point) const
{
    assert(true);
    return vec3();
}
