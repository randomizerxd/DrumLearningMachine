# DrumLearningMachine
Arduino code for EGCP470/1 senior project
## Bluetooth Protocol
- The app sends data to the Arduino via bluetooth
- The app sends one byte of data for each setting

The first screen contains settings to select the beat, tempo and mode
The first screen sends data in the following order:
1. **Beat** 2. **Tempo** 3. **Mode**
- The Beat value received from the app will be:
  - `1`, `2`, `3`, and so on..
- The Tempo value received from the app will be:
  - `40bpm` -> `176 bpm`
- The Mode value received from the app will be:
  - `101` for Demo, `102` for Sequence, and `103` for PlayAlong


