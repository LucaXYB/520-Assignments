#include <math.h>
#include <float.h> /* defines DBL_EPSILON */
#include <assert.h>
#include "filter.h"
#include "integrator.h"
#include "random_process.h"
#include "stopwatch.h"
#include "gtest/gtest.h"
#include <map>
#include <string>
#include "elma/elma.h"

using namespace elma;

namespace
{
    TEST (TEST_STOPWATCH, TEST_1) {
        #define SLEEP std::this_thread::sleep_for(std::chrono::milliseconds(1500))
        Stopwatch w; // should set the stopwatch to 0 seconds
        w.start();
        SLEEP;
        w.stop();
        //std::cout << w.get_seconds() << "\n"; // about 1.5
        EXPECT_EQ(w.get_seconds(), 1.5);
        SLEEP;
        //std::cout << w.get_seconds() << "\n"; // still about 1.5
        EXPECT_EQ(w.get_seconds(), 1.5);
        w.start();
        SLEEP;
        w.stop();
        //std::cout << w.get_seconds() << "\n"; // about 3.0
        EXPECT_EQ(w.get_seconds(), 3.0);
        w.reset();
        //std::cout << w.get_seconds() << "\n"; // 0.0
        EXPECT_EQ(w.get_seconds(), 0.0);
    }

    TEST(TEST_RANDOMPROCESS, TEST_2){
        elma::Manager m;
        RandomProcess r("random numbers");
        Filter f("filter");
        elma::Channel link("link");

        m.schedule(r, 1_ms)
        .schedule(f, 1_ms)
        .add_channel(link)
        .init()
        .run(100_ms);
        //EXPECT_EQ(result, expected);
    }

    TEST(TEST_Process, TEST_3) {
        elma::Manager m;

        RandomProcess test("test process");
        Filter f("filter");
        elma::Channel link("link");

        m.schedule(test, 1_ms) // Use TestProcess instead of RandomProcess
        .schedule(f, 1_ms)
        .add_channel(link)
        .init()
        .run(100_ms); // Run for 100 steps

        // Check the running average
        assert(std::abs(f.value() - 0.5) < 0.01);
        //#std::cout << "Filter's running average after 100 steps: " << f.value() << std::endl;
    }
}