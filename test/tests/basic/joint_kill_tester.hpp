#ifndef JOINT_KILL_BASIC_TESTER_HPP
#define JOINT_KILL_BASIC_TESTER_HPP

#include "lizard/lizard.hpp"
#include "inc/joint.hpp"

namespace test {

class joint_kill_basic_tester : public lizard_base_tester {
public:
    void run() {
        // create a joint
        joint_kill j;
        // test defaults
        IS_ZERO(j.size());
        // the # of branches that joint will have
        const size_t branch_count = 10;
        // bound streets as branch to the joint
        FOR(i,0,branch_count,++) {
            j.add_branch()
                (street_ptr(new street(10, "S-"+std::to_string(i))), HEAD);
            // make sure this is it
            IS_ZERO(j[i]->size());
            SHOULD_BE(j[i]->capacity(), 10);
            SHOULD_BE(j[i]->name(), "S-"+std::to_string(i));
            // initially every street will have a car
            car_ptr c(new car("CS-"+std::to_string(i)));
            // it goes to HEAD
            c->direction(HEAD);
            // with 10m/s max speed
            c->max_speed(10 + rand() % 5);
            // the car starts from the tail of street
            j[i]->bound_car(c, TAIL);
            // adjust the street's traffic weight randomly!
            j[i]->traffic_weight(rand() % 3 + 1);
        }
        // make sure we have all of our branches as desired
        SHOULD_BE(j.size(), branch_count);
        // validate every street has only 1 car goes to its HEAD
        FOR(i,0,j.size(),++) { SHOULD_BE(j[i]->size(HEAD), 1); SHOULD_BE(j[i]->size(), 1); }
        // make streets flow!!
        size_t car_count = 0;
        size_t flowless_count = 0;
        bool head_flow, tail_flow;
        while(flowless_count < j.size()) {
            flowless_count = 0;
            FOR(i,0,j.size(),++) {
                j[i]->flow(1, &head_flow, &tail_flow);
                if(!(head_flow || tail_flow)) flowless_count++;
                else flowless_count = 0;
            }
        }
        // all street should remain in flowless mode at the end
        SHOULD_BE(flowless_count, j.size());
        // count the totall cars that are created
        FOR(i,0,j.size(),++) {
            car_count += j[i]->size();
            // since all streets are joined by their HEAD
            //  and all cars were directed to the HEAD
            //  they will all go to the TAIL of other streets and
            //  remain hold!
            // hence the HEADs# will always be zero
            IS_ZERO(j[i]->size(HEAD));
            // (*) none of cars can go/trun around to their original street at dispatch point
            FOR(line,0,CONST_STREET_LINES_NO,++) {
                // cars should vanish do to kill joint defined property
                IS_ZERO(j[i]->operator ()(TAIL,line).size());
            }
        }
        // all cars should vanish by reaching to the kill joint
        IS_ZERO(car_count);
        // test dispatching events to branches
        FOR(i,0,j.size(),++) { IS_FALSE(j[i]->event_has_defined(street::AFTER_EXIT)); IS_FALSE(j[i]->event_has_defined(street::ON_TRAFFIC_HOLD)); }
        j.dispatch_event(street::AFTER_EXIT, [](vector<const void*>) { });
        FOR(i,0,j.size(),++) { IS_TRUE(j[i]->event_has_defined(street::AFTER_EXIT)); IS_FALSE(j[i]->event_has_defined(street::ON_TRAFFIC_HOLD)); }
        // validate the inherit of joint instance
        IS_BASE_OF(base_event, decltype(j));
    }
};

}

#endif

