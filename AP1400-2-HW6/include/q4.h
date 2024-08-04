#ifndef Q4_H
#define Q4_H

#include <vector>
#include <numeric>

namespace q4 {

    struct Vector2D {
        double x{};
        double y{};
    };

    struct Sensor {
        Vector2D pos;
        double accuracy;
    };

    Vector2D kalman_filter(const std::vector<Sensor>& sensors) {
        double totalAccuracy = std::accumulate(sensors.begin(), sensors.end(),0.0,
                                               [](double sum, const Sensor & sensor) {
            return sum + sensor.accuracy;
        });
        double weightedX = std::accumulate(sensors.begin(), sensors.end(), 0.0,
                                [totalAccuracy](double sum, const Sensor & sensor) {
            return sum + sensor.pos.x*(sensor.accuracy)/totalAccuracy;
        }
        );
        double weightedY = std::accumulate(sensors.begin(), sensors.end(), 0.0,
                                           [totalAccuracy](double sum, const Sensor & sensor) {
            return sum + sensor.pos.y*(sensor.accuracy)/totalAccuracy;
        });
        return {weightedX, weightedY};
    }

} // namespace q4
#endif //Q4_H