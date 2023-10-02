#ifndef HITTABLE_LIST_H
#define HITTABLE_LIST_H

#include "utils.h"

#include "hittable.h"

#include <memory>
#include <vector>


class hittable_list : public hittable {
  public:
    std::vector<shared_ptr<hittable>> objects;

    hittable_list() {}
    hittable_list(shared_ptr<hittable> object) { add(object); }

    void clear() {  }

    void add(shared_ptr<hittable> object) {
    }

    bool hit(const ray& r, interval ray_t, hit_record& rec) const override {
    }
};


#endif
