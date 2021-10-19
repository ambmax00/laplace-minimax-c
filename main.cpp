#include "quadmath.hpp"
#include "minimax.hpp"
#include <vector>

bool nearly_equal(double a1, double a2, int ndigits)
{
  
  double factor = std::pow(10, ndigits);
  double epsilon = std::pow(10, -ndigits);
  
  double b1 = std::round(a1*factor)/factor;
  double b2 = std::round(a2*factor)/factor;
    
  if (b1 == 0 && b2 == 0)
    return true;

  return std::abs(b1 - b2) < epsilon * std::pow(2.0, static_cast<int>(
    std::log2(std::max(std::abs(b1), std::abs(b2)))));
}

void test_ref(int nlap, std::vector<double> eps, std::vector<double> weights_ref,
  std::vector<double> expos_ref) {
  
  const int ndig = 10;
  
  double ymin = 2.0 * (eps[2]-eps[1]);
  double ymax = 2.0 * (eps[3]-eps[0]);
    
  minimax myminimax(0);
    
  myminimax.compute(nlap,ymin,ymax);
  
  auto weights_calc = myminimax.weights();
  auto expos_calc = myminimax.exponents();
  
  for (int ilap = 0; ilap < nlap; ++ilap) {
    
    double wr_ilap = weights_ref[ilap];
    double wc_ilap = weights_calc[ilap];
    double er_ilap = expos_ref[ilap];
    double ec_ilap = expos_calc[ilap];
    
    if (!nearly_equal(wr_ilap,wc_ilap,ndig)) {
      throw std::runtime_error("Weights are not equal: "
        + std::to_string(wr_ilap) + " " 
        + std::to_string(wc_ilap));
    }
    
    if (!nearly_equal(er_ilap,ec_ilap,ndig)) {
      throw std::runtime_error("Exponents are not equal: "
        + std::to_string(wr_ilap) + " " 
        + std::to_string(wc_ilap)); 
    }
    
  }
  
}

bool test1() {
  
  minimax mymax(1);

  int n = 3;
  std::vector<double> eps = {-2.0, -1.0, 1.0, 2.0};

  std::vector<double> omega_ref = {
    0.1867648544, 
    0.4897225836, 
    1.0404470994
  };

  std::vector<double> alpha_ref = {
    0.0718733276, 
    0.4011592651, 
    1.1266216172
  };
  
  try {
    test_ref(n, eps, omega_ref, alpha_ref);
    std::cout << "Test 1 completed." << std::endl;
    return true;
  } catch (const std::exception& err) {
    std::cout << "Test 1 failed: " << err.what() << std::endl;
    return false;
  }
    
}

bool test2() {

  int n = 8;
  std::vector<double> eps = {-23.0, -1.7, 1.7, 23.0};

  std::vector<double> omega_ref = {
    0.0125691396,
    0.0309289959,
    0.0540252512,
    0.0867298102,
    0.1372836182,
    0.2198332379,
    0.3641556991,
    0.6778500284
  };

  std::vector<double> alpha_ref = {
    0.0048668703,
    0.0263616711,
    0.0682809545,
    0.1375783219,
    0.2476309385,
    0.4226716810,
    0.7073431760,
    1.2030465340
  };
  
  try {
    test_ref(n, eps, omega_ref, alpha_ref);
    std::cout << "Test 2 completed." << std::endl;
    return true;
  } catch (const std::exception& err) {
    std::cout << "Test 2 failed: " << err.what() << std::endl;
    return false;
  }
  
}

bool test3() {
  
  int n = 25;
  std::vector<double> eps = {-2.3e+3, -0.8e-1, 0.8e-1, 2.3e+3};

  std::vector<double> omega_ref = {
    0.0001469099,
    0.0003693775,
    0.0006730326,
    0.0011484850,
    0.0019426055,
    0.0032759395,
    0.0054813492,
    0.0090717111,
    0.0148381889,
    0.0239916129,
    0.0383684097,
    0.0607302985,
    0.0951980645,
    0.1478758062,
    0.2277450338,
    0.3479417620,
    0.5275833719,
    0.7944097216,
    1.1887157389,
    1.7696003867,
    2.6261576538,
    3.9014600347,
    5.8570041856,
    9.1039053934,
    15.9876940125
  };

  std::vector<double> alpha_ref = {
    0.0000567494,
    0.0003106954,
    0.0008221133,
    0.0017133953,
    0.0032245215,
    0.0057771354,
    0.0100651294,
    0.0171984480,
    0.0289293446,
    0.0479969786,
    0.0786435878,
    0.1273806420,
    0.2041177907,
    0.3238152880,
    0.5088877799,
    0.7926824362,
    1.2244920757,
    1.8767740637,
    2.8556015341,
    4.3160792262,
    6.4861350104,
    9.7068110990,
    14.5126669046,
    21.8390582637,
    33.8353980668
  };
  
  try {
    test_ref(n, eps, omega_ref, alpha_ref);
     std::cout << "Test 3 completed." << std::endl;
    return true;
  } catch (const std::exception& err) {
    std::cout << "Test 3 failed: " << err.what() << std::endl;
    return false;
  }
  
}

bool test4() {
  
  int n = 3;

  std::vector<double> eps = {
    -20.557772190846030, 
    -0.5454512125421230, 
    +1.1900668172888584, 
    +2.6379585887262555};
    
  std::vector<double> omega_ref = {
    0.0686417550,
    0.2491952611,
    0.7883072458
  };

  std::vector<double> alpha_ref = {
    0.0253887061,
    0.1695993438,
    0.6362664092
  };
  
  try {
    test_ref(n, eps, omega_ref, alpha_ref);
    std::cout << "Test 4 completed." << std::endl;
    return true;
  } catch (const std::exception& err) {
    std::cout << "Test 4 failed: " << err.what() << std::endl;
    return false;
  }
  
}

int main() {

  int nsuccess = 0;

  nsuccess += test1();
  nsuccess += test2();
  nsuccess += test3();
  nsuccess += test4();
  
  std::cout << "Done. " << nsuccess << "/4" << " tests completed sucessfully." << std::endl;
  
  return 0;
  
}
