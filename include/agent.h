/*
	Agent class
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <gmp.h>
#include <paillier.h>

typedef unsigned long ulong;

Class Agent
{
public:
	Agent();
	~Agent();

	/*
		
	*/
	int communicate(List<Agent*>& peers);
	

	/*
		Update the internal states
	*/
	int update_state();

private:

	/*
		
	*/
	int exchange(const paillier_pubkey_t* pub,
				 const paillier_ciphertext_t* msg_in,
				 paillier_ciphertext_t* msg_out);

	string id;
	double state;

	long int_state;
	long alpha;
	long diff_state;

	FILE* logfile;

  	paillier_pubkey_t* pubKey;
  	paillier_prvkey_t* prvKey;
};