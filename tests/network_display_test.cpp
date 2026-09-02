#include "dbus/network/network_display.h"
#include "dbus/network/network_types.h"
#include "tests/test_check.h"

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
  TEST_CHECK(std::string_view(network_display::glyphForState(state)) == "antenna-bars-5");

  return 0;
}