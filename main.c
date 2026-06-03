#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#define WIDTH 60
#define HEIGHT 24
#define MAX_OBJECTS 100

typedef enum {
    OBJ_RECTANGLE,
    OBJ_CIRCLE,
    OBJ_LINE,
    OBJ_TRIANGLE,
    OBJ_NONE
} ObjectType;

typedef struct {
    ObjectType type;
    int x1, y1, x2, y2, x3, y3;
    int radius;
} Shape;

static char canvas[HEIGHT][WIDTH];
static Shape objects[MAX_OBJECTS];
static int objectCount = 0;

void clearCanvas(void) {
    for (int y = 0; y < HEIGHT; y++)
        for (int x = 0; x < WIDTH; x++)
            canvas[y][x] = '_';
}

void paintPixel(int x, int y) {
    if (x >= 0 && x < WIDTH && y >= 0 && y < HEIGHT) {
        canvas[y][x] = '*';
    }
}

void drawLineOnCanvas(int x1, int y1, int x2, int y2) {
    int dx = abs(x2 - x1);
    int dy = abs(y2 - y1);
    int sx = x1 < x2 ? 1 : -1;
    int sy = y1 < y2 ? 1 : -1;
    int err = dx - dy;

    while (1) {
        paintPixel(x1, y1);
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

void drawRectangleOnCanvas(int x1, int y1, int x2, int y2) {
    int left = x1 < x2 ? x1 : x2, right = x1 < x2 ? x2 : x1;
    int top = y1 < y2 ? y1 : y2, bottom = y1 < y2 ? y2 : y1;

    for (int x = left; x <= right; x++) {
        paintPixel(x, top);
        paintPixel(x, bottom);
    }
    for (int y = top; y <= bottom; y++) {
        paintPixel(left, y);
        paintPixel(right, y);
    }
}

void drawCircleOnCanvas(int cx, int cy, int radius) {
    int x = 0;
    int y = radius;
    int d = 3 - 2 * radius;

    while (x <= y) {
        paintPixel(cx + x, cy + y);
        paintPixel(cx - x, cy + y);
        paintPixel(cx + x, cy - y);
        paintPixel(cx - x, cy - y);
        paintPixel(cx + y, cy + x);
        paintPixel(cx - y, cy + x);
        paintPixel(cx + y, cy - x);
        paintPixel(cx - y, cy - x);

        if (d <= 0) {
            d += 4 * x + 6;
        } else {
            d += 4 * (x - y) + 10;
            y--;
        }
        x++;
    }
}

void drawTriangleOnCanvas(int x1, int y1, int x2, int y2, int x3, int y3) {
    drawLineOnCanvas(x1, y1, x2, y2);
    drawLineOnCanvas(x2, y2, x3, y3);
    drawLineOnCanvas(x3, y3, x1, y1);
}

void redrawCanvas(void) {
    clearCanvas();
    for (int i = 0; i < objectCount; i++) {
        Shape *s = &objects[i];
        switch (s->type) {
            case OBJ_RECTANGLE:
                drawRectangleOnCanvas(s->x1, s->y1, s->x2, s->y2);
                break;
            case OBJ_CIRCLE:
                drawCircleOnCanvas(s->x1, s->y1, s->radius);
                break;
            case OBJ_LINE:
                drawLineOnCanvas(s->x1, s->y1, s->x2, s->y2);
                break;
            case OBJ_TRIANGLE:
                drawTriangleOnCanvas(s->x1, s->y1, s->x2, s->y2, s->x3, s->y3);
                break;
            default:
                break;
        }
    }
}

void displayCanvas(void) {
    redrawCanvas();
    printf("\n");
    for (int y = 0; y < HEIGHT; y++) {
        for (int x = 0; x < WIDTH; x++)
            putchar(canvas[y][x]);
        putchar('\n');
    }
}

void printObject(int index) {
    Shape *s = &objects[index];
    printf("[%d] ", index + 1);
    switch (s->type) {
        case OBJ_RECTANGLE:
            printf("Rectangle: (%d,%d) to (%d,%d)\n", s->x1, s->y1, s->x2, s->y2);
            break;
        case OBJ_CIRCLE:
            printf("Circle: center (%d,%d), radius %d\n", s->x1, s->y1, s->radius);
            break;
        case OBJ_LINE:
            printf("Line: (%d,%d) to (%d,%d)\n", s->x1, s->y1, s->x2, s->y2);
            break;
        case OBJ_TRIANGLE:
            printf("Triangle: (%d,%d), (%d,%d), (%d,%d)\n", s->x1, s->y1, s->x2, s->y2, s->x3, s->y3);
            break;
        default:
            printf("Unknown object\n");
            break;
    }
}

void listObjects(void) {
    if (objectCount == 0) {
        printf("No objects in the picture.\n");
        return;
    }
    for (int i = 0; i < objectCount; i++) {
        printObject(i);
    }
}

int readInt(const char *prompt) {
    int value;
    printf("%s", prompt);
    while (scanf("%d", &value) != 1) {
        while (getchar() != '\n');
        printf("Invalid input. %s", prompt);
    }
    while (getchar() != '\n');
    return value;
}

void readShapeParams(Shape *shape) {
    switch (shape->type) {
        case OBJ_RECTANGLE:
            shape->x1 = readInt("Enter x1: ");
            shape->y1 = readInt("Enter y1: ");
            shape->x2 = readInt("Enter x2: ");
            shape->y2 = readInt("Enter y2: ");
            break;
        case OBJ_CIRCLE:
            shape->x1 = readInt("Enter center x: ");
            shape->y1 = readInt("Enter center y: ");
            shape->radius = readInt("Enter radius: ");
            break;
        case OBJ_LINE:
            shape->x1 = readInt("Enter x1: ");
            shape->y1 = readInt("Enter y1: ");
            shape->x2 = readInt("Enter x2: ");
            shape->y2 = readInt("Enter y2: ");
            break;
        case OBJ_TRIANGLE:
            shape->x1 = readInt("Enter x1: ");
            shape->y1 = readInt("Enter y1: ");
            shape->x2 = readInt("Enter x2: ");
            shape->y2 = readInt("Enter y2: ");
            shape->x3 = readInt("Enter x3: ");
            shape->y3 = readInt("Enter y3: ");
            break;
        default:
            break;
    }
}

void addObject(void) {
    if (objectCount >= MAX_OBJECTS) {
        printf("Maximum object count reached.\n");
        return;
    }
    printf("Select object type:\n");
    printf("  1. Rectangle\n");
    printf("  2. Circle\n");
    printf("  3. Line\n");
    printf("  4. Triangle\n");
    int choice = readInt("Enter choice: ");
    
    if (choice < 1 || choice > 4) {
        printf("Invalid type. Object was not added.\n");
        return;
    }

    Shape shape = {0};
    static const ObjectType types[] = {OBJ_RECTANGLE, OBJ_CIRCLE, OBJ_LINE, OBJ_TRIANGLE};
    shape.type = types[choice - 1];
    
    readShapeParams(&shape);
    objects[objectCount++] = shape;
    printf("Object added.\n");
}

void deleteObject(void) {
    if (objectCount == 0) {
        printf("No objects to delete.\n");
        return;
    }
    listObjects();
    int index = readInt("Enter object number to delete: ") - 1;
    if (index < 0 || index >= objectCount) {
        printf("Invalid object number.\n");
        return;
    }
    for (int i = index; i < objectCount - 1; i++) {
        objects[i] = objects[i + 1];
    }
    objectCount--;
    printf("Object deleted.\n");
}

void modifyObject(void) {
    if (objectCount == 0) {
        printf("No objects to modify.\n");
        return;
    }
    listObjects();
    int index = readInt("Enter object number to modify: ") - 1;
    if (index < 0 || index >= objectCount) {
        printf("Invalid object number.\n");
        return;
    }
    readShapeParams(&objects[index]);
    printf("Object modified.\n");
}

void showMenu(void) {
    printf("\n2D Graphics Editor\n");
    printf("1. Display picture\n");
    printf("2. Add object\n");
    printf("3. Delete object\n");
    printf("4. Modify object\n");
    printf("5. List objects\n");
    printf("6. Clear all objects\n");
    printf("7. Exit\n");
}

int main(void) {
    clearCanvas();
    while (1) {
        showMenu();
        int choice = readInt("Enter option: ");
        switch (choice) {
            case 1:
                displayCanvas();
                break;
            case 2:
                addObject();
                break;
            case 3:
                deleteObject();
                break;
            case 4:
                modifyObject();
                break;
            case 5:
                listObjects();
                break;
            case 6:
                objectCount = 0;
                clearCanvas();
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
