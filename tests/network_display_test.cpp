#include "dbus/network/network_display.h"
#include "dbus/network/network_types.h"
#include "tests/test_check.h"

#include <limits>
#include <string_view>

int main() {
  NetworkState state{
      .kind = NetworkConnectivity::Cellular,
      .connected = false,
      .resolving = false,
      .wirelessEnabled = true,
      .cellularEnabled = false,
  };

  TEST_CHECK(std::string_view(network_display::glyphForState(state)) == "antenna-bars-off");

  state.cellularEnabled = true;
  TEST_CHECK(std::string_view(network_display::glyphForState(state)) == "antenna");

  state.resolving = true;
  TEST_CHECK(std::string_view(network_display::glyphForState(state)) == "antenna-bars-1");

  state.resolving = false;
  state.connected = true;
  TEST_CHECK(std::string_view(network_display::glyphForState(state)) == "antenna-bars-1");

  state.cellularSignalStrength = 15;
  TEST_CHECK(std::string_view(network_display::glyphForState(state)) == "antenna-bars-2");
  state.cellularSignalStrength = 35;
  TEST_CHECK(std::string_view(network_display::glyphForState(state)) == "antenna-bars-3");
  state.cellularSignalStrength = 60;
  TEST_CHECK(std::string_view(network_display::glyphForState(state)) == "antenna-bars-4");
  state.cellularSignalStrength = 80;
  TEST_CHECK(std::string_view(network_display::glyphForState(state)) == "antenna-bars-5");

  TEST_CHECK(network_display::cellularSignalPercentFromRsrp(-141.0) == 0);
  TEST_CHECK(network_display::cellularSignalPercentFromRsrp(-140.0) == 0);
  TEST_CHECK(network_display::cellularSignalPercentFromRsrp(-116.0) == 25);
  TEST_CHECK(network_display::cellularSignalPercentFromRsrp(-44.0) == 100);
  TEST_CHECK(network_display::cellularSignalPercentFromRsrp(-43.0) == 100);
  TEST_CHECK(network_display::cellularSignalPercentFromRsrp(std::numeric_limits<double>::quiet_NaN()) == 0);

  return 0;
}