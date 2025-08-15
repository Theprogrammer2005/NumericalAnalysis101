#include <iostream>
#include <functional>
#include <cmath>

using namespace std;

// Function to perform Runge-Kutta 4th order method
float rungeKutta(float x0, float y0, float x, float h, function<float(float, float)> dydx) {
    int n = static_cast<int>((x - x0) / h);
    float y = y0;
    float x_current = x0;

    for (int i = 0; i < n; i++) {
        // Calculate the four RK4 coefficients
        float k1 = h * dydx(x_current, y);
        float k2 = h * dydx(x_current + h/2, y + k1/2);
        float k3 = h * dydx(x_current + h/2, y + k2/2);
        float k4 = h * dydx(x_current + h, y + k3);

        // Update y using weighted average of coefficients
        y = y + (k1 + 2*k2 + 2*k3 + k4) / 6;
        x_current += h;
    }

    return y;
}

int main() {
    // Example differential equation: dy/dx = -2x*y
    auto dydx = [](float x, float y) { return -2 * x * y; };


    float x0, y0, x, h;

    // Get input from user
    cout << "Enter initial x (x0): ";
    cin >> x0;
    cout << "Enter initial y (y0): ";
    cin >> y0;
    cout << "Enter final x: ";
    cin >> x;
    cout << "Enter step size (h): ";
    cin >> h;

    // Check for valid step size
    if (h <= 0) {
        cout << "Step size must be positive!" << endl;
        return 1;
    }

    // Calculate solution using Runge-Kutta
    float result = rungeKutta(x0, y0, x, h, dydx);

    // Output result
    cout << "The value of y at x = " << x << " is: " << result << endl;

    return 0;
}
