#ifndef __MAZE__H
#define __MAZE__H

#include <bits/stdc++.h>
#include <json/json.h>
using nlohmann::json;

class point
{
private:
    int pointX;
    int pointY;

public:
    point(int _x = 0, int _y = 0)
    {
        pointX = _x;
        pointY = _y;
    }
    int x() { return pointX; }
    int y() { return pointY; }

    void set(int _x, int _y)
    {
        pointX = _x;
        pointY = _y;
    }

    json to_json()
    {
        json p = {{"x", pointX}, {"y", pointY}};
        return p;
    }
};

class MAZE
{
private:
    std::vector<point> corners;
    std::vector<std::vector<point>> walls;
    int width;
    std::mt19937 rng;

public:
    MAZE(point a, point b, point c, point d, int _width)
    {
        corners.push_back(a);
        corners.push_back(b);
        corners.push_back(c);
        corners.push_back(d);
        width = _width;
        rng.seed(std::chrono::steady_clock::now().time_since_epoch().count());
    }

    void sub_maze(std::vector<point> corners, bool orientation);
    void create_hole(std::vector<point> wall, bool orientation);
    void generate_random_maze();
    void update_enviro_config();
    int random(int len);
};

#endif