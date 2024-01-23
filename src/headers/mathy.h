//
// Created by Manuel Suarez on 22/01/2024.
//

#ifndef DOOMY_MATHY_H
#define DOOMY_MATHY_H

#define RAY_X_SPEED 1
#define RAY_Y_SPEED 1

// using from here sqrt and pow, and abs
#include <cmath>

class point {

    int x, y;

public:

    point (int x, int y);

    point (point const &other);

    void set_x (int x);

    void set_y (int y);

    double get_distance (const point& other);

    int operator[] (int i) const;

    point& operator= (const point& p);
};


class line {
    // s for start, e for end
    point s,e;

public:

    // explicit to avoid weird conversions
    line (const point& s, const point& e);

    line (line const &other);

//    point get_e () {
//        // use braces instead of parentheses because IDE
//        return point{e};
//    }

    void set_e (point& e);

//    point get_s () {
//        return point{s};
//    }

    void set_s (point& s); 

    float get_slope ();

    float* get_equation ();

    point operator[] (int i);

    line& operator= (const line& l);
};

class ray {
    line dir;
    // we add the speed to the dir
    point speed;
    bool has_hit = false;

public:
    // explicit in order to avoid weird conversions
    explicit ray (const point player_pos, const point dst);

    ray (ray& other);

    line get_dir();

    point get_speed();

    point notify_hit();

    bool check_if_has_hit();

    int* get_square_its_on();

    ray* operator+ (point p);

    ray& operator= (const ray& r);
};

int sgn (double n);

#endif //DOOMY_MATHY_H
