//
// Created by Manuel Suarez on 22/01/2024.
//

#include "headers/mathy.h"
#include <stdlib.h>
#include <iostream>

point::point (int x=0, int y=0) {
    this->x = x;
    this->y = y;
}

point::point (point const &other) {
    this->x = other.x;
    this->y = other.y;
}

void point::set_x (int x) {
    this->x = x;
}

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

void point::draw (SDL_Renderer*& renderer, SDL_Color c) {
    SDL_SetRenderDrawColor(renderer, c.r, c.g, c.b, c.a);
    SDL_RenderDrawPoint(renderer, x, y);
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

// point& line::intersection (const line& other) {
//     return;
// }

void line::draw (SDL_Renderer*& renderer, SDL_Color c) {

}

ray::ray (const point player_pos, const point dst) {
    dir = line(player_pos, dst);
    speed = point(RAY_X_SPEED, RAY_Y_SPEED);
}

ray::ray (const point player_pos, const double len, const double angle) {
    // help ensures that approximation to 0, 1, -1 are ints and not fp
    // by changing cos and sin, we added 90 degrees to our triangle such that
    // up is zero degrees and it goes counter clockwise
    int x = help(cos(to_radians(angle))) * len;
    int y = help(sin(to_radians(angle))) * len;
    
    point dst {player_pos[0] + x, player_pos[1] + y};
    dir = line (player_pos, dst);
    speed = point(RAY_X_SPEED, RAY_Y_SPEED);
}

// ray::ray (ray& other) {
//     // use copy ctors
//     dir = line (other.get_dir());
//     speed = point (other.get_speed());
// }

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

// help ensures that approximation to 0, 1, -1 are ints and not fp
double help (double n) {
    if (n > 0 && n < EPSILON) {
        return 0;
    }
    if (n > 1 - EPSILON && n < 1) {
        return 1;
    }

    if (n > -1 + EPSILON && n < -1) {
        return -1;
    }
    return n;
}

double to_radians (double degrees) {
    return (degrees * M_PI) / 180;
}

double to_degrees (double radians) {
    return (radians * 180) / M_PI; 
}

int sgn (double n) {
    if (n > 0) { return 1; }
    if (n < 0) { return -1; }
    return 0;
}

void test () {
    // this works good :)
    // std::cout << help(sin(to_radians(0))) << std::endl;
    // std::cout << help(sin(to_radians(90))) << std::endl;
    // std::cout << help(sin(to_radians(180))) << std::endl;
    // std::cout << help(sin(to_radians(270))) << std::endl;
    

    // this works good :>
     // imagine unit-circle, sin and cos
    // ray test1 {{250, 250}, 1, 0}; // expected {251, 250}
    // ray test2 {{250, 250}, 1, 90}; // expected {250, 251}
    // ray test3 {{250, 250}, 1, 180}; // expected {249, 250}
    // ray test4 {{250, 250}, 1, 270}; // expected {250, 249}
    
    // std::cout << "test1 dir end: " << test1.get_dir()[1][0] << " " <<  test1.get_dir()[1][1] << std::endl;
    // std::cout << "test2 dir end: " << test2.get_dir()[1][0] << " " <<  test2.get_dir()[1][1] << std::endl;
    // std::cout << "test3 dir end: " << test3.get_dir()[1][0] << " " <<  test3.get_dir()[1][1] << std::endl;
    // std::cout << "test4 dir end: " << test4.get_dir()[1][0] << " " <<  test4.get_dir()[1][1] << std::endl;

    // this works :}
    // ray test1 {{250, 250}, 1, 270};
    // ray test2 {{250, 250}, 1, -90}; // expected same value
    // std::cout << "test1 dir end: " << test1.get_dir()[1][0] << " " <<  test1.get_dir()[1][1] << std::endl;
    // std::cout << "test2 dir end: " << test1.get_dir()[1][0] << " " <<  test1.get_dir()[1][1] << std::endl;
}