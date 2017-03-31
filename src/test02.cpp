/*
  Weighted Average consensus
 */

#include "agent.h"

#include <cstdlib>
#include <string>
#include <vector>
#include <list>
#include <ctime>

using namespace std;

typedef list<Agent*> AgentList;

int main()
{
  const int numAgents = 4;
  const int maxSteps = 25;

  // The agents are stored in a vector
  // The graph (neighbors) is stored in a vector of list
  vector<Agent*> nodes(numAgents);
  vector<AgentList> edges(numAgents);
  double st[4] = {1.0, 4.0, 2.0, 8.0};
  double wt[4] = {0.1, 0.3, 0.2, 0.4};
  srand(0);

  printf("Initialize nodes long=%lu\n", sizeof(long));
  
  char id[32];
  double state;
  double avg = 0.0;
  for(int i=0; i< numAgents; ++i)
    {
      sprintf(id, "agent_%d", i);
      nodes[i] = new Agent(string(id), wt[i]);
      state = st[i];//(rand() % 1000);
      nodes[i]->setState(state);
      // accumulate initial state
      avg += wt[i]*nodes[i]->getState();
    }
  printf("Initial avg= %lf\n", avg);
  
  printf("Initialize edges\n");
  
  for(int i=0; i< numAgents; ++i)
    {
      edges[i].push_back(nodes[(i+1)%numAgents]);
      edges[i].push_back(nodes[(i+numAgents-1)%numAgents]);
    }

  printf("Main loop\n");
  
  double total_time = 0.0;
  for(int i=0; i< maxSteps; ++i)
    {
      printf("Step %2d: ", i);

      clock_t begin = clock();

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
      clock_t end = clock();
      double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
      printf("\tTime elapsed: %lf\t", elapsed_secs);
      total_time += elapsed_secs;
      
      avg = 0.0;
      for(int j=0; j< numAgents; ++j)
	{
	  avg += wt[j]*nodes[j]->getState();
	}
      printf(" avg= %lf\n", avg);
    }

  printf("Avg_time = %lf ms\n", total_time/maxSteps*1000);
  
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
