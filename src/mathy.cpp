//
// Created by Manuel Suarez on 22/01/2024.
//

#include "headers/mathy.h"
#include <stdlib.h>

point::point (int x=0, int y=0) {
    this->x = x;
    this->y = y;
}

point::point (point const &other) {
    this->x = other.x;
    this->y = other.y;
}

//    int get_x () {
//        return x;
//    }

void point::set_x (int x) {
    this->x = x;
}

//    int get_y () {
//        return y;
//    }

void point::set_y (int y) {
    this->y = y;
}

double point::get_distance (const point& other) {
    return (sqrt(pow(x - other.x, 2) + pow(y - other.y, 2)));
}

int point::operator[] (int i) const {
    if (i%2 == 0) { return x; }
    return y;
}

point& point::operator= (const point& p) {
    if (this == &p) {
        return *this;
    }
    // these are not overloaded
    this->x = p.x;
    this->y = p.y;
}


line::line (const point& s={0,0}, const point& e={0,0}) {
    this->s = s;
    this->e = e;
}

line::line (line const &other) {
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

void line::set_e (point& e) {
    this->e = e;
}

//    point get_s () {
//        return point{s};
//    }

void line::set_s (point& s) {
    this->s = s;
}

float line::get_slope () {
    return ((float) s[1] - e[1])/((float) s[0] - e[0]);
}

float* line::get_equation () {
    float m=0, b=0;
    m = get_slope();
    // y = mx + b -> b = y-mx
    b = s[1] - m * s[0];

    float* ans = new float[2];
    ans[0] = m; ans[1] = b;
    return ans;
}

point line::operator[] (int i) {
    if (i%2 == 0) { return s; }
    return e;
}

line& line::operator= (const line& l) {
    // self-assignment
    if (this == &l) {
        return *this;
    }

    this->s = l.s;
    this->e = l.e;
}


ray::ray (const point player_pos, const point dst) {
    dir = line(player_pos, dst);
    speed = point(RAY_X_SPEED, RAY_Y_SPEED);
}

ray::ray (ray& other) {
    // use copy ctors
    dir = line (other.get_dir());
    speed = point (other.get_speed());
}

line ray::get_dir() {
    // copy dir
    line dir_cpy = line(dir);
    return dir_cpy;
}

point ray::get_speed() {
    // copy speed
    point speed_cpy = point(speed);
    return speed_cpy;
}

point ray::notify_hit() {
    has_hit = true;
}

bool ray::check_if_has_hit() {
    return has_hit;
}

ray* ray::operator+ (point p) {
    // copy ctor
    point new_e = {0,0};
    // set the tip via speed
    new_e.set_x (dir[1][0] + p[0]);
    new_e.set_y (dir[1][1] + p[1]);

    // from dir-start to new_e
    ray* new_ray = (ray*) malloc (sizeof(ray));
    *new_ray = ray {this->dir[0], new_e};

    return new_ray;
}

// need this to copy assignment, for changes not to dance around
ray& ray::operator= (const ray& r) {
    // self-assignment check
    if (this == &r) {
        return *this;
    }

    // these are also overloaded
    dir = r.dir;
    speed = r.speed;
    return *this;
}


int sgn (double n) {
    if (n > 0) { return 1; }
    if (n < 0) { return -1; }
    return 0;
}