#include <assert.h>
#include "../src/stopwatch_logic.h"

int main() {
  StopwatchState state{};

  stopwatchReset(state);
  assert(state.isRunning == false);
  assert(state.elapsedMs == 0);
  assert(state.lastStartTimeMs == 0);

  stopwatchStart(state, 1000);
  assert(state.isRunning == true);
  assert(state.elapsedMs == 0);
  assert(state.lastStartTimeMs == 1000);

  assert(stopwatchElapsedMs(state, 2500) == 1500);
  assert(stopwatchDisplayValue(state, 2500) == 1);

  stopwatchStop(state, 4000);
  assert(state.isRunning == false);
  assert(state.elapsedMs == 3000);
  assert(stopwatchDisplayValue(state, 4000) == 3);

  stopwatchStart(state, 5000);
  stopwatchToggle(state, 7000);
  assert(state.isRunning == false);
  assert(state.elapsedMs == 2000);

  stopwatchToggle(state, 8000);
  assert(state.isRunning == true);
  assert(state.elapsedMs == 2000);
  assert(stopwatchDisplayValue(state, 9000) == 3);

  StopwatchState unitState{};
  stopwatchStart(unitState, 0);
  assert(stopwatchDisplayValue(unitState, 100000) == 1);
  assert(stopwatchDisplayValue(unitState, 6000000) == 1);

  return 0;
}
