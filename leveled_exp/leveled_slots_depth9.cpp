#include <iostream>
#include <chrono>

#include <helib/helib.h>
#include <helib/intraSlot.h>

using namespace helib;
using namespace std;

  // N=23040 m=23377  m=97*(241) :-( m/phim(m)=1.01 C=179 D=3 E=1  
  // mvec="[97 241]" gens="[14943 971]" ords="[96 -40]" 

int main(void) {
  unsigned long p = 65537, m = 23377, r = 1, bits = 360;

  // generated using HElib/misc/params.cpp
  vector<long> mvec = {97, 241};
  vector<long> gens = {14943, 971};
  vector<long> ords = {96, -40};
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
  
  int num_mults = 9; // depth
  
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
