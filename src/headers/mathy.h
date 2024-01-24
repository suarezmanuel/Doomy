//
// Created by Manuel Suarez on 22/01/2024.
//

#ifndef MATHY_H
#define MATHY_H

#define M_PI   3.14159265358979323846
#define EPSILON 1.e-10
#define RAY_X_SPEED 1
#define RAY_Y_SPEED 1

// using from here sqrt and pow, and abs
#include <cmath>
#include <SDL2/SDL.h>

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

    void draw (SDL_Renderer*& renderer, SDL_Color c);
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

    // point& intersection (const line& other);

    void draw (SDL_Renderer*& renderer, SDL_Color c);
};

class ray {
    
    line dir;
    // we add the speed to the dir
    point speed;
    bool has_hit = false;

public:
    // explicit in order to avoid weird conversions
    explicit ray (const point player_pos, const point dst);

    // create ray dir via length and angle, speed is pre-set
    // angle 0 is right (we are in radians, imagine unit-circle)
    ray (const point player_pos, const double len, const double angle);
    
    // ray (ray& other);

    line get_dir();

    point get_speed();

    point notify_hit();

    bool check_if_has_hit();

    int* get_square_its_on();

    ray* operator+ (point p);

    ray& operator= (const ray& r);

    // void draw (SDL_Renderer*& renderer, SDL_Color c);
};

double help (double n);

double to_radians (double degrees);

double to_degrees (double radians);

int sgn (double n);

void test ();

#endif //MATHY_H
