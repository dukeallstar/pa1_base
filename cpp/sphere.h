#ifndef SPHERE_H
#define SPHERE_H

#include "utils.h"

#include "hittable.h"


class sphere : public hittable {
  public:
    sphere(point3 _center, double _radius)
      : center(_center), radius(_radius)  {}

    bool hit(const ray& r, interval ray_t, hit_record& rec) const override {
    }

  private:
    point3 center;
    double radius;
};


#endif
