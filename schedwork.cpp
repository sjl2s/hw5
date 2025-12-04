#ifndef RECCHECK
#include <set>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
// add or remove necessary headers as you please

#endif

#include "schedwork.h"

using namespace std;

// a constant that can be used to indicate an INVALID 
// worker ID if that is useful to your implementation.
// Feel free to not use or delete.
static const Worker_T INVALID_ID = (unsigned int)-1;


// Add prototypes for any helper functions here
bool scheduleHelper( const AvailabilityMatrix& avail, const size_t dailyNeed, const size_t maxShifts,
    DailySchedule& sched, vector<int>& shifts, int day,int col);

// Add your implementation of schedule() and other helper functions here

bool schedule(
    const AvailabilityMatrix& avail,
    const size_t dailyNeed,
    const size_t maxShifts,
    DailySchedule& sched
)
{
    if(avail.size() == 0){
        return false;
    }
    sched.clear();
    // Add your code below
    
    vector<Worker_T> tempRow(dailyNeed, INVALID_ID);
    for (size_t i = 0; i < avail.size(); i++) {
        sched.push_back(tempRow);
    }

    vector<int> shifts(avail[0].size(), 0);
    return scheduleHelper(avail, dailyNeed, maxShifts, sched, shifts, 0, 0);
}

bool scheduleHelper(const AvailabilityMatrix& avail,const size_t dailyNeed, const size_t maxShifts, 
    DailySchedule& sched, vector<int>& shifts, int day, int col){
    if (day == (int)avail.size()){
        return true;
    }

    if (col == (int)dailyNeed) {
        return scheduleHelper(avail, dailyNeed, maxShifts, sched, shifts, day + 1, 0);
    }

    int worker = 0;
    if (col > 0) {
        worker = sched[day][col - 1] + 1;
    }

    for(int i = worker; i < (int)avail[0].size(); i++){
        if (avail[day][i] && shifts[i] < (int)maxShifts) {
            sched[day][col] = i;
            shifts[i]++;

            if (scheduleHelper(avail, dailyNeed, maxShifts, sched, shifts, day, col + 1)) {
                return true;
            }

            shifts[i]--;
            sched[day][col] = INVALID_ID;
        }
    }
    return false;
}