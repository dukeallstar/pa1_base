#ifndef INTERVAL_H
#define INTERVAL_H

class interval {
  public:
    double min, max;

    interval() : min(+infinity), max(-infinity) {} // Default interval is empty

    interval(double _min, double _max) : min(_min), max(_max) {}

    double size() const {
    }

    interval expand(double delta) const {
    }

    bool contains(double x) const {
    }

    bool surrounds(double x) const {
    }

    double clamp(double x) const {
    }

    static const interval empty, universe;
};

const interval interval::empty    = ;
const interval interval::universe = ;


#endif
