from(bucket: "light_data")
  |> range(start: -1h)  // Query the last 1 hour of data
  |> filter(fn: (r) => r["_measurement"] == "light_sensor")  // Filter by measurement
  |> filter(fn: (r) => r["_field"] == "light")  // Filter by field (light)
  |> aggregateWindow(every: 10s, fn: mean)  // Aggregate by minute, taking the mean value
  |> yield(name: "mean_light")  // Yield the result
