# Bloomberg C++ Mock Demos

This repository contains **mock Bloomberg API C++ demos** for Linux.  

## Files

- `demo.cpp` — Minimal skeleton connecting to Bloomberg API (fails gracefully if API not running)
- `demo_mock.cpp` — Simulated single-security PX_LAST request
- `demo_mock_historical.cpp` — Multi-security, multi-field mock historical data

## Compile & Run

```bash
g++ -std=c++17 demo_mock_historical.cpp -o demo_mock_historical
./demo_mock_historical


Save & exit.

---

### 4️⃣ Stage & commit

```bash
git add demo.cpp demo_mock.cpp demo_mock_historical.cpp README.md .gitignore
git commit -m "Initial commit: add local Bloomberg C++ mock demos"
