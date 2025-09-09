# Course Prerequisite Planner and Campus Route Finder

This project is a **C-based application** that combines two functionalities for first-year university students:

1. **Campus Route Finder** – Helps students calculate the shortest distance between two buildings on campus using **Dijkstra’s Algorithm**.
2. **Course Prerequisite Planner** – Helps students sort and plan their courses based on prerequisites using **Topological Sort**.

---

## 📂 Project Structure

* **`P4_1221858_YahyaSarhan_3.c`** – Main source code implementing the application logic.
* **`input_buildings.txt`** – File containing the list of buildings and distances between them (graph data for shortest path calculation).
* **`input_courses.txt`** – File containing the list of courses and their prerequisites (graph data for topological sort).

---

## 📌 Features

1. **Campus Route Finder**

   * Loads building names and their distances from `input_buildings.txt`.

   * Represents the campus map as a graph.

   * Allows the user to input a **start** and **end building**, then finds the shortest path and prints:

     * ✅ The route (path of buildings)
     * ✅ The total distance

   * Implemented using **Dijkstra’s Algorithm** with a min-heap priority queue.

2. **Course Prerequisite Planner**

   * Loads courses and their prerequisites from `input_courses.txt`.
   * Represents prerequisites as a **directed acyclic graph (DAG)**.
   * Sorts courses using **Topological Sort** so students know the correct order of courses to take.
   * Displays the sorted courses.

3. **User-Friendly Menu**

   ```
   1. Load the two files.
   2. Calculate the shortest distance between two buildings.
   3. Print the shortest route between two buildings and the total distance.
   4. Sort the courses using the topological sort.
   5. Print the sorted courses.
   6. Exit the application.
   ```

---

## 🏗️ How It Works

1. **Load Data**

   * The user first selects option `1` to load `input_buildings.txt` and `input_courses.txt`.
   * Buildings and distances are stored as a graph.
   * Courses and prerequisites are stored in a separate graph.

2. **Shortest Path Calculation (Dijkstra)**

   * The user selects option `2`.
   * Inputs start and end building names.
   * The system calculates and stores the shortest distance.

3. **Print Shortest Route**

   * The user selects option `3`.
   * Displays the shortest route and total distance between two buildings.

4. **Topological Sort**

   * The user selects option `4`.
   * Performs a topological sort on the course prerequisite graph.

5. **Print Sorted Courses**

   * The user selects option `5`.
   * Displays the ordered list of courses.

---

## 🖥️ Example Input Files

### `input_buildings.txt`

```
Masri#Aggad#70
Aggad#A.Shaheen#60
A.Shaheen#Bamieh#40
...
```

### `input_courses.txt`

```
COMP2310#COMP133
ENCS3340#COMP233#COMP133
COMP333#COMP2421
...
```

---

## ⚙️ Compilation & Execution

### Compile

```bash
gcc P4_1221858_YahyaSarhan_3.c -o planner
```

### Run

```bash
./planner
```

---

## 📑 Requirements

* **Language**: C
* **Libraries Used**: `stdio.h`, `stdlib.h`, `string.h`, `math.h`, `limits.h`
* **Algorithms Implemented**:

  * **Dijkstra’s Algorithm** (Shortest Path)
  * **Topological Sort** (Course Ordering)

---

## 🚦 Notes

* Ensure `input_buildings.txt` and `input_courses.txt` are present in the same directory as the executable.
* File formats must follow the specified structure (`#` as a separator).
* The program handles errors such as missing files or invalid building/course names.

---

## 👨‍🎓 Author

**Name**: Yahya Sarhan

