#pragma once

#include <string>
#include <vector>



class myQueues
{
public:
  myQueues(const std::string &id)
      : queues_id(id)
  {
    ;
  }

private:
  std::string queues_id;
};