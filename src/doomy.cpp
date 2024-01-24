
// all important code is in this .cpp file, recommended to check this one first.
// which contains all the logic, and only afterward go for the definitions.

#include "headers/doomy.h"

enum blocks {
    red, blue, green
};

// TODO: change this
SDL_Color colors[3] = {SDL_Color{255,0,0,255}, SDL_Color{0,255,0,255}, SDL_Color{0,0,255,255}};

int grid [XBLOCKS][YBLOCKS] = {
        {red,0,0,0,0,0,0,0,0,0},
        {red,0,0,0,0,0,0,0,0,0},
        {red,0,0,0,0,0,0,red,0,0},
        {red,0,0,0,0,0,0,0,0,0},
        {red,0,0,red,0,0,0,0,0,0},
        {red,0,0,red,0,0,0,0,0,0},
        {red,0,0,red,0,0,0,0,0,0},
        {red,0,0,red,0,0,0,0,0,0},
        {red,0,0,red,0,0,0,0,0,0},
        {red,red,red,red,red,red,red,0,0,0}
};

std::vector<ray> rays;

// some harmless definitions
point step (ray& r);
void draw_line_on_screen (SDL_Renderer*& renderer, SDL_Color c, ray& r);


// defined here as we need to know the screen, blocks info
// returns the square of the ray end
int* ray::get_square_its_on() {
    int* ans = new int[2]; ans[0] = 0; ans[1] = 0;
    point end = this->get_dir()[1];
    // works well width indexes, no need to -1
    // because we truncate decimals by using int
    ans[0] = end[0] / BLOCKWIDTH;
    ans[1] = end[1] / BLOCKHEIGHT;

    return ans;
}


void cast_rays (point& starting_pos) {
    int theta = FOVANGLE/2;
    // up is zero degrees and it goes counter clockwise
    // -tetha is supposed to work

    /// TODO: adjust angle with direction, player will always look up with this
    for (int i = -theta; i < theta; i++) {
        ray* r = new ray (starting_pos, (double)RAYDEFAULTLEN, (double)i);
        rays.push_back(*r);
    }
}

void step_and_draw_all (SDL_Renderer*& renderer) {

    for (ray& ray : rays) {

        // won't step if already hit
        point next = step(ray);
    
        std::cout << "priviet" << std::endl;

        // draw ray as red
        point s (ray.get_dir()[0]);
        SDL_SetRenderDrawColor(renderer, 255,0,0,255);
        SDL_RenderDrawLine(renderer, s[0], s[1], next[0], next[1]);
        // draw next as blue
        SDL_RenderDrawPoint(renderer, next[0], next[1]);
        SDL_RenderPresent(renderer);


        if (ray.check_if_has_hit()) {
            int* block = ray.get_square_its_on();
            int block_color = grid[block[0]][block[1]];
            draw_line_on_screen (renderer, colors[block_color], ray);
        } else {
            ray.get_dir().set_e(next);
        }
    }
}


// returns point for step
point step (ray& r) {
    // we suppose that the ray cannot start in a red block.
    // rather, may only be at its border
    int* square_index = r.get_square_its_on();

    // if is on red block
    if (grid[square_index[0]][square_index[1]] == red) {
        // TODO: if not on border go back
        // do not step
        r.notify_hit();
        return r.get_dir()[1];
    }

    // I was only able to override + with a ptr return.
    ray* curr_ray_with_step_ptr = r + r.get_speed();
    ray curr_ray_with_step = *curr_ray_with_step_ptr;

    int* next_square_index = curr_ray_with_step.get_square_its_on();

    /// you sense an evil pressure emmanating from this line...
    free(curr_ray_with_step_ptr);


    // if next step is in another block
    if ((square_index[0] != next_square_index[0]) && (square_index[1] != next_square_index[1])) {

        // check x and y separately, check for closest col

        // get ray line from dir;  y = mx + b
        // returns float [], of the type: {m, b}.
        float* eq = r.get_dir().get_equation();

        int next_block_y = next_square_index[1]*BLOCKHEIGHT;
        int next_block_x = next_square_index[0]*BLOCKWIDTH;

        // dir is a vertical line
        if (eq[0] == INFINITY) {

            // return point of curr x with block top
            point ans(r.get_dir()[1][0], next_block_y);
            return ans;
        }
        // dir is a horizontal line
        if (eq[0] == 0) {

            point ans(next_block_x, r.get_dir()[1][1]);
            return ans;
        }

        // inverse plot top side y;  x = (y-b)/m
        point inv_plot ((int)( ((float)next_block_y - eq[1])/eq[0]) , next_block_y);
        // plot block right side x;  y = mx + b
        point plot (next_block_x, (int)((float)eq[0] * next_block_x + eq[1]));

        point player_pos = r.get_dir()[0];
        double distance1 = player_pos.get_distance(inv_plot);
        double distance2 = player_pos.get_distance(plot);

        point dst = (distance1 <= distance2) ? inv_plot : plot;

        return dst;

    } else {
        return curr_ray_with_step.get_dir()[1];
    }
}

void draw_line_on_screen (SDL_Renderer*& renderer, SDL_Color c, ray& r){
    // check distance between dir line's inverse (the players camera) and dir
    float* eq = r.get_dir().get_equation();
    // extended equation of the type ax + by + c = 0 for dir
    float* x_eq = new float [3];
    // mx + (-y) + b = 0
    x_eq[0] = eq[0];
    x_eq[1] = -1;
    x_eq[2] = eq[1];

    point player_pos = r.get_dir()[0];
    // the plane that is perpendicular to movement plane (also a line)
    float* camera_plane_eq = new float [3];
    // (-1/m)x + (-y) + (y0 + x0/m) = 0
    camera_plane_eq[0] = -1/x_eq[0];
    camera_plane_eq[1] = x_eq[1];
    camera_plane_eq[2] = (player_pos[1] + player_pos[0]/x_eq[0]);

    // distance between camera_plane and wall hit (dir.e)
    point wall_hit = r.get_dir()[1];
    float numerator = (camera_plane_eq[0] * wall_hit[0] + camera_plane_eq[1] * wall_hit[1] + camera_plane_eq[2]);
    float denominator = sqrt(pow(camera_plane_eq[0], 2) + pow(camera_plane_eq[1], 2));

    float distance = numerator/denominator;

    // we also need to know the len of the square side trapped
    // between the dir plane and the intersection,
    // that gives where on the screen we should draw the column.

    // get intersection between dir and the square's side.
    // if the ray hit a vertical line of the block
    point a{0,0};
    if (wall_hit[0] % BLOCKWIDTH == 0) {

        // plot x to get y
        a = point ( wall_hit[0], x_eq[0] * wall_hit[0] + x_eq[2] );
    }
    // if the ray hit a horizontal line of the block
    else if (wall_hit[1] % BLOCKHEIGHT == 0)  {

        // plot y to get x
        a = point ( wall_hit[1], (wall_hit[1] - x_eq[2]) / x_eq[0] );
    }

    double h0 = player_pos.get_distance(a);
    double h1 = distance;
    double h2 = abs(h1-h0);
    double x0 = wall_hit[0] - player_pos[0];
    double l = sqrt( pow(x0, 2) + pow(h2, 2) );

    // sgn(x0) tells it to draw on the right side if wall_hit is bigger than player_pos
    // and on the left side if wall_hit is less than player_pos
    int line_height_on_screen = (int)((FOVRADIUS-l)/FOVRADIUS) * SCREENHEIGHT;

    point line_top (SCREENWIDTH/2 + sgn(x0) * l, (SCREENHEIGHT-line_height_on_screen)/2);
    // point line_bot (SCREENWIDTH/2 + sgn(x0) * l, (SCREENHEIGHT+line_height_on_screen)/2);
    // check: if wall_hit = a then h2=0 and x0=0 thus, l=0. Thus, we draw in the middle of the screen. :)
    SDL_SetRenderDrawColor(renderer, c.r, c.g, c.b, c.a);
    // we need to draw a rectangle of width SCREENWIDTH/FOVRADIUS
    // the curly braces are for denoting that it is a struct (aggregate init)
    int rect_width = SCREENWIDTH/FOVRADIUS;
    // rect {x, y, w, h}
    SDL_Rect* rect = new SDL_Rect{line_top[0]-(rect_width/2), line_top[1], rect_width, line_height_on_screen};
    SDL_RenderDrawRect(renderer, rect);
}