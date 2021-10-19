#include "quadmath.hpp"
#include "minimax.hpp"

int main() {

	minimax mx(1);
	
	double emin = -20.5519;
	double ehomo = -0.493214;
	double elumo = 0.186114;
	double emax = 4.14902;
	int k = 5;
	
	mx.compute(emin, ehomo, elumo, emax, k);

	float128 c = float128(9.62964972193617926527988971292463659e-35);
	
	std::cout << c << std::endl;

	/*float128 p = 1.0_q;
	
	float128 i = 5;
	
	float128 a = cos(i);
	
	std::cout << a << std::endl;
	
	Eigen::MatrixXq M = Eigen::MatrixXq::Random(5,5);
	
	Eigen::JacobiSVD<Eigen::MatrixXq> svd(M);
	
	std::cout << "SVD\n" << svd.singularValues() << std::endl;
	
	std::cout << M << std::endl;

-20.5519 -0.493214 0.186114 4.14902
	
0.0505014
0.156024
0.396858
0.965863
2.41703

0.0190711
0.116085
0.375278
1.01659
2.58142

	
	* 
	* 
	*/
}
