#include "maze.h"

using namespace std;
using nlohmann ::json;

int MAZE::random(int len)
{
    rng.seed(std::chrono::steady_clock::now().time_since_epoch().count());
    int low = 2 * width;
    int high = len - 2 * width - 1;
    return std::uniform_int_distribution<int>(low, high)(rng);
}

void MAZE::generate_random_maze()
{
    sub_maze(corners, true);
}

void MAZE::create_hole(vector<point> wall, bool orientation)
{
    int len = abs(orientation ? wall[2].y() - wall[0].y() : wall[1].x() - wall[0].x());
    if (len <= 6 * width)
    {
        return;
    }
    int hole_point = random(len);
    vector<point> new_wall1, new_wall2;
    if (orientation)
    {
        point temp_a(wall[1].x(), wall[1].y() + hole_point - 2 * width);
        point temp_b(wall[0].x(), wall[0].y() + hole_point - 2 * width);
        point temp_c(wall[0].x(), wall[0].y() + hole_point + 2 * width);
        point temp_d(wall[1].x(), wall[1].y() + hole_point + 2 * width);

        new_wall1 = {wall[0], wall[1], temp_a, temp_b};
        new_wall2 = {temp_c, temp_d, wall[3], wall[2]};
    }
    else
    {
        point temp_a(wall[0].x() + hole_point - 2 * width, wall[0].y());
        point temp_b(wall[0].x() + hole_point + 2 * width, wall[0].y());
        point temp_c(wall[0].x() + hole_point + 2 * width, wall[2].y());
        point temp_d(wall[0].x() + hole_point - 2 * width, wall[2].y());

        new_wall1 = {wall[0], temp_a, temp_d, wall[3]};
        new_wall2 = {temp_b, wall[1], wall[2], temp_c};
    }
    walls.push_back(new_wall1);
    walls.push_back(new_wall2);
}

// Divide the maze into several smaller parts
void MAZE::sub_maze(vector<point> corners, bool orientation)
{
    if (abs(corners[0].x() - corners[1].x()) <= 7 * width || abs(corners[0].y() - corners[3].y()) <= 7 * width)
    {
        return;
    }

    int len = abs(orientation ? corners[0].x() - corners[1].x() : corners[0].y() - corners[3].y());
    if (len <= 6 * width)
    {
        return;
    }

    int divide_point = random(len);
    vector<point> wall;

    if (orientation)
    {
        point temp_a(corners[0].x() + divide_point - width, corners[0].y());
        point temp_b(corners[0].x() + divide_point + width, corners[0].y());
        point temp_c(corners[0].x() + divide_point - width, corners[3].y());
        point temp_d(corners[0].x() + divide_point + width, corners[3].y());

        wall = {temp_a, temp_b, temp_c, temp_d};

        //! Recursively calling sub_maze for the smaller sub-spaces
        sub_maze({corners[0], temp_a, temp_d, corners[3]}, !orientation);
        sub_maze({temp_b, corners[1], corners[2], temp_c}, !orientation);
    }
    else
    {
        point temp_a(corners[0].x(), corners[0].y() + divide_point - width);
        point temp_b(corners[1].x(), corners[0].y() + divide_point - width);
        point temp_c(corners[1].x(), corners[0].y() + divide_point + width);
        point temp_d(corners[0].x(), corners[0].y() + divide_point + width);

        wall = {temp_a, temp_b, temp_c, temp_d};

        //! Recursively calling sub_maze for the smaller sub-spaces
        sub_maze({corners[0], corners[1], temp_b, temp_a}, !orientation);
        sub_maze({temp_d, temp_c, corners[2], corners[3]}, !orientation);
    }

    create_hole(wall, orientation);
}

void MAZE::update_enviro_config()
{
    std::ifstream inp("config.json");
    json maze;
    inp >> maze;

    auto wall_style = maze["statics"][0]["style"];
    auto border0 = maze["statics"][0];
    auto border1 = maze["statics"][1];
    auto border2 = maze["statics"][2];
    auto border3 = maze["statics"][3];

    maze["statics"].clear();

    maze["statics"].push_back(border0);
    maze["statics"].push_back(border1);
    maze["statics"].push_back(border2);
    maze["statics"].push_back(border3);

    for (auto wall : walls)
    {
        json wall_temp;
        for (point p : wall)
        {
            wall_temp["shape"].push_back(p.to_json());
        }

        wall_temp["style"] = wall_style;

        maze["statics"].push_back(wall_temp);
    }

    std::ofstream out("config.json");
    out << std::setw(4) << maze << std::endl;
}

int main()
{
    point c0(-340, -190), c1(340, -190), c2(340, 190), c3(-340, 190);

    MAZE RandomMaze(c0, c1, c2, c3, 11);

    RandomMaze.generate_random_maze();

    RandomMaze.update_enviro_config();

    return 0;
}