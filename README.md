# ACP-Basic-2D-Graphics-Editor

A lightweight terminal-based 2D graphics drawing application developed in C. This editor enables users to compose artistic compositions using fundamental geometric shapes on a character-based canvas. Employ underscore (`_`) characters to denote empty regions and asterisk (`*`) symbols to depict the drawn elements.

This endeavor exemplifies essential C programming principles including multidimensional arrays, data structures, algorithmic design, input validation, and computational geometry.

## Project Summary

A mini-project created for Advanced C Programming (ACP), Semester 2. This application demonstrates how to implement shape rendering algorithms and object management within a terminal interface.

## Capabilities

- Construct lines, rectangles, circles, and triangular shapes
- Accumulate numerous geometric objects onto a unified drawing surface
- Remove unwanted shapes by referencing their object identifier
- Adjust properties of existing geometric objects seamlessly
- Enumerate all presently active objects in the composition
- Reset the entire visual composition to a blank state
- Preview the current drawing instantaneously
- Safely disregard pixels located outside canvas boundaries
- Validate and reject improperly formatted numeric entries

## Operational Architecture

The system utilizes a 24 × 60 character-based drawing surface:

- `_` denotes an unoccupied cell
- `*` represents a rendered pixel
- The drawing data persists in a 2D character matrix: `canvas[HEIGHT][WIDTH]`
- User-created shapes are catalogued in: `Shape objects[MAX_OBJECTS]`

### Rendering Process

1. User initiates shape creation, deletion, or alteration
2. Application clears the visual display
3. System re-renders all stored objects from the object registry
4. Updated visualization is presented

This methodology maintains synchronization between the stored geometric data and the displayed output.

## Shape Specifications

| Shape | Parameters |
|-------|-----------|
| Line | Starting coordinates and terminating coordinates |
| Rectangle | Upper-left position and diagonal lower-right position |
| Circle | Focal point and radial dimension |
| Triangle | Coordinates of the three vertices |

## Project Layout

```
.
├── main.c       # Core editor application source
├── README.md    # Documentation and guidelines
└── .gitignore   # Excluded build artifacts
```

## Compilation Procedure

Utilize GCC compiler to generate the executable:

```bash
gcc main.c -o graphics_editor.exe
```

## Execution Instructions

Launch the compiled application:

```bash
./graphics_editor.exe
```

Choose from the interactive menu:

```
2D Graphics Editor
1. Display picture
2. Add object
3. Delete object
4. Modify object
5. List objects
6. Clear all objects
7. Exit
```

## Technical Implementation Details

- **Coordinate System**: `x` represents horizontal position, `y` represents vertical position
- **Canvas Origin**: Position `(0, 0)` corresponds to the upper-left corner
- **Line Drawing Algorithm**: Bresenham's line algorithm for precise pixel placement
- **Circle Rendering**: Midpoint circle algorithm for accurate circular geometry
- **Input Processing**: Comprehensive validation rejects malformed numerical entries

## Programming Concepts Demonstrated

This undertaking illustrates:

- Utilization of 2D character arrays in C
- Object management via structured data types
- Modular function-oriented architecture
- Implementation of computational geometry algorithms
- Canvas reconstruction from persistent object data
- Robust input validation and error handling

## Building and Testing

```bash
# Compile with warnings enabled
gcc -Wall -Wextra main.c -o graphics_editor.exe

# Execute the program
./graphics_editor.exe
```

## Usage Example Workflow

1. Select "Add object" to create a shape
2. Choose shape type (rectangle, circle, line, or triangle)
3. Supply coordinate values when prompted
4. Select "Display picture" to visualize your composition
5. Modify or remove objects as desired

## Observations

- Terminal-based graphics interface, not a graphical user interface (GUI)
- Maximum concurrent objects: 100
- Canvas dimensions: 24 rows by 60 columns
- Application stores object metadata for non-destructive editing
- Build artifacts (executables, object files) are excluded from version control

## Academic Context

Created as a semester-long mini-project demonstrating mastery of fundamental C programming concepts and practical software engineering practices.
