from(bucket: "light_data")
  |> range(start: -1h)
  |> filter(fn: (r) => r["_measurement"] == "light_sensor")
  |> filter(fn: (r) => r["_field"] == "light")
  |> histogram(
      column: "_value",
      bins: [50.0, 100.0, 200.0, 500.0, 1000.0, 2000.0, 3000.0, 4000.0, 5000.0, 6000.0]
    )
  |> yield(name: "histogram")
