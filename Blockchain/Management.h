#include "Common.h"


class running_rule
{
public:
  running_rule(const block_time &t, const double &reward, const double &weight)
      : timeslot(t)
  {
    ;
  }
  void resouce_allocation_per_timeslot(const block_time &t,                 // timeslot
                                       const block_queue *queue,            // the address of the queue
                                       const double &weight,                // the weight of penalty
                                       const double &reward,                // the reward to easure each unit of dequeued data
                                       const double &consensus_difficulty); // consensus_difficulty
private:
  block_time timeslot;
  double weight;
};