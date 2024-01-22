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

    point (int x=0, int y=0) {
        this->x = x;
        this->y = y;
    }

    point (point const &other) {
        this->x = other.x;
        this->y = other.y;
    }

//    int get_x () {
//        return x;
//    }

    void set_x (int x) {
        this->x = x;
    }

//    int get_y () {
//        return y;
//    }

    void set_y (int y) {
        this->y = y;
    }

    double get_distance (const point& other) {
        return (sqrt(pow(x - other.x, 2) + pow(y - other.y, 2)));
    }

    int operator[] (int i) const {
        if (i%2 == 0) { return x; }
        return y;
    }
};


class line {
    // s for start, e for end
    point s,e;

public:

    // explicit to avoid weird conversions
    explicit line (const point& s={0,0}, const point& e={0,0}) {
        this->s = s;
        this->e = e;
    }

    line (line const &other) {
        point s_cpy, e_cpy;
        s_cpy = point (other.s);
        e_cpy = point (other.e);

        this->s = s_cpy;
        this->e = e_cpy;
    }

//    point get_e () {
//        // use braces instead of parentheses because IDE
//        return point{e};
//    }

    void set_e (point& e) {
        this->e = e;
    }

//    point get_s () {
//        return point{s};
//    }

    void set_s (point& s) {
        this->s = s;
    }

    float get_slope () {
        return ((float) s[1] - e[1])/((float) s[0] - e[0]);
    }

    float* get_equation () {
        float m=0, b=0;
        m = get_slope();
        // y = mx + b -> b = y-mx
        b = s[1] - m * s[0];

        float* ans = new float[2];
        ans[0] = m; ans[1] = b;
        return ans;
    }

    point operator[] (int i) {
        if (i%2 == 0) { return s; }
        return e;
    }
};

class ray {
    line dir;
    // we add the speed to the dir
    point speed;
    bool has_hit = false;

public:
    // explicit in order to avoid weird conversions
    explicit ray (const point& player_pos) {
        dir = line(player_pos);
        speed = point(RAY_X_SPEED, RAY_Y_SPEED);
    }

    ray (ray& other) {
        // use copy ctors
        dir = line (other.get_dir());
        speed = point (other.get_speed());
    }

    line get_dir() {
        // copy dir
        line dir_cpy = line(dir);
        return dir_cpy;
    }

    point get_speed() {
        // copy speed
        point speed_cpy = point(speed);
        return speed_cpy;
    }

    point notify_hit() {
        has_hit = true;
    }

    bool check_if_has_hit() {
        return has_hit;
    }

    int* get_square_its_on();

    ray operator+ (point p) {
        // copy ctor
        ray new_r = ray(*this);
        point new_e = {0,0};
        // set the tip via speed
        new_e.set_x (new_r.dir[1][0] + p[0]);
        (new_r.dir).set_e(new_e);

        return new_r;
    }
};

int sgn (double n) {
    if (n > 0) { return 1; }
    if (n < 0) { return -1; }
    return 0;
}

#endif //DOOMY_MATHY_H
