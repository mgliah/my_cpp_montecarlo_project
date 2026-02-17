#include <iostream>
#include <cmath>
#include <random>
#include <vector>

// Helper functions

// Function to generate random numbers that are normally distributed
double generateGaussianNoise(double mean, double stdDev) {
    static std::mt19937 generator(std::random_device{}()); //set up a reusable random number generator
    std::normal_distribution<double> distribution(mean, stdDev); //set up the shape of the distribution we will sample from
    return distribution(generator);
}

// Function to calculate the payoff of a CALL option
double callOptionPayoff(double S, double K) {
    return std::max(S - K, 0.0);
}

// Function to calculate the payoff of a PUT option
double putOptionPayoff(double S, double K) {
    return std::max(K - S, 0.0);
}

// Monte Carlo Simulation Function
double monteCarloOptionPricer(double S0, double K, double r, double sigma, double T, int numSimulations, bool isCallOption) {
    double payoffSum = 0.0;

    for (int i = 0; i < numSimulations; i++) {
        //Generate random price path -- estimates stock price at the maturity of the option
        //Geometric Brownian motion: Initial price * e^((r - 0.5*sigma^2)T + sigma*sqrt(T)*Z)
        double ST = S0 * std::exp((r - 0.5 * sigma * sigma) * T + sigma * std::sqrt(T) * generateGaussianNoise(0.0, 1.0)); 

        //Calculate payoff for this path
        double payoff = isCallOption ? callOptionPayoff(ST, K) : putOptionPayoff(ST, K);

        //Accumulate payoff
        payoffSum += payoff;
    }

    //Calculate average payoff and discount to present value
    double avgPayoff = payoffSum / static_cast<double>(numSimulations);
    return std::exp(-r * T) * avgPayoff;
}

int main() {
    //Option parameters
    double S0;          //Initial stock price
    double K;           //Strike price
    double r;            //Risk-free rate
    double sigma;         //Volatility
    double T;               //Time to maturity (1 year)
    int numSimulations;//Number of simulations
    std::cout << "Enter the initial stock price: ";
    std::cin >> S0;
    std::cout << "Enter the strike price: ";
    std::cin >> K;
    std::cout << "Enter the risk-free rate: ";
    std::cin >> r;
    std::cout << "Enter the volatility: ";
    std::cin >> sigma;
    std::cout << "Enter the time to maturity in years: ";
    std::cin >> T;
    std::cout << "Enter the number of simulations: ";
    std::cin >> S0;
    
    //Calculate the option prices (call and put)
    double callPrice = monteCarloOptionPricer(S0, K, r, sigma, T, numSimulations, true);
    double putPrice = monteCarloOptionPricer(S0, K, r, sigma, T, numSimulations, false);

    //Output

    std::cout << "European Call Option Price: " << callPrice << std::endl;
    std::cout << "European Put Option Price: " << putPrice << std::endl;


}

