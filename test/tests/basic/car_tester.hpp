#ifndef CAR_BASIC_TESTER_HPP
#define CAR_BASIC_TESTER_HPP

#include "lizard/lizard.hpp"
#include "inc/car.hpp"

namespace test {

class car_basic_tester : public lizard_base_tester {
public:
    void run() {
        car c("CAR-ID");
        SHOULD_BE(c.line(), -1);
        SHOULD_BE(c.position(), -1);
        SHOULD_BE(c.max_speed(), 0);
        IS_ZERO(c.getTour().size());
        SHOULD_BE(c.direction(), NILL);
        SHOULD_BE(c.getID(), "CAR-ID");
        NOT_ZERO(c.to_string().length());
        SHOULD_BE(c.getLong(), CONST_AVG_CAR_LONG);
        FOR(i,0,2,++) {
            c.add2Tour(std::to_string(char(int('A')+i)));
            SHOULD_BE(c.getTour().size(), (size_t)i+1);
            IS_TRUE(c.getTour().back().length() > 1);
        }
        c.line(10);
        c.position(100);
        c.max_speed(1000);
        SHOULD_BE(c.line(), 10);
        SHOULD_BE(c.position(), 100);
        SHOULD_BE(c.max_speed(), 1000);
        car c1 = c;
        SHOULD_BE(c.line(), 10);
        SHOULD_BE(c.position(), 100);
        SHOULD_BE(c.max_speed(), 1000);
        SHOULD_BE(c.getID(), "CAR-ID");
        SHOULD_BE(c.getTour().size(), 2);
    }
};

}

#endif

