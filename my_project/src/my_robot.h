#ifndef __MY_ROBOT_AGENT__H
#define __MY_ROBOT_AGENT__H

#include "enviro.h"
#include <bits/stdc++.h>

using namespace enviro;

struct Direction
{
    Direction(char dir, int step)
    {
        if (dir == 'R')
        {
            dx = step;
            dy = 0;
        }
        else if (dir == 'L')
        {
            dx = -step;
            dy = 0;
        }
        else if (dir == 'D')
        {
            dx = 0;
            dy = step;
        }
        else if (dir == 'U')
        {
            dx = 0;
            dy = -step;
        }
        else
        {
            throw std::invalid_argument("Invalid Direction");
        }
    }
    int x() { return dx; }
    int y() { return dy; }

private:
    int dx;
    int dy;
};

// Controlling the robot's movement
// Algorithm: DFS + Backtracking
class MyRobotController : public Process, public AgentInterface
{
private:
    int m_iStep;
    bool m_bPosInit;
    // Store the visited cell
    std::map<std::pair<int, int>, bool> m_visited;
    // Store the order in which the positions were accessed along the DFS
    std::stack<std::pair<int, int>> m_recStack;

public:
    MyRobotController() : Process(), AgentInterface()
    {
        m_bPosInit = false;
        m_iStep = 4;
    }

    void init();
    void start();
    void update();
    void stop();
    std::pair<int, int> get_next_pos(std::pair<int, int> cur_pos, char dir);
};

class MyRobot : public Agent
{
public:
    MyRobot(json spec, World &world) : Agent(spec, world)
    {
        add_process(c);
    }

private:
    MyRobotController c;
};

DECLARE_INTERFACE(MyRobot)

#endif