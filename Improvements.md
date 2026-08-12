# AquaTrack – Measurement Noise Filtering

DSP algorithms and filtering strategies for load cell weight data.

## Filter Implementations

### 1. Low-Pass Filter - a moving Exponential Moving Average version
Simple IIR filter with minimal memory footprint. Higher smoothing factors introduce response lag.

```cpp
// alpha = 0.1f (smoothing factor, sum of coefficients = 1.0)
filteredWeight = alpha * weight + (1.0f - alpha) * filteredWeight;
```

| Coefficients (alpha / 1 - alpha) | Response Speed | Stability |
|---|---|---|
| 0.1 / 0.9 | Slow | Very stable |
| 0.2 / 0.8 | Medium | Stable |
| 0.3 / 0.7 | Fast | Slight noise |
| 0.4 / 0.6 | Very fast | Significant noise |

> **Note:** Coefficients must sum to 1.0 to prevent DC offset drift over time.

### 2. Moving Average (SMA)
Averages the last N samples using a ring buffer.

```cpp
float movingAvg(float newVal) {
    static float buffer[5] = {0};
    static uint8_t idx = 0;
    
    buffer[idx] = newVal;
    idx = (idx + 1) % 5;

    float sum = 0.0f;
    for (uint8_t i = 0; i < 5; i++) sum += buffer[i];
    return sum / 5.0f;
}
```

### 3. Median Filter
Rejects isolated impulse noise and ADC spikes without blurring step changes.

```cpp
#include <algorithm>

float medianFilter(float newVal) {
    static float buffer[5] = {0};
    static uint8_t idx = 0;
    
    buffer[idx] = newVal;
    idx = (idx + 1) % 5;

    float temp[5];
    std::copy(buffer, buffer + 5, temp);
    std::sort(temp, temp + 5);
    
    return temp[2];
}
```

### 4. Weighted Moving Average (WMA)
Applies higher weights to recent samples for better responsiveness than simple SMA.

```cpp
float wma(float newVal) {
    static float b[5] = {0};
    for (int i = 0; i < 4; i++) b[i] = b[i+1];
    b[4] = newVal;

    return (0.10f * b[0]) + (0.15f * b[1]) + (0.20f * b[2]) + (0.25f * b[3]) + (0.30f * b[4]);
}
```

### 5. 1D Kalman Filter
Optimal dynamic estimation balancing noise suppression and response latency.

```cpp
float kalman(float newVal) {
    static float x = 0.0f, p = 1.0f;
    const float q = 0.1f; // Process noise
    const float r = 0.5f; // Measurement noise

    p += q;
    float k = p / (p + r);
    x += k * (newVal - x);
    p *= (1.0f - k);
    
    return x;
}
```

## Tooling & Real-Time Tuning
PlatformIO's built-in serial plotter lacks two-way communication for dynamic parameter tuning.
* **TODO:** Build a Python tool (`pyserial` + `matplotlib`) to visualize raw/filtered channels and send updated filter parameters back over UART.
