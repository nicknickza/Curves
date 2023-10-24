#include "curves.h"
#include <memory>
#include <algorithm>
#include <numeric>
#include <functional>

using namespace std;

// Function to generate a random curve object
std::unique_ptr<Curve> generateRandomCurve() {
    std::function<std::unique_ptr<Curve>()> curveCreators[] = {
        []() {
            double r = rand() % 10 + 1;
            return std::make_unique<Circle>(r);
        },
        []() {
            double a = rand() % 10 + 1;
            double b = rand() % 10 + 1;
            return std::make_unique<Ellipse>(a, b);
        },
        []() {
            double r = rand() % 10 + 1;
            double s = rand() % 10 + 1;
            return std::make_unique<Helix>(r, s);
        }
    };

    return curveCreators[rand() % 3]();
    
}

int main() {
    srand(time(0));

    std::vector<std::unique_ptr<Curve>> curves;
   {
        // Generate random curves
        unsigned numCurves = rand() % 8 + 5;
        while(--numCurves)
            curves.push_back(generateRandomCurve());
    }

    // Print coordinates and derivatives at t = PI/4
    double t = M_PI / 4;
    for (const auto& curve : curves) {
        std::vector<double> point = curve->getPoint(t);
        std::vector<double> derivative = curve->getDerivative(t);
        std::cout << "Curve Type: ";
        std::cout << (dynamic_cast<Circle*>(curve.get()) ? "Circle" : 
            dynamic_cast<Ellipse*>(curve.get()) ? "Ellipse" :
            dynamic_cast<Helix*>(curve.get()) ? "Helix" : "Other Curve") << std::endl;

        std::cout << "Point at t = PI/4: ";
        for (const auto& coord : point) {
            std::cout << coord << ' ';
        }
        std::cout << std::endl;

        std::cout << "Derivative at t = PI/4: ";
        for (const auto& coord : derivative) {
            std::cout << coord << ' ';
        }
        std::cout << std::endl;
    }

    // Filter circles and store them in a new container
    std::vector<Circle> circles;
    for (const auto& curve : curves) {
        Circle * circle = dynamic_cast<Circle*>(curve.get());
        if (circle) {
            circles.push_back(*circle);
        }
    }

    // Sort circles by radius
    std::sort(circles.begin(), circles.end(), [](const Circle& c1, const Circle& c2) {
        return c1.getRadius() < c2.getRadius();
    });
/*    
    for(const auto& circle : circles)
        cout << circle.getRadius() << ' ';
    cout << endl;
*/
    // Compute the sum of radii
    double sumRadii = std::accumulate(circles.begin(), circles.end(), 0.0,
                                      [](double sum, const Circle& circle) {
                                          return sum += circle.getRadius();
                                      });

    std::cout << "Sum of Radii: " << sumRadii << std::endl;

    return 0;
}