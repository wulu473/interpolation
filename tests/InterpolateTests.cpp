
#include <boost/test/unit_test.hpp>
#include <vector>

#include "Interpolate.hpp"

BOOST_AUTO_TEST_SUITE(InterpoalteTests)

BOOST_AUTO_TEST_CASE(CompilationTest)
{
  std::vector<double> sFrom{0.  ,  1.  ,  2.  ,  3.};
  std::vector<double> uFrom{   0.5 ,  1.5 , -1.0   };
  std::vector<double> wFrom{   1.0 ,  1.0 ,  1.0   };

  double x = Interpolate::nonUniform1D(sFrom.begin(), sFrom.end(),
      uFrom.begin(),wFrom.begin(),1.5,2.5);

  BOOST_CHECK_CLOSE(x,0.25,1e-10);
}

BOOST_AUTO_TEST_SUITE_END()
