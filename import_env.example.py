Import("env")

env.Append(CPPDEFINES=[
  ("SENSOR_DASHBOARD_URL", "sensor-dashboard.trina.si"),
  ("WIFI_SSID", "wifiSSID"),
  ("WIFI_PASSWORD", "wifiPass"),
  ("ACCESS_TOKEN", "forwarderAccessToken")
])