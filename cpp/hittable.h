#ifndef HITTABLE_H
#define HITTABLE_H

#include "utils.h"



class hit_record {
  public:
    point3 p;
    vec3 normal;
    double t;
    bool front_face;

    void set_face_normal(const ray& r, const vec3& outward_normal) {
    }
};


class hittable {
};


#endif
