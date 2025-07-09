# 🌊 COMS3270P1 – Watershed Simulation Project

## 🏫 Iowa State University – Department of Computer Science
**COMS 3270 – Systems Programming** is a course at [Iowa State University](https://www.iastate.edu/), focusing on topics such as:
    - Memory management  
    - Pointers and data structures in C  
    - File processing and system simulation  
    - Design and implementation of a watershed flow simulator

### 📁 Project 1: Watershed
`COMS3270P1` is the first project of the course, requiring students to:
    - Read terrain data in point cloud format  
    - Simulate water flow and evaporation over the terrain  
    - Output water depth visualization as `.gif` images  
    - Implement neighbor-based computation and water dynamics  

### 🎯 Learning Objectives
    - Understand and use **pointers**, **structs**, and **dynamic memory**  
    - Apply **simple physical models** in C programming  
    - Work with basic bitmap image output  
    - Use **Makefiles** and modular compilation  

---

## 💧 Project Overview
This program simulates **water flow and evaporation** over a 2D terrain represented as a point cloud. Input data includes `(x, y, z)` coordinates indicating elevation. The simulation:
    - Initializes the water map  
    - Propagates water flow and evaporation over several steps  
    - Outputs `.gif` images visualizing water at each step  

---

## 🚀 How to Compile

### ⚙️ With `Makefile`
    make

🧹 Clean compiled files 
    make clean

🏃 How to Run
    ./watershed <ifile> <iter> <iwater> <wcoef> <ecoef> <ofilebase> <seq>

✅ Arguments
        Argument	            Description
        <ifile>	                Input point cloud file (.xyz format)
        <iter>	                Number of simulation steps
        <iwater>	            Initial water depth (same for all cells)
        <wcoef>	                Water flow coefficient (suggested: 0.01–0.2)
        <ecoef>	                Evaporation coefficient (suggested: 0.0–0.1)
        <ofilebase>	            Base name for output images
        <seq>	                Output frequency (e.g., 5 = every 5 steps; 0 = final image only)

📂 Example

    ./watershed data/test1.xyz 50 10.0 0.05 0.01 out 10

    Simulates 50 steps

    Adds 10.0 units of water initially to each cell

    Saves images: out-0.gif, out-10.gif, ..., out-50.gif

📁 Input Format

    The input .xyz file should follow the format:
        x   y   z
        0   0   48.5
        0   1   49.2
        ...

    Data is expected to be row-major ordered

    The number of points must match rows × cols for proper neighbor setup

🖼️ Output Visualization
    The program generates .gif images representing:

    Grayscale base: terrain elevation (z)

    Blue overlay: current water depth (wd)

    Deeper blue = higher water depth

---

## 🖼️ Output Image Files (`.gif`)

The simulation generates one or more `.gif` image files to visually represent the water depth and terrain over time.

### 📷 Example Output

| File        | Description |
|-------------|-------------|
| `out-0.gif` | Initial state of the terrain after water is added (Step 0) |
| `out-49.gif` | Final state after 49 simulation steps (Step 49) |

You can observe subtle to significant differences between frames depending on parameters like water flow coefficient (`wcoef`), evaporation (`ecoef`), and number of steps (`iter`).

### 🌀 Image Composition

Each image represents:

- **Grayscale background**: Terrain elevation (`z` value) mapped to brightness  
- **Blue overlay**: Water depth (`wd` value), rendered as a blue gradient  
  - Water depth = 0 → pure grayscale (no blue)
  - Water depth = `maxwd` or higher → fully blue overlay (`RGB(0, 0, 255)`)
  - Water in between → blended color between gray and blue

### 🧪 Image Output Logic

- If `seq = 5`, images will be saved every 5 steps:  
    `out-0.gif`, `out-5.gif`, `out-10.gif`, ..., `out-45.gif`, `out-49.gif`
- If `seq = 0`, only the final image is generated:  
    `out.gif`

### 🔍 Visual Changes Between Frames

Although changes may appear subtle (especially if water has stabilized), differences can include:

    - Shifts in blue tint intensity (indicating water movement)
    - Evaporation effects (slightly less blue in some areas)
    - Water redistribution toward lower elevation areas

For example:

    - 🔹 `out-0.gif`: Strong blue overlay in flat regions after water is added  
    - 🔹 `out-49.gif`: Smoother distribution and possibly reduced blue due to evaporation

🧠 Simulation Model
    At each step, water flows based on differences in elevation + water level between neighboring cells (N, S, E, W)

    Evaporation is applied after each step based on ecoef

👨‍💻 Author
    Name: Bùi Duy Minh

    Course: COMS 3270

    Institution: Iowa State University

## 🛠️ This submission was developed to fulfill the requirements of `COMS3270P1`, based on the official project specification from the Department of Computer Science, Iowa State University.

# references
https://www.geeksforgeeks.org/dynamically-growing-array-in-c/
https://www.hackerearth.com/practice/notes/void-pointer-in-c/
https://docs.silabs.com/mcu/5.8/efr32bg13/bmp-c
https://cppcoder.blogspot.com/2007/11/bmp-file-format.html
https://stackoverflow.com/questions/14279242/read-bitmap-file-into-structure
