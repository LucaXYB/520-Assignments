#include <iostream>
#include "my_robot.h"

using namespace enviro;

// Initiate the Robot's position by clicking within the Maze
void MyRobotController::init()
{
    // Watch for the screen click to get the robot's start position
    // Event: the starting position's coordinate
    watch("screen_click", [this](Event &e)
          {
        if (!this->m_bPosInit)
        {
            this->m_visited.clear();
            this->m_recStack = std::stack<std::pair<int, int>>();
            this->m_recStack.push(std::make_pair(e.value()["x"], e.value()["y"]));
        }
        e.stop_propagation();
        this->m_bPosInit = true; });
}

void MyRobotController::start() {}

void MyRobotController::update()
{
    if (!this->m_bPosInit)
    {
        return;
    }
    if (this->m_recStack.empty())
    {
        return;
    }
    auto node = this->m_recStack.top();
    this->m_recStack.pop();

    // Move the robot to the node position
    teleport(node.first, node.second, 0.0);

    if (this->m_visited[node] == true)
    {
        return;
    }

    // check if the robot is out of the maze
    if (x() <= -350 || x() >= 350 || y() <= -200 || y() >= 200)
    {
        return;
    }

    node = std::make_pair((int)x(), (int)y());

    this->m_visited[node] = true;

    // dfs: 4 directional beighboring cells
    for (int i = 0; i < 4; ++i)
    {
        auto d = "RULD"[i];
        auto next = get_next_pos(node, d);
        if (this->m_visited[next])
        {
            continue;
        }
        // detect static agents through using multiple sensors
        if (std::min(sensor_value(2 * i), sensor_value(2 * i + 1)) <= 4 + this->m_iStep)
        {
            continue;
        }

        m_recStack.push(node);
        m_recStack.push(next);
    }
}
void MyRobotController::stop() {}

std::pair<int, int> MyRobotController::get_next_pos(std::pair<int, int> cur_pos, char dir)
{
    Direction d(dir, this->m_iStep);
    int new_x = cur_pos.first + d.x();
    int new_y = cur_pos.second + d.y();
    return std::make_pair(new_x, new_y);
}