#ifndef STOPWATCH_LOGIC_H
#define STOPWATCH_LOGIC_H

struct StopwatchState {
  bool isRunning;
  unsigned long elapsedMs;
  unsigned long lastStartTimeMs;
};

inline void stopwatchReset(StopwatchState &state) {
  state.isRunning = false;
  state.elapsedMs = 0;
  state.lastStartTimeMs = 0;
}

inline void stopwatchStart(StopwatchState &state, unsigned long nowMs) {
  if (!state.isRunning) {
    state.isRunning = true;
    state.lastStartTimeMs = nowMs;
  }
}

inline void stopwatchStop(StopwatchState &state, unsigned long nowMs) {
  if (state.isRunning) {
    state.elapsedMs += nowMs - state.lastStartTimeMs;
    state.isRunning = false;
    state.lastStartTimeMs = 0;
  }
}

inline void stopwatchToggle(StopwatchState &state, unsigned long nowMs) {
  if (state.isRunning) {
    stopwatchStop(state, nowMs);
  } else {
    stopwatchStart(state, nowMs);
  }
}

inline unsigned long stopwatchElapsedMs(const StopwatchState &state, unsigned long nowMs) {
  if (!state.isRunning) {
    return state.elapsedMs;
  }

  return state.elapsedMs + (nowMs - state.lastStartTimeMs);
}

inline int stopwatchDisplayValue(const StopwatchState &state, unsigned long nowMs) {
  const unsigned long elapsedSeconds = stopwatchElapsedMs(state, nowMs) / 1000UL;

  if (elapsedSeconds >= 60UL * 60UL * 100UL) {
    return static_cast<int>(elapsedSeconds / (60UL * 60UL));
  }

  if (elapsedSeconds >= 100UL) {
    return static_cast<int>(elapsedSeconds / 60UL);
  }

  return static_cast<int>(elapsedSeconds);
}

#endif
