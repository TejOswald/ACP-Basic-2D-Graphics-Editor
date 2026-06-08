#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// Simple 2D drawing app - lets you draw shapes on a canvas
#define WIDTH 60
#define HEIGHT 24
#define MAX_OBJECTS 100

typedef enum {
    SHAPE_RECTANGLE,
    SHAPE_CIRCLE,
    SHAPE_LINE,
    SHAPE_TRIANGLE,
    SHAPE_NONE
} ShapeType;

typedef struct {
    ShapeType type;
    int x1, y1, x2, y2, x3, y3;
    int radius;
} Shape;

static char drawing[HEIGHT][WIDTH];
static Shape shapes[MAX_OBJECTS];
static int shapeCount = 0;

// Clear the canvas and fill with empty space
void initializeDrawing(void) {
    for (int y = 0; y < HEIGHT; y++)
        for (int x = 0; x < WIDTH; x++)
            drawing[y][x] = '_';
}

// Draw a single pixel at (x,y) if it's within bounds
void setPixel(int x, int y) {
    if (x >= 0 && x < WIDTH && y >= 0 && y < HEIGHT)
        drawing[y][x] = '*';
}

// Draw a line from (x1,y1) to (x2,y2) using Bresenham's algorithm
void renderLine(int x1, int y1, int x2, int y2) {
    int dx = abs(x2 - x1);
    int dy = abs(y2 - y1);
    int sx = (x1 < x2) ? 1 : -1;
    int sy = (y1 < y2) ? 1 : -1;
    int err = dx - dy;

    while (1) {
        setPixel(x1, y1);
        if (x1 == x2 && y1 == y2) break;
        int e2 = err * 2;
        if (e2 > -dy) {
            err -= dy;
            x1 += sx;
        }
        if (e2 < dx) {
            err += dx;
            y1 += sy;
        }
    }
}

// Draw a rectangle outline between two points
void renderRect(int x1, int y1, int x2, int y2) {
    int left = (x1 < x2) ? x1 : x2;
    int right = (x1 < x2) ? x2 : x1;
    int top = (y1 < y2) ? y1 : y2;
    int bottom = (y1 < y2) ? y2 : y1;

    // Draw top and bottom edges
    for (int x = left; x <= right; x++)
        setPixel(x, top), setPixel(x, bottom);
    // Draw left and right edges
    for (int y = top; y <= bottom; y++)
        setPixel(left, y), setPixel(right, y);
}

// Draw a circle using midpoint algorithm
void renderCircle(int cx, int cy, int radius) {
    int x = 0;
    int y = radius;
    int d = 3 - 2 * radius;

    while (x <= y) {
        setPixel(cx + x, cy + y);
        setPixel(cx - x, cy + y);
        setPixel(cx + x, cy - y);
        setPixel(cx - x, cy - y);
        setPixel(cx + y, cy + x);
        setPixel(cx - y, cy + x);
        setPixel(cx + y, cy - x);
        setPixel(cx - y, cy - x);

        if (d <= 0) {
            d += 4 * x + 6;
        } else {
            d += 4 * (x - y) + 10;
            y--;
        }
        x++;
    }
}

// Draw a triangle by connecting three points
void renderTriangle(int x1, int y1, int x2, int y2, int x3, int y3) {
    renderLine(x1, y1, x2, y2);
    renderLine(x2, y2, x3, y3);
    renderLine(x3, y3, x1, y1);
}

// Redraw everything from scratch
void refreshDrawing(void) {
    initializeDrawing();
    for (int i = 0; i < shapeCount; i++) {
        Shape *s = &shapes[i];
        // Render each shape based on its type
        switch (s->type) {
            case SHAPE_RECTANGLE:
                renderRect(s->x1, s->y1, s->x2, s->y2);
                break;
            case SHAPE_CIRCLE:
                renderCircle(s->x1, s->y1, s->radius);
                break;
            case SHAPE_LINE:
                renderLine(s->x1, s->y1, s->x2, s->y2);
                break;
            case SHAPE_TRIANGLE:
                renderTriangle(s->x1, s->y1, s->x2, s->y2, s->x3, s->y3);
                break;
            default:
                break;
        }
    }
}

// Display the canvas on screen
void showDrawing(void) {
    refreshDrawing();
    printf("\n");
    for (int y = 0; y < HEIGHT; y++) {
        for (int x = 0; x < WIDTH; x++)
            putchar(drawing[y][x]);
        putchar('\n');
    }
}

// Print details about a single shape
void describeShape(int index) {
    Shape *s = &shapes[index];
    printf("[%d] ", index + 1);
    switch (s->type) {
        case SHAPE_RECTANGLE:
            printf("Rectangle: (%d,%d) to (%d,%d)\n", s->x1, s->y1, s->x2, s->y2);
            break;
        case SHAPE_CIRCLE:
            printf("Circle: center (%d,%d), radius %d\n", s->x1, s->y1, s->radius);
            break;
        case SHAPE_LINE:
            printf("Line: (%d,%d) to (%d,%d)\n", s->x1, s->y1, s->x2, s->y2);
            break;
        case SHAPE_TRIANGLE:
            printf("Triangle: (%d,%d), (%d,%d), (%d,%d)\n", s->x1, s->y1, s->x2, s->y2, s->x3, s->y3);
            break;
        default:
            printf("Unknown object\n");
            break;
    }
}

// List all shapes in the drawing
void showAllShapes(void) {
    if (shapeCount == 0) {
        printf("No objects in the picture.\n");
        return;
    }
    for (int i = 0; i < shapeCount; i++)
        describeShape(i);
}

// Get a valid integer from user
int getInput(const char *prompt) {
    int value;
    printf("%s", prompt);
    while (scanf("%d", &value) != 1) {
        while (getchar() != '\n');
        printf("Invalid input. %s", prompt);
    }
    while (getchar() != '\n');
    return value;
}

// Ask user to enter coordinates/parameters for a shape
void inputShapeParameters(Shape *shape) {
    switch (shape->type) {
        case SHAPE_RECTANGLE:
            shape->x1 = getInput("Enter x1: ");
            shape->y1 = getInput("Enter y1: ");
            shape->x2 = getInput("Enter x2: ");
            shape->y2 = getInput("Enter y2: ");
            break;
        case SHAPE_CIRCLE:
            shape->x1 = getInput("Enter center x: ");
            shape->y1 = getInput("Enter center y: ");
            shape->radius = getInput("Enter radius: ");
            break;
        case SHAPE_LINE:
            shape->x1 = getInput("Enter x1: ");
            shape->y1 = getInput("Enter y1: ");
            shape->x2 = getInput("Enter x2: ");
            shape->y2 = getInput("Enter y2: ");
            break;
        case SHAPE_TRIANGLE:
            shape->x1 = getInput("Enter x1: ");
            shape->y1 = getInput("Enter y1: ");
            shape->x2 = getInput("Enter x2: ");
            shape->y2 = getInput("Enter y2: ");
            shape->x3 = getInput("Enter x3: ");
            shape->y3 = getInput("Enter y3: ");
            break;
        default:
            break;
    }
}

// Add a new shape to the drawing
void addShape(void) {
    if (shapeCount >= MAX_OBJECTS) {
        printf("Maximum object count reached.\n");
        return;
    }
    printf("Select object type:\n");
    printf("  1. Rectangle\n");
    printf("  2. Circle\n");
    printf("  3. Line\n");
    printf("  4. Triangle\n");
    int choice = getInput("Enter choice: ");
    
    if (choice < 1 || choice > 4) {
        printf("Invalid type. Object was not added.\n");
        return;
    }

    Shape shape = {0};
    static const ShapeType types[] = {SHAPE_RECTANGLE, SHAPE_CIRCLE, SHAPE_LINE, SHAPE_TRIANGLE};
    shape.type = types[choice - 1];
    
    inputShapeParameters(&shape);
    shapes[shapeCount++] = shape;
    printf("Object added.\n");
}

// Delete a shape from the drawing
void removeShape(void) {
    if (shapeCount == 0) {
        printf("No objects to delete.\n");
        return;
    }
    showAllShapes();
    int index = getInput("Enter object number to delete: ") - 1;
    if (index < 0 || index >= shapeCount) {
        printf("Invalid object number.\n");
        return;
    }
    // Shift remaining shapes down
    for (int i = index; i < shapeCount - 1; i++)
        shapes[i] = shapes[i + 1];
    shapeCount--;
    printf("Object deleted.\n");
}

// Change a shape's coordinates
void editShape(void) {
    if (shapeCount == 0) {
        printf("No objects to modify.\n");
        return;
    }
    showAllShapes();
    int index = getInput("Enter object number to modify: ") - 1;
    if (index < 0 || index >= shapeCount) {
        printf("Invalid object number.\n");
        return;
    }
    inputShapeParameters(&shapes[index]);
    printf("Object modified.\n");
}

// Show the main menu
void displayMenu(void) {
    printf("\n2D Graphics Editor\n");
    printf("1. Display picture\n");
    printf("2. Add object\n");
    printf("3. Delete object\n");
    printf("4. Modify object\n");
    printf("5. List objects\n");
    printf("6. Clear all objects\n");
    printf("7. Exit\n");
}

// Main program loop
int main(void) {
    initializeDrawing();
    while (1) {
        displayMenu();
        int choice = getInput("Enter option: ");
        // Handle user's menu choice
        switch (choice) {
            case 1:
                showDrawing();
                break;
            case 2:
                addShape();
                break;
            case 3:
                removeShape();
                break;
            case 4:
                editShape();
                break;
            case 5:
                showAllShapes();
                break;
            case 6:
                shapeCount = 0;
                initializeDrawing();
                printf("All objects cleared.\n");
                break;
            case 7:
                printf("Exiting editor.\n");
                return 0;
            default:
                printf("Invalid option. Please choose 1-7.\n");
        }
    }
    return 0;
}
