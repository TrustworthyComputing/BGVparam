#include <iostream>
#include <chrono>

#include <helib/helib.h>
#include <helib/intraSlot.h>

using namespace helib;
using namespace std;

  // N=39600 m=47333 m=(11)*{13}*331 m/phim(m)=1.19 C=354 D=2 E=1  
  // mvec="[331 143]" gens="[35751 23171]" ords="[330 20]" 

int main(void) {
  unsigned long p = 65537, m = 47333, r = 1, bits = 660;

  // generated using HElib/misc/params.cpp
  vector<long> mvec = {331, 143};
  vector<long> gens = {35751, 23171};
  vector<long> ords = {330, 20};
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
  
  int num_mults = 17; // depth
  
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
