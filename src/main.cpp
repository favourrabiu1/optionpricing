#include <iostream>
#include <cmath>
#include <limits>

using namespace std;

class CallOptionPricingCalculator {
private:
    double strikePrice, underlyingPrice, expiryTime, riskFreeRate, volatility;

    double calculateD1() {
        double term = (riskFreeRate + (0.5 * volatility * volatility)) * expiryTime;
        double numerator = log(underlyingPrice / strikePrice) + term;
        double denominator = volatility * sqrt(expiryTime);

        if (denominator == 0 || expiryTime < 0) {
            cerr << "Error: Division by zero or square root of a negative number." << endl;
            return std::numeric_limits<double>::quiet_NaN();
        }

        return numerator / denominator;
    }

    double calculateD2() {
        double d1 = calculateD1();
        return d1 - volatility * sqrt(expiryTime);
    }

    double cumulativeDistributionFunction(double x) {
        return 0.5 * erfc(-x / sqrt(2.0));
    }

public:
    CallOptionPricingCalculator(double underlying, double strike, double time, double rate, double vol)
        : underlyingPrice(underlying), strikePrice(strike), expiryTime(time), riskFreeRate(rate), volatility(vol) {}

    double OptionPrice() {
        double d1 = calculateD1();
        double d2 = calculateD2();

        cout << "d1: " << d1 << ", d2: " << d2 << endl;

        double term1 = underlyingPrice * cumulativeDistributionFunction(d1);
        double term2 = strikePrice * exp(-riskFreeRate * expiryTime) * cumulativeDistributionFunction(d2);

        cout << "Term 1: " << term1 << ", Term 2: " << term2 << endl;

        return term1 - term2;
    }
};

int main() {
    CallOptionPricingCalculator optionPricer(100, 100.3, 30, 0.05, 0.2);
    double Price = optionPricer.OptionPrice();
    cout << "Price: " << Price << endl;
    return 0;
}
