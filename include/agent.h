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

  void setState(const double st){ state = st;}
  double getState() { return state;}
  /*
		
   */
  int communicate(std::list<Agent*>& peers);
	

  /*
    Update the internal states
  */
  int updateState();

  int logState();

 private:

  /*
		
   */
  int exchange(paillier_pubkey_t* pub,
	       paillier_ciphertext_t* msg_in,
	       paillier_ciphertext_t* msg_out);

  long ciphertext_to_long(paillier_ciphertext_t* c);

  long updateAlpha();

  std::string id;
  double state;
  long alpha;
  long long_state;
  long diff_state;

  FILE* logfile = NULL;

  paillier_pubkey_t* pubKey = NULL;
  paillier_prvkey_t* prvKey = NULL;
};

#endif
