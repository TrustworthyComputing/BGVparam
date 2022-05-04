#include <iostream>
#include <chrono>

#include <helib/helib.h>
#include <helib/intraSlot.h>

using namespace helib;
using namespace std;


  // N=5292 m=5461  m=(43)*{127} m/phim(m)=1.03 C=166 D=1 E=1  
  // mvec="[5461]" gens="[6]" ords="[126]" 

int main(void) {
  unsigned long p = 65537, m = 5461, r = 1, bits = 60;

  // generated using HElib/misc/params.cpp
  vector<long> mvec = {5461};
  vector<long> gens = {6};
  vector<long> ords = {126};
  unsigned long c = 2;
  
  // build crypto context
  Context context = helib::ContextBuilder<helib::BGV>()
    .m(m).p(p).r(r).gens(gens).ords(ords).bits(bits)
    .c(c).mvec(mvec).build();
    
  // key gen
  SecKey secret_key(context);
  cout << "Security Level: " << context.securityLevel() << endl;
  secret_key.GenSecKey();
  addSome1DMatrices(secret_key);
  addFrbMatrices(secret_key);
  PubKey& public_key = secret_key;
  const EncryptedArray& ea = context.getEA();
  long slots = ea.size();
  cout << "Slots: " << slots << endl;
  
  
  Ptxt<helib::BGV> pt(context);
  Ctxt c1(public_key);
  Ctxt c2(public_key);
  
  int num_mults = 2; // depth
  
  // encrypt [1, 2, 3, 4...]
  for (int i = 0; i < slots; i++) {
    pt[i] = i;
  }
  public_key.Encrypt(c1, pt);
  public_key.Encrypt(c2, pt);

  for (int i = 0; i < num_mults; i++) {
    auto start_timer = chrono::high_resolution_clock::now();
    c1 *= c2; // ctxt multiplication
    auto stop_timer = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::milliseconds>(stop_timer-start_timer);
    cout << "Mult Time: " << duration.count() << "ms" << endl;
    // Decrypt running product to check correctness
    secret_key.Decrypt(pt, c1);
    // cout << "dec(prod) (#" << i << ") = " << pt << endl;
  }
  return 0;
}
