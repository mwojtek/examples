#include <doctest.h>
#include <utility> // before c++11 std::swap was located in algorithm

struct swappable {
   bool user_defined_swap_called = false;
};


struct non_swappable {
   bool user_defined_swap_called = false;
};


static inline void swap(swappable& lhs, swappable& rhs) noexcept {
   lhs.user_defined_swap_called = true;
   rhs.user_defined_swap_called = true;
}


TEST_CASE("swap") {
   swappable s1;
   swappable s2;

   REQUIRE(!s1.user_defined_swap_called);
   REQUIRE(!s2.user_defined_swap_called);

   SUBCASE("standard library swap") {
      /* should be used in case you don't need anything special
       */
      SUBCASE("incorrect usage") {
         /* in case you are sure you really need this - never call it
          * explicitly!
          *
          * let's say for now you don't need user-defined swap, but it is
          * possible that after a while some the situation changes and you'll
          * need one - in that case you will have to replace each place in code
          * where you are calling std::swap for this particular type
          */
         swappable s1;
         swappable s2;

         std::swap(s1, s2);
         CHECK(!s1.user_defined_swap_called);
         CHECK(!s2.user_defined_swap_called);
      }
      SUBCASE("correct usage") {
         /* declare std::swap with using so that compiler can find it but let
          * him decide which should be used - in case there's other 'swap'
          * dedicated for this particular type
          */
         using std::swap;

         swappable s1;
         swappable s2;

         swap(s1, s2);
         CHECK(s1.user_defined_swap_called);
         CHECK(s2.user_defined_swap_called);

         /* even if other type has the same fields (in below case ->
          * user_defined_swap_called) there will be called std::swap
          */
         non_swappable n1;
         non_swappable n2;

         swap(n1, n2);
         CHECK(!n1.user_defined_swap_called);
         CHECK(!n2.user_defined_swap_called);
      }
   }
   SUBCASE("user-defined swap") {
      /* should be used when more efficient algorithm is required
       */
      swappable s1;
      swappable s2;

      swap(s1, s2);
      CHECK(s1.user_defined_swap_called);
      CHECK(s2.user_defined_swap_called);
   }
}
