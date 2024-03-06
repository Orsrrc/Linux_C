#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <stdexcept>
#include "hash.h"
#include "Block.h"

///////////////////////define the data struct/////////////////////////////////////////////////////////////////////

//
// the struct of block node
//

//
// the struct of queues
//
struct block_queue
{

};

//
// the struct of block resouce
//
struct block_resouce
{
};

//
// the struct of timeslots
//
struct block_time
{
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/////////////////////// symbols and Notations ////////////////////////////////////////////////////////////////////

void init_queue();                                                        // initliation queue
void inject_actual_queues_set();                                          // inject the vector of actual queues
void inject_virtual_queues_set();                                         // inject the vector of virtual queues
void get_resource_allocated(const block_time &t, const Block &ID);        // the IDth vector of resouces allocated for shard at t
void get_resource_allocated(const block_time &t, const block_resouce &k); // the kth resouce allocated to shard
void get_budget(const block_resouce &k);                                  // the budget of the kth resouce
void get_queue_length(const block_time &t, const block_queue &i);         // the queue length of shard
void get_arrival_transaction(const block_time &t, const block_queue &i);  // the arrival transactions of queue
void get_dequeued_transaction(const block_time &t, const block_queue &i); // the dequeued transaction of queue
void set_reward();                                                        // the reward to easure each unit of dequeued data
void set_penalty_weight(const std::string &id, const double &weight);     // set the weight of penalty 0 -> perfer queue stability  >0 consider queue stability and resource consume
void set_consensus_difficulty();                                          // set the parameter reverse to the consensus difficulty
void Lyapunov();                                                          // the Lyapunov function of Q(t)
void lyapunov_drift();                                                    // the Lyapunov drift
void get_increment(const block_resouce &k, const block_time &t);          // the increment arrived in virtual queue k at timeslot t
void concatenated_actual_and_virtual();                                   // the concatenated vector

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// void print_hex(const char *label, const uint8_t *v, size_t len);

std::string getMerkleRoot(const std::vector<std::string> &merkle);

std::pair<std::string, std::string> findHash(int index, std::string prevHash, std::vector<std::string> &merkle);
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
extern std::vector<block_queue> queues_set;         // the set of queues
extern std::vector<block_queue> actual_queues_set;  // vector of actual queues
extern std::vector<block_queue> virtual_queues_set; // vector of virtual queues
extern std::vector<block_time> timeslots_set;       // the set of all timeslots
extern std::vector<block_resouce> resouce_set;      // the # of all types of resouces
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



// int addBlock(int index, string prevHash, vector<string> &merkle, vector<unique_ptr<Block> > &blockchain)
//{
//     string header = to_string(index) + prevHash + getMerkleRoot(merkle);
//     auto pair = findHash(header);

//     blockchain.push_back(std::make_unique<Block>(index,prevHash,pair.first,pair.second,merkle));
//     return 1;
// }