#include "agent.h"

#include <cstdlib>
#include <string>
#include <vector>
#include <list>

using namespace std;

typedef list<Agent*> AgentList;

int main()
{
  const int numAgents = 2;
  const int maxSteps = 100;
  vector<Agent*> nodes(numAgents);
  vector<AgentList> edges(numAgents);

  srand(0);
  
  // The agents are stored in a vector
  
  // The graph (neighbors) is stored in a vector of list

  printf("Initialize nodes\n");
  
  char id[32];
  double state=0;
  for(int i=0; i< numAgents; ++i)
    {
      sprintf(id, "agent_%d", i);
      nodes[i] = new Agent(string(id));
      state = (rand() % 1000) / 1000.0;
      nodes[i]->setState(state);
      //start logging:
      nodes[i]->logState();
    }

  printf("Initialize edges\n");
  
  for(int i=0; i< numAgents; ++i)
    {
      edges[i].push_back(nodes[(i+1)%numAgents]);
      //      edges[i].push_back(nodes[(i+2)%numAgents]);
    }

  printf("Main loop\n");
  for(int i=0; i< maxSteps; ++i)
    {
      printf("Step %2d\n", i);
      for(int j=0; j< numAgents; ++j)
	{
	  nodes[j]->communicate(edges[j]);
	  nodes[j]->updateState();
	}
    }

  printf("3\n");
  // Clean up allocated memory
  edges.clear();

  printf("4\n");
  for(int i=0; i< numAgents; ++i)
    {
      delete nodes[i];
    }
  printf("5\n");
  nodes.clear();
  return 0;
}
