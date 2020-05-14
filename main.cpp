#include <boost/multiprecision/cpp_int.hpp>
#include <boost/multiprecision/miller_rabin.hpp>
#include <iostream>
#include <iomanip>

using namespace boost::random;
using namespace boost::multiprecision;

int find_primitive(cpp_int num)
{
    namespace mp = boost::multiprecision;
    for(int i = 2; i <= 10; i++){
        for(int j = 2; j < num -1; j++){
            cpp_int number = mp::pow(mp::cpp_int(i), j);
            if(number % num == 1) break; 
        }
    }
}

cpp_int find_safe_prime()
{
    mt11213b base_gen(clock());
    independent_bits_engine<mt11213b, 256, cpp_int> gen(base_gen);

    mt19937 gen2(clock());

   for(unsigned i = 0; i < 100000; ++i)
   {
      cpp_int n = gen();
      if(miller_rabin_test(n, 25, gen2))
      {
         // Value n is probably prime, see if (n-1)/2 is also prime:
         if(miller_rabin_test((n-1)/2, 25, gen2))
         {
            return n;
         }
      }
   }
}

int main()
{

    cpp_int p = find_safe_prime();
    std::cout << p << std::endl;

    std::cout << find_primitive(p);

   return 0;
}