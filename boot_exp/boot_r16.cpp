#include <iostream>
#include <chrono>

#include <helib/helib.h>
#include <helib/intraSlot.h>

using namespace helib;
using namespace std;


// m: 55831 phi(m): 54000 slots: 2160.0
//  54000    25   55831  m=31*(1801) m/phim(m)=1.03 C=125 D=2 E=0  mvec="[31 1801]" gens="[19812 50593]" ords="[30 72]" 


int main(void) {
  unsigned long p = 2, m = 55831, r = 16, bits = 780; // plaintext space = 2^16

  // generated using HElib/misc/params.cpp
  vector<long> mvec = {31, 1801};
  vector<long> gens = {19812, 50593};
  vector<long> ords = {30, 72};
  unsigned long c = 2;
  
  // build crypto context
  Context context = helib::ContextBuilder<helib::BGV>()
    .m(m).p(p).r(r).gens(gens).ords(ords).bits(bits)
    .c(c).bootstrappable(true).mvec(mvec).build();
    
  // key gen
  SecKey secret_key(context);
  cout << "Security Level: " << context.securityLevel() << endl;
  secret_key.GenSecKey();
  addSome1DMatrices(secret_key);
  addFrbMatrices(secret_key);
  secret_key.genRecryptData(); // needed for bootstrapping
  PubKey& public_key = secret_key;
  const EncryptedArray& ea = context.getEA();
  std::vector<helib::zzX> unpackSlotEncoding;
  buildUnpackSlotEncoding(unpackSlotEncoding, ea); // needed for bootstrapping
  long slots = ea.size();
  cout << "Slots: " << slots << endl;
  
  
  Ptxt<helib::BGV> pt(context);
  Ctxt c1(public_key);
  Ctxt c2(public_key);
  
  int num_mults = 100; // depth
  
  // encrypt [3, 3, 3, 3, ... 3]
  for (int i = 0; i < slots; i++) {
    pt[i] = 3;
  }
  public_key.Encrypt(c1, pt);
  public_key.Encrypt(c2, pt);

  for (int i = 0; i < num_mults; i++) {
    c1 *= c2; // ctxt multiplication
    cout << "Capacity before boot: " << c1.bitCapacity() << endl;
    if (c1.bitCapacity() < 100) {
      auto start_timer = chrono::high_resolution_clock::now();
      public_key.thinReCrypt(c1); // bootstrap
      auto stop_timer = chrono::high_resolution_clock::now();
      auto duration = chrono::duration_cast<chrono::milliseconds>(stop_timer-start_timer);
      cout << "Boot Time: " << duration.count() << "ms" << endl;
      cout << "Capacity after boot: " << c1.bitCapacity() << endl;
    }
    // Decrypt running product to check correctness
    secret_key.Decrypt(pt, c1);
    cout << "dec(prod) (#" << i << ") = " << static_cast<long>(pt[0]) << endl;
  }
  return 0;
}
