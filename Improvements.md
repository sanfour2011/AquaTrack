# AquaTrack – Projektverbesserungen aus verschiedenen Quellen und Foren
## Improve Measurment noise
### 1. Low Pass Filter

To smooth the measurements, a low-pass filter can be used:

```cpp
filteredWeight = 0.9f * filteredWeight + 0.1f * weight;
```
However, this results in a sluggish response time. The two parameters (0.9 and 0.1) should be tested and optimized. For optimization, the values should be plotted in real-time and be adjustable.
Since the PlatformIO serial plotter does not allow data transfer, either:
An alternative serial plotter should be used, or A small Python program should be developed to receive the data via the serial interface, visualize it, and possibly send parameters back.

| Coefficients (old/new) | Response Speed | Stability          |
|------------------------|----------------|---------------------|
| 0.9 / 0.1              | Slow           | Very stable         |
| 0.8 / 0.2              | Medium         | Stable              |
| 0.7 / 0.3              | Fast           | Slight noise        |
| 0.6 / 0.4              | Very fast      | Significant noise   |

> **Note:** The sum of the factors **should** always equal 1.0, otherwise the filtered value will drift over time (either towards 0 or ±∞).

I did some research and found these examples to test:
### 2. Moving Average
Averages the last N values.

```cpp
float values[5] = {0}; // Buffer for 5 values
float movingAvg(float newVal) {
    for (int i = 0; i < 4; i++) values[i] = values[i+1]; // Shift
    values[4] = newVal;
    return (values[0] + values[1] + values[2] + values[3] + values[4]) / 5.0f;
}
```
### 3. Median Filter
Removes outliers, spikes.

```cpp
float medianFilter(float newVal) {
    static float buffer[5] = {0};
    buffer[0] = newVal;
    std::sort(buffer, buffer + 5); // <algorithm> ne
    eded
    return buffer[2]; // Middle value
}
```
### 4. Weighted Moving Average (WMA)
More weight is given to recent values. Should be Faster response than a simple moving average.

```cpp
float wma(float newVal) {
    static float buffer[5] = {0};
    // Weights: [0.1, 0.15, 0.2, 0.25, 0.3] (Sum = 1.0)
    return 0.1*buffer[0] + 0.15*buffer[1] + 0.2*buffer[2] + 0.25*buffer[3] + 0.3*newVal;
}
```

### 5. Kalman Filter 
Extremely precise, adaptive compromise between noise filtering and response time.

```cpp
float kalman(float newVal) {
    static float x = 0, p = 1, k, q = 0.1, r = 0.5;
    p = p + q;
    k = p / (p + r);
    x = x + k * (newVal - x);
    p = (1 - k) * p;
    return x;
}
```