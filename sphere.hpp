#ifndef SPHERE_HPP
#define SPHERE_HPP

#include "hitable.hpp"

class sphere: public hitable{
    public:
        sphere() {}
        sphere(vec3 cen, float r) : center(cen), radius(r) {};
        virtual bool hitpoint (const ray& r, float t_min, float t_max, hit_record& rec) const;
        vec3 center;
        float radius;
};

bool sphere::hitpoint (const ray& r, float t_min, float t_max, hit_record& rec) const
{
    vec3 oc = r.origin() - center;
    float a = dot(r.direction(), r.direction());
    float b = 2.0 * dot(oc, r.direction());
    float c = dot(oc,oc) - radius * radius;
    float discriminant = b*b - 4*a*c;
    if (discriminant > 0) {
        float solv = (-b - sqrt(discriminant)) / (2.0 * a);
        if (solv < t_max && solv > t_min) {
            rec.t = solv;
            rec.p = r.point_at_parameter(rec.t);
            rec.normal = (rec.p - center) / radius;
            return true;
        }
        solv = (-b + sqrt(discriminant)) / (2.0 * a);
        if (solv < t_max && solv > t_min) {
            rec.t = solv;
            rec.p = r.point_at_parameter(rec.t);
            rec.normal = (rec.p - center) / radius;
            return true;
        }
    }
    return false;
}


#endif