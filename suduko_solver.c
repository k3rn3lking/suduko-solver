#include <gtk/gtk.h>
#include <stdbool.h>

#define N 9
#define UNASSIGNED 0

GtkWidget *entries[N][N];

// Function to check if a number can be placed in the given position
bool isSafe(int grid[N][N], int row, int col, int num) {
    // Check if the number is already present in that row or column
    for (int x = 0; x < N; x++)
        if (grid[row][x] == num || grid[x][col] == num)
            return false;

    // Check if the number is already present in the 3x3 grid
    int startRow = row - row % 3;
    int startCol = col - col % 3;
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            if (grid[i + startRow][j + startCol] == num)
                return false;

    return true;
}

// Function to solve the Sudoku puzzle
bool solveSudoku(int grid[N][N]) {
    int row, col;

    // Check for unassigned positions
    bool found = false;
    for (row = 0; row < N; row++) {
        for (col = 0; col < N; col++) {
            if (grid[row][col] == UNASSIGNED) {
                found = true;
                break;
            }
        }
        if (found)
            break;
    }

    // If no unassigned position is found, puzzle solved
    if (!found)
        return true;

    // Try assigning numbers from 1 to 9
    for (int num = 1; num <= 9; num++) {
        if (isSafe(grid, row, col, num)) {
            grid[row][col] = num;

            // Recur to solve the rest of the puzzle
            if (solveSudoku(grid))
                return true;

            // If no solution found, backtrack
            grid[row][col] = UNASSIGNED;
        }
    }

    // Trigger backtracking
    return false;
}

void solve_sudoku(GtkWidget *widget, gpointer data) {
    int grid[N][N];

    // Read values from text entry fields
    for (int row = 0; row < N; row++) {
        for (int col = 0; col < N; col++) {
            const gchar *entry_text = gtk_entry_get_text(GTK_ENTRY(entries[row][col]));
            if (strcmp(entry_text, "") == 0) {
                grid[row][col] = 0;
            } else {
                grid[row][col] = atoi(entry_text);
            }
        }
    }

    // Solve the Sudoku puzzle
    if (solveSudoku(grid)) {
        // Display the solved puzzle
        for (int row = 0; row < N; row++) {
            for (int col = 0; col < N; col++) {
                gchar text[2];
                if (grid[row][col] != UNASSIGNED)
                    sprintf(text, "%d", grid[row][col]);
                else
                    strcpy(text, "");
                gtk_entry_set_text(GTK_ENTRY(entries[row][col]), text);
            }
        }
    } else {
        GtkWidget *dialog = gtk_message_dialog_new(NULL, GTK_DIALOG_MODAL, GTK_MESSAGE_ERROR, GTK_BUTTONS_CLOSE, "No solution exists.");
        gtk_dialog_run(GTK_DIALOG(dialog));
        gtk_widget_destroy(dialog);
    }
}

void activate(GtkApplication *app, gpointer user_data) {
    GtkWidget *window;
    GtkWidget *grid;
    GtkWidget *entry;
    GtkWidget *solve_button;

    window = gtk_application_window_new(app);
    gtk_window_set_title(GTK_WINDOW(window), "Sudoku Solver");
    gtk_window_set_default_size(GTK_WINDOW(window), 400, 400);

    grid = gtk_grid_new();
    gtk_container_add(GTK_CONTAINER(window), grid);

    for (int row = 0; row < N; row++) {
        for (int col = 0; col < N; col++) {
            entry = gtk_entry_new();
            gtk_entry_set_max_length(GTK_ENTRY(entry), 1);
            gtk_entry_set_width_chars(GTK_ENTRY(entry), 3);
            gtk_grid_attach(GTK_GRID(grid), entry, col, row, 1, 1);
            entries[row][col] = entry;
        }
    }

    solve_button = gtk_button_new_with_label("Solve");
    g_signal_connect(solve_button, "clicked", G_CALLBACK(solve_sudoku), NULL);
    gtk_grid_attach(GTK_GRID(grid), solve_button, 0, N, N, 1);

    gtk_widget_show_all(window);
}

int main(int argc, char **argv) {
    GtkApplication *app;
    int status;

    app = gtk_application_new("org.gtk.sudoku_solver", G_APPLICATION_DEFAULT_FLAGS);
    g_signal_connect(app, "activate", G_CALLBACK(activate), NULL);
    status = g_application_run(G_APPLICATION(app), argc, argv);
    g_object_unref(app);

    return status;
}

