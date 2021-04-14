#pragma once

#include "vec2.h"

namespace rawaccel {
    using milliseconds = double;

    inline constexpr int POLL_RATE_MIN = 125;
    inline constexpr int POLL_RATE_MAX = 8000;

    inline constexpr milliseconds DEFAULT_TIME_MIN = 1000.0 / POLL_RATE_MAX / 2;
    inline constexpr milliseconds DEFAULT_TIME_MAX = 1000.0 / POLL_RATE_MIN * 2;

    inline constexpr milliseconds WRITE_DELAY = 1000;

    inline constexpr size_t MAX_DEV_ID_LEN = 200;

    inline constexpr size_t SPACED_LUT_CAPACITY = 1025;
    inline constexpr size_t ARB_LUT_CAPACITY = SPACED_LUT_CAPACITY / 4;

    inline constexpr double MAX_NORM = 16;
    inline constexpr double PI = 3.14159265358979323846;

    enum class accel_mode {
        classic,
        jump,
        natural,
        motivity,
        power,
        arb_lookup,
        noaccel
    };

    enum class spaced_lut_mode {
        off,
        binlog,
        linear
    };

    struct spaced_lut_args {
        spaced_lut_mode mode = spaced_lut_mode::off;
        bool transfer = true;
        unsigned char partitions = 2;
        short num_elements = 8;
        double start = 0;
        double stop = 8;
    };

    struct table_args {
        bool velocity = true;
        int length = 0;
        vec2<float> data[ARB_LUT_CAPACITY] = {};
    };

    struct accel_args {
        accel_mode mode = accel_mode::noaccel;
        bool legacy = false;

        double offset = 0;
        double cap = 1.5;
        double accel_classic = 0.005;
        double decay_rate = 0.1;
        double growth_rate = 1;
        double motivity = 1.5;
        double power = 2;
        double scale = 1;
        double weight = 1;
        double exponent = 0.05;
        double limit = 1.5;
        double midpoint = 5;
        double smooth = 0.5;

        spaced_lut_args spaced_args;
        table_args arb_args;
    };

    struct domain_args {
        vec2d domain_weights = { 1, 1 };
        double lp_norm = 2;
    };

    struct settings {
        double degrees_rotation = 0;
        double degrees_snap = 0;
        bool combine_mags = true;
        double dpi = 1000;
        double speed_min = 0;
        double speed_max = 0;

        vec2<accel_args> argsv;
        vec2d sens = { 1, 1 };
        vec2d dir_multipliers = { 1, 1 };
        domain_args dom_args = {};
        vec2d range_weights = { 1, 1 };

        milliseconds time_min = DEFAULT_TIME_MIN;
        milliseconds time_max = DEFAULT_TIME_MAX;

        bool ignore = false;
        wchar_t device_id[MAX_DEV_ID_LEN] = {};
    };

    template <typename AccelFunc>
    inline double apply_weighted(AccelFunc&& f, double x, double w)
    {
        return 1 + (f(x) - 1) * w;
    }

}
