

#include <algorithm>
#include <fstream>
#include <iostream>
#include <map>
#include <set>
#include <string>
#include <vector>
// add or remove necessary headers as you please
#include "schedwork.h"

using namespace std;

// // a constant that can be used to indicate an INVALID
// // worker ID if that is useful to your implementation.
// // Feel free to not use or delete.
// static const Worker_T INVALID_ID = (unsigned int)-1;

bool schedule_helper(const AvailabilityMatrix& avail, const size_t dailyNeed,
                     const size_t maxShifts, DailySchedule& sched,
                     vector<size_t>& shifts_worked, size_t day, size_t worker) {
    if (day >= avail.size()) {
        // We've reached the end of the schedule successfully
        return true;
    }
    if (worker >= avail[0].size()) {
        // We've don't have enough workers we can schedule today, so we need to
        // backtrack. (We go immediately to the next day whenever we have enough
        // workers for the current day)
        return false;
    }
    if (avail[day][worker] && (shifts_worked[worker] < maxShifts)) {
        // try scheduling this worker for today
        sched[day].push_back(worker);
        shifts_worked[worker]++;
        bool found_schedule = false;
        if (sched[day].size() >= dailyNeed) {
            // We have all the workers we need today, so go to the next day
            found_schedule = schedule_helper(avail, dailyNeed, maxShifts, sched,
                                             shifts_worked, day + 1, 0);
        } else {
            found_schedule = schedule_helper(avail, dailyNeed, maxShifts, sched,
                                             shifts_worked, day, worker + 1);
        }
        if (found_schedule) {
            return true;
        }
        shifts_worked[worker]--;
        sched[day].pop_back();
    }
    // Try not scheduling this worker for today
    return schedule_helper(avail, dailyNeed, maxShifts, sched, shifts_worked,
                           day, worker + 1);
}

bool schedule(const AvailabilityMatrix& avail, const size_t dailyNeed,
              const size_t maxShifts, DailySchedule& sched) {
    if (avail.size() == 0U) {
        return false;
    }
    sched.clear();
    sched.resize(avail.size());
    std::vector<size_t> shifts_worked(avail[0].size());
    return schedule_helper(avail, dailyNeed, maxShifts, sched, shifts_worked, 0,
                           0);
}
