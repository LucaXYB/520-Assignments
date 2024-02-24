#include "filter.h"
#include<numeric>

void Filter::update() {
    if (channel("link").nonempty()) {
        double value = channel("link").latest();
        _lastValues.push_back(value);
        if (_lastValues.size() > 10) {
            _lastValues.pop_front();
        }

        _average = std::accumulate(_lastValues.begin(), _lastValues.end(), 0);
    }
}

double Filter::value() const {
    return _average;
}