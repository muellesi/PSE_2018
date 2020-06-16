#pragma once

#include <vector>
#include <memory>

#include <MarkerInfo.hpp>


/// Sensor and image processing manager.
class SensorManager {
public:
    SensorManager(const SensorManager &) = delete;

    SensorManager &operator=(const SensorManager &) = delete;

    /// Get the singleton instance of the sensor manager.
    static SensorManager *getInstance() {
        static SensorManager instance; // Guaranteed to be destroyed.
        // Instantiated on first use.
        return &instance;
    }

    /// Update color and depth data, and perform marker detection.
    bool runOnce() {
        return true;
    }

    /// Get the list of currently detected markers.
    std::vector<MarkerInfo> getMarkerList() {
        return debugMarkerInfoList;
    }

    /// Get the width of the sensor data.
    int getSensorWidth() {
        return 1024;
    }

    /// Get the height of the sensor data.
    int getSensorHeight() {
        return 600;
    }

    /// Get the depth [m] at the given pixel in the sensor data.
    double getDepth(int x, int y) {
        return depth;
    }

    /// Get an average of the current processing FPS
    float getFps() {
        return 10.0f;
    }

    void setDebugMarkerInfoList(const std::vector<MarkerInfo> &debugMarkerInfoList) {
        SensorManager::debugMarkerInfoList = debugMarkerInfoList;
    }

    void setDepth(double depth) {
        SensorManager::depth = depth;
    }
protected:
    SensorManager() = default;

    ~SensorManager() = default;

    std::vector<MarkerInfo> debugMarkerInfoList;
    double depth{};


};
