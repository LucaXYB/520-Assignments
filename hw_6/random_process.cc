#include "random_process.h"

void RandomProcess::update() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(0, 1);
    double value = dis(gen);
    channel("link").send(value);
}