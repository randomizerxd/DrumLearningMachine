# DrumLearningMachine
Arduino code for EGCP470/1 senior project
## Board
- **Arduino DUE**
## Bluetooth Protocol
- The app sends data to the Arduino via bluetooth
- The app sends one byte of data for each setting

### First Screen
The first screen contains settings to select the beat, tempo and mode\
The first screen sends data in the following order:
1. **Beat** 2. **Tempo** 3. **Mode**
- The Beat value received from the app will be:
  - `1`, `2`, `3`, and so on..
- The Tempo value received from the app will be:
  - `40bpm` -> `176 bpm`
- The Mode value received from the app will be:
  - `101` for Demo, `102` for Sequence, and `103` for PlayAlong
  
### Second Screen
The second screen currently contains a 'back' button and volume control buttons (up and down) for the Demo mode only\
The second screen sends data in the following manner:
- Send a 201 when the Back button has been pushed
- Send a 211 when the Volume Down button has been pushed
- Send a 212 when the Volume Up button has been pushed
