#include "agent.h"

#include <cstdlib>
#include <string>
#include <vector>
#include <list>

using namespace std;

typedef list<Agent*> AgentList;

int main()
{
  const int numAgents = 5;
  const int maxSteps = 40;

  // The agents are stored in a vector
  // The graph (neighbors) is stored in a vector of list
  vector<Agent*> nodes(numAgents);
  vector<AgentList> edges(numAgents);

  srand(0);

  printf("Initialize nodes\n");
  
  char id[32];
  double state;
  double avg = 0.0;
  for(int i=0; i< numAgents; ++i)
    {
      sprintf(id, "agent_%d", i);
      nodes[i] = new Agent(string(id));
      state = (rand() % 1000);
      nodes[i]->setState(state);
      // accumulate initial state
      avg += nodes[i]->getState();
    }
  printf("Initial avg= %lf\n", avg/numAgents);
  
  printf("Initialize edges\n");
  
  for(int i=0; i< numAgents; ++i)
    {
      edges[i].push_back(nodes[(i+1)%numAgents]);
      //      edges[i].push_back(nodes[(i+2)%numAgents]);
    }

  printf("Main loop\n");
  for(int i=0; i< maxSteps; ++i)
    {
      printf("Step %2d: ", i);
      // NOTE: The following steps must be done in seperate steps
      // TODO: consider pair-wise update
      // First everyone collect info from neighbors
      for(int j=0; j< numAgents; ++j)
	{
	  nodes[j]->communicate(edges[j]);
	}
      // Then do update
      for(int j=0; j< numAgents; ++j)
	{
	  nodes[j]->updateState();
	}
      avg = 0.0;
      for(int j=0; j< numAgents; ++j)
	{
	  avg += nodes[j]->getState();
	}
      printf(" avg= %lf\n", avg/numAgents);
    }

  printf("Clean up\n");
  // Clean up allocated memory
  edges.clear();
  for(int i=0; i< numAgents; ++i)
    {
      delete nodes[i];
    }
  nodes.clear();
  return 0;
}
