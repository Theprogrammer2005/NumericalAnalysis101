#include <iostream>
#include <cmath>
#include <functional>
#include <iomanip>

// Function to integrate (example: x^2 + 2x + 1)
double f(double x) {
    return x * x + 2 * x + 1;
}

// Another example function (sin(x))
double g(double x) {
    return sin(x);
}

// Simpson's 1/3 rule implementation
double simpsonsRule(std::function<double(double)> func, double a, double b, int n) {
    // Ensure n is even for Simpson's 1/3 rule
    if (n % 2 != 0) {
        n++; // Make n even
        std::cout << "Note: n adjusted to " << n << " (must be even for Simpson's 1/3 rule)\n";
    }
    
    double h = (b - a) / n; // Step size
    double sum = func(a) + func(b); // First and last terms
    
    // Add odd-indexed terms (multiplied by 4)
    for (int i = 1; i < n; i += 2) {
        sum += 4 * func(a + i * h);
    }
    
    // Add even-indexed terms (multiplied by 2)
    for (int i = 2; i < n; i += 2) {
        sum += 2 * func(a + i * h);
    }
    
    return (h / 3) * sum;
}

// Simpson's 3/8 rule implementation (alternative method)
double simpsons38Rule(std::function<double(double)> func, double a, double b, int n) {
    // Ensure n is divisible by 3 for Simpson's 3/8 rule
    while (n % 3 != 0) {
        n++;
    }
    
    double h = (b - a) / n;
    double sum = func(a) + func(b);
    
    for (int i = 1; i < n; i++) {
        if (i % 3 == 0) {
            sum += 2 * func(a + i * h);
        } else {
            sum += 3 * func(a + i * h);
        }
    }
    
    return (3 * h / 8) * sum;
}

// Function to calculate the exact integral for comparison (for f(x) = x^2 + 2x + 1)
double exactIntegral(double a, double b) {
    auto F = [](double x) { return (x * x * x) / 3 + x * x + x; };
    return F(b) - F(a);
}

int main() {
    double a, b;
    int n, choice;
    
    std::cout << "Simpson's Rule Numerical Integration\n";
    std::cout << "====================================\n\n";
    
    // Get integration bounds
    std::cout << "Enter lower bound (a): ";
    std::cin >> a;
    std::cout << "Enter upper bound (b): ";
    std::cin >> b;
    std::cout << "Enter number of intervals (n): ";
    std::cin >> n;
    
    std::cout << "\nChoose function to integrate:\n";
    std::cout << "1. f(x) = x^2 + 2x + 1\n";
    std::cout << "2. g(x) = sin(x)\n";
    std::cout << "Enter choice (1 or 2): ";
    std::cin >> choice;
    
    std::cout << std::fixed << std::setprecision(6);
    
    if (choice == 1) {
        // Using Simpson's 1/3 rule
        double result13 = simpsonsRule(f, a, b, n);
        std::cout << "\nUsing f(x) = x^2 + 2x + 1\n";
        std::cout << "Simpson's 1/3 rule result: " << result13 << std::endl;
        
        // Calculate exact value for comparison
        double exact = exactIntegral(a, b);
        std::cout << "Exact integral value: " << exact << std::endl;
        std::cout << "Absolute error: " << std::abs(exact - result13) << std::endl;
        
        // Using Simpson's 3/8 rule for comparison
        double result38 = simpsons38Rule(f, a, b, n);
        std::cout << "Simpson's 3/8 rule result: " << result38 << std::endl;
        std::cout << "Error with 3/8 rule: " << std::abs(exact - result38) << std::endl;
        
    } else if (choice == 2) {
        // Using Simpson's 1/3 rule with sin(x)
        double result13 = simpsonsRule(g, a, b, n);
        std::cout << "\nUsing g(x) = sin(x)\n";
        std::cout << "Simpson's 1/3 rule result: " << result13 << std::endl;
        
        // For sin(x), exact integral is -cos(b) + cos(a)
        double exact = -cos(b) + cos(a);
        std::cout << "Exact integral value: " << exact << std::endl;
        std::cout << "Absolute error: " << std::abs(exact - result13) << std::endl;
        
        // Using Simpson's 3/8 rule for comparison
        double result38 = simpsons38Rule(g, a, b, n);
        std::cout << "Simpson's 3/8 rule result: " << result38 << std::endl;
        std::cout << "Error with 3/8 rule: " << std::abs(exact - result38) << std::endl;
    }
    
    // Show the formulas used
    std::cout << "\n" << std::string(50, '-') << std::endl;
    std::cout << "Formulas used:\n";
    std::cout << "Simpson's 1/3 rule: ∫f(x)dx ≈ (h/3)[f(x₀) + 4f(x₁) + 2f(x₂) + 4f(x₃) + ... + f(xₙ)]\n";
    std::cout << "Simpson's 3/8 rule: ∫f(x)dx ≈ (3h/8)[f(x₀) + 3f(x₁) + 3f(x₂) + 2f(x₃) + ... + f(xₙ)]\n";
    std::cout << "where h = (b-a)/n\n";
    
    return 0;
}
