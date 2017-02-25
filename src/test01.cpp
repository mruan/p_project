#include "Agent.h"

#include <cstdlib>
#include <string>
#include <vector>
#include <list>

using namespace std;

typedef list<Agent*> AgentList;

int main()
{
  const int numAgents = 3;
  vector<Agent*> agents(numAgents);
  vector<AgentList> edges;

  srand(0);
  
  // The agents are stored in a vector
  
  // The graph (neighbors) is stored in a vector of list

  char id[32];
  double state=0;
  for(int i=0; i< numAgents; ++i)
    {
      sprintf(id, "agent_%d", i);
      agents[i] = new Agent(string(id));
      state = (rand() % 1000) / 1000.0;
      agents[i]->setState(state);
    }

  for(int i=0; i< numAgents; ++i)
    {
      edges[i].push_back(agents[(i+1)%numAgents]);
    }

  // Clean up allocated memory
  edges.clear();
  for(int i=0; i< numAgents; ++i)
    {
      delete agents[i];
    }
  agents.clear();
  return 0;
}
