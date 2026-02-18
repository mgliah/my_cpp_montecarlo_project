Monte Carlo Option Pricer
A command-line tool written in C++ that prices European call and put options using Monte Carlo simulation and Geometric Brownian Motion (GBM).
How It Works
The pricer simulates thousands of possible future stock price paths using the GBM formula.

Where:
S0​ = initial stock price

r = risk-free rate

sigma = volatility

T = time to maturity

Z = standard normal random variable


The option payoff is calculated for each simulated path, averaged across all simulations, and discounted back to present value.
