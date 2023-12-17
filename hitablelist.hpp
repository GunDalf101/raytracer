#ifndef HITABLELIST_HPP
#define HITABLELIST_HPP

#include "hitable.hpp"

class hit_list: public hitable {
    public:
        hit_list() {}
        hit_list (hitable **hit_arr, int n) {list = hit_arr; list_size = n;}
        virtual bool hitpoint (const ray& r, float t_min, float t_max, hit_record& rec) const;
        hitable **list;
        int list_size;
};

bool hit_list::hitpoint (const ray& r, float t_min, float t_max, hit_record& rec) const {
    hit_record temp;
    bool hit_some = false;
    double closest = t_max;
    for (int i = 0; i < list_size; i++) {
        if (list[i]->hitpoint(r, t_min, closest, temp)) {
            hit_some = true;
            closest = temp.t;
            rec = temp;
        }
    }
    return hit_some;
}

#endif