# Conway’s Game of Life (C Implementation)

This project is a simple **C implementation** of **Conway’s Game of Life** with support for several classic patterns (Blinker, Toad, Beacon, Pulsar, Pentadecathlon) and a random initial state.
It runs in the terminal and uses ASCII characters to display the grid.

---

## 📋 How It Works

This program simulates Conway’s Game of Life with three cell states:

* **ALIVE (`o`)**: A living cell.
* **DYING (`+`)**: A cell transitioning between alive and dead.
* **DEAD (`.`)**: An empty/dead cell.

Each cell evolves based on its neighbors:

* Live cells become dying.
* Dying cells may stay alive or die based on neighbors.
* Dead cells become alive if exactly 3 neighbors are alive or dying.

---

## 📁 Project Structure

* `main.c` — Main program logic.
* Uses **ANSI terminal control** to clear the screen for a simple animation effect.

---

## ⚙️ How to Compile

Use `gcc` to compile:

```bash
gcc -o game_of_life main.c -lncurses
```

> **Note:** The code uses `termcap` functions (`tgetent` and `tgetstr`).
> Make sure you have **libncurses** or **libtermcap** installed.

---

## ▶️ How to Run

```bash
./game_of_life <PATTERN_NUMBER>
```

**PATTERN\_NUMBER**:

| Number | Pattern            |
| ------ | ------------------ |
| 0      | Blinker            |
| 1      | Toad               |
| 2      | Beacon             |
| 3      | Pulsar             |
| 4      | Pentadecathlon     |
| 5      | Random (10% alive) |

**Example:**

```bash
./game_of_life 3
```

Runs the **Pulsar** pattern.

---

## 🧩 Patterns

Patterns are based on classic oscillators:

* **Blinker:** Small 3-cell line.
* **Toad:** 2x2 oscillator.
* **Beacon:** Pair of 2x2 blocks.
* **Pulsar:** Large oscillator.
* **Pentadecathlon:** Period-15 oscillator.
* **Random:** Random grid with \~10% alive cells.

---

## 🚦 Stopping Conditions

* Runs for **2000 generations** or until the grid stops changing.

---

## 🧹 Dependencies

* `stdio.h`, `stdlib.h`, `unistd.h`, `time.h`, `termcap.h`
* **Terminal must support clearing via termcap**

---

## 📝 License

This project is provided for educational purposes — free to use, modify, and share.
Add a proper license (like MIT) if you want to clarify usage rights.

---

## 💡 References

* [Conway’s Game of Life (Wikipedia)](https://en.wikipedia.org/wiki/Conway%27s_Game_of_Life)

---

**Have fun experimenting with Life! 🧬**
