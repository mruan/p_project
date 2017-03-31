/*
	Agent class
*/

#ifndef AGENT_H
#define AGENT_H

#include <cstdio>
#include <cstdlib>
#include <string>
#include <list>

#include <gmp.h>

extern "C" 
{
  #include <paillier.h>
}

typedef unsigned long ulong;

class Agent
{
 public:
  Agent(std::string id);
  ~Agent();

  double setState(const double st);
  double getState() { return state;}

  /*
    Send inquiries to all neighbors and do computation 
    without updating its states
   */
  int communicate(std::list<Agent*>& peers);
	
  /*
    Update the internal states
  */
  int updateState();

  int logState();

 private:
  /*
    Process another agent's inquiry
   */
  int exchange(paillier_pubkey_t* pub,
	       paillier_ciphertext_t* msg_in,
	       paillier_ciphertext_t* msg_out);

  long ciphertext_to_long(paillier_ciphertext_t* c);

  // Generate a new random weight alpha
  long updateAlpha();

  std::string id;
  // For illustrative purpose, state is a scalar
  double state;
  long alpha;
  long long_state;
  long mdif_state;

  FILE* logfile = NULL;

  paillier_pubkey_t* pubKey = NULL;
  paillier_prvkey_t* prvKey = NULL;
};

#endif
