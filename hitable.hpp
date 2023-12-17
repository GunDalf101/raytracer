#ifndef HITABLE_HPP
#define HITABLE_HPP

#include "ray.hpp"

struct hit_record {
    float   t;
    vec3    p;
    vec3    normal;
};

class hitable {
    public:
        virtual bool hitpoint (const ray& r, float t_min, float t_max, hit_record& rec) const = 0;
};

#endif