/*
	Agent.cpp
*/
#include <math.h>

#include "agent.h"

#define KEY_LENGTH 512
#define STATE_FACTOR 10000
#define ALPHA_FACTOR 10
//#define ALPHA_RULE rand() % ALPHA_FACTOR + 1

Agent::Agent(std::string _id)
  :id(_id),
   state(0.0),
   alpha(1),
   long_state(0),
   diff_state(0)
{
  // Generate key pair
  paillier_keygen(KEY_LENGTH,
		  &pubKey,
		  &prvKey,
		  paillier_get_rand_devurandom);

  // Open the log file:
  logfile = fopen(id.append(".log").c_str(), "w");
  if (logfile == NULL)
    {
      printf("%s log open failed\n", id.c_str());
    }
  
  alpha = rand() % ALPHA_FACTOR + 1;
}

Agent::~Agent()
{
  // Close the log file
  if(logfile != NULL)
    fclose(logfile);

  // Destroy the key pair
  paillier_freepubkey(pubKey);
  paillier_freeprvkey(prvKey);
}

int Agent::communicate(std::list<Agent*>& peers)
{
  // Convert and encrypt the current state
  // May want to log enc_state
  long_state = -(long) lround(state * STATE_FACTOR);

  // encrypt the state
  paillier_plaintext_t* m_s = paillier_plaintext_from_ui(long_state);
  paillier_ciphertext_t* c_s = NULL;
  c_s = paillier_enc(NULL, pubKey, m_s,
		     paillier_get_rand_devurandom);

  paillier_ciphertext_t* c_res = paillier_create_enc_zero();
  /*
    For each peer in the list,
    > Communicate
    > add to diff_state
  */
  diff_state = 0;
  long result =0;
  for(std::list<Agent*>::iterator it= peers.begin();
      it != peers.end(); ++it)
    {
      (*it)->exchange(pubKey, c_s, c_res);
      result = ciphertext_to_long(c_res);
      diff_state += alpha * result;
    }

  paillier_freeplaintext(m_s);
  paillier_freeciphertext(c_s);
  paillier_freeciphertext(c_res);
  return 0;
}

double Agent::setState(const double st)
{
  state = st;
  // initialize alpha in [1, ALPHA_FACTOR]
  alpha = updateAlpha();
  
  // a new state is set, log the state
  logState();
  return state;
}

int Agent::updateState()
{
  /*
    > convert diff_state to double
    > and add to state 
    > change alpha
    > log the state
  */
  state += diff_state / ( (double) STATE_FACTOR * ALPHA_FACTOR * ALPHA_FACTOR);

  alpha = updateAlpha();

  logState();
  return 0;
}

int Agent::logState()
{
  fprintf(logfile, "%8.4lf\t%2ld\t%ld\n", state, alpha, diff_state);
}


/*
  This function is called by another Agent 
 */
int Agent::exchange(paillier_pubkey_t* pub,
		    paillier_ciphertext_t* msg_in,
		    paillier_ciphertext_t* msg_out)
{
  // create the negative of the current state
  long_state = (long) lround(state * STATE_FACTOR);

  // encrypt the state
  paillier_plaintext_t* m_s = paillier_plaintext_from_ui(long_state);
  paillier_plaintext_t* m_a = paillier_plaintext_from_ui(alpha);
  
  paillier_ciphertext_t* c_s = NULL;
  c_s = paillier_enc(NULL, pub, m_s,
		     paillier_get_rand_devurandom);

  paillier_ciphertext_t* c_d = paillier_create_enc_zero();

  // c_d = ENC( x_j + (-x_i) )
  paillier_mul(pub, c_d, msg_in, c_s);

  if (msg_out == NULL)
    msg_out = paillier_create_enc_zero();
  
  // msg_out = ENC( alpha * (x_j + (-x_i) )
  paillier_exp(pub, msg_out, c_d, m_a);


  paillier_freeplaintext(m_s);
  paillier_freeplaintext(m_a);
  paillier_freeciphertext(c_s);
  paillier_freeciphertext(c_d);
  return 0;
}

long Agent::ciphertext_to_long(paillier_ciphertext_t* c)
{
  paillier_plaintext_t* m = paillier_dec(NULL, pubKey, prvKey, c);

  size_t nBytes = 0;
  unsigned char* bytes = (unsigned char*) mpz_export(0, &nBytes, 1, 1, 0, 0, m->m);

  long int e = 0;
  //  assert( nBytes > sizeof(a));
  //  for(int i=nBytes-1; i >= nBytes-sizeof(a); --i)
  for(int i= nBytes-sizeof(long); i < nBytes; i++)
  {
      e = (e << 8) | bytes[i];
  }

  paillier_freeplaintext(m);
  free(bytes);
  return e;
}

long Agent::updateAlpha()
{
  //  return rand() % ALPHA_FACTOR + 1;
  //  return ALPHA_FACTOR;
  return alpha;
}
