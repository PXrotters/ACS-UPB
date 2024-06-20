#include "./utils.h"

// Functie pentru a actualiza pozitia unui avion
void update_position(int *current_x, int *current_y, unsigned char direction, int speed, int time_elapsed) {
    if (direction == 'N') {
        *current_x -= speed * time_elapsed;
    } else if (direction == 'S') {
        *current_x += speed * time_elapsed;
    } else if (direction == 'E') {
        *current_y += speed * time_elapsed;
    } else if (direction == 'W') {
        *current_y -= speed * time_elapsed;
    }
}

// Functie pentru a verifica daca avionul este distrus
int is_aircraft_destroyed(char **map_matrix, int map_size, int aircraft_x, int aircraft_y, unsigned char direction, unsigned char type) {
    int row = aircraft_x, col = aircraft_y, search = 1;

    if (type == '1') {
        if (direction == 'N') {
            if ((row >= 0) && map_matrix[row][aircraft_y] == '@') search = 0;
            row++;
            for (col = aircraft_y - 2; col <= aircraft_y + 2 && (row >= 0 && row < map_size && col >= 0 && col < map_size && search); col++)
                if (map_matrix[row][col] == '@') search = 0;
            row++;
            if ((row >= 0 && row < map_size && search) && map_matrix[row][aircraft_y] == '@') search = 0;
            row++;
            for (col = aircraft_y - 1; col <= aircraft_y + 1 && (row >= 0 && row < map_size && col >= 0 && col < map_size && search); col++)
                if (map_matrix[row][col] == '@') search = 0;
        } else if (direction == 'S') {
            if ((row < map_size) && map_matrix[row][aircraft_y] == '@') search = 0;
            row--;
            for (col = aircraft_y - 2; col <= aircraft_y + 2 && (row >= 0 && row < map_size && col >= 0 && col < map_size && search); col++)
                if (map_matrix[row][col] == '@') search = 0;
            row--;
            if ((row >= 0 && row < map_size && search) && map_matrix[row][aircraft_y] == '@') search = 0;
            row--;
            for (col = aircraft_y - 1; col <= aircraft_y + 1 && (row >= 0 && row < map_size && col >= 0 && col < map_size && search); col++)
                if (map_matrix[row][col] == '@') search = 0;
        } else if (direction == 'E') {
            if ((col < map_size) && map_matrix[aircraft_x][col] == '@') search = 0;
            col--;
            for (row = aircraft_x - 2; row <= aircraft_x + 2 && (row >= 0 && row < map_size && col >= 0 && col < map_size && search); row++)
                if (map_matrix[row][col] == '@') search = 0;
            col--;
            if ((col >= 0 && col < map_size && search) && map_matrix[aircraft_x][col] == '@') search = 0;
            col--;
            for (row = aircraft_x - 1; row <= aircraft_x + 1 && (row >= 0 && row < map_size && col >= 0 && col < map_size && search); row++)
                if (map_matrix[row][col] == '@') search = 0;
        } else if (direction == 'W') {
            if ((col >= 0) && map_matrix[aircraft_x][col] == '@') search = 0;
            col++;
            for (row = aircraft_x - 2; row <= aircraft_x + 2 && (row >= 0 && row < map_size && col >= 0 && col < map_size && search); row++)
                if (map_matrix[row][col] == '@') search = 0;
            col++;
            if ((col >= 0 && col < map_size && search) && map_matrix[aircraft_x][col] == '@') search = 0;
            col++;
            for (row = aircraft_x - 1; row <= aircraft_x + 1 && (row >= 0 && row < map_size && col >= 0 && col < map_size && search); row++)
                if (map_matrix[row][col] == '@') search = 0;
        }
    } else {
        if (direction == 'N') {
            if ((row >= 0) && map_matrix[row][aircraft_y] == '@') search = 0;
            row++;
            for (col = aircraft_y - 1; col <= aircraft_y + 1 && (row >= 0 && row < map_size && col >= 0 && col < map_size && search); col++)
                if (map_matrix[row][col] == '@') search = 0;
            row++;
            for (col = aircraft_y - 3; col <= aircraft_y + 3 && (row >= 0 && row < map_size && col >= 0 && col < map_size && search); col++)
                if (map_matrix[row][col] == '@') search = 0;
            row++;
            if ((row >= 0 && row < map_size && search) && map_matrix[row][aircraft_y] == '@') search = 0;
            row++;
            for (col = aircraft_y - 2; col <= aircraft_y + 2 && (row >= 0 && row < map_size && col >= 0 && col < map_size && search); col++)
                if (map_matrix[row][col] == '@') search = 0;
        } else if (direction == 'S') {
            if ((row < map_size) && map_matrix[row][aircraft_y] == '@') search = 0;
            row--;
            for (col = aircraft_y - 1; col <= aircraft_y + 1 && (row >= 0 && row < map_size && col >= 0 && col < map_size && search); col++)
                if (map_matrix[row][col] == '@') search = 0;
            row--;
            for (col = aircraft_y - 3; col <= aircraft_y + 3 && (row >= 0 && row < map_size && col >= 0 && col < map_size && search); col++)
                if (map_matrix[row][col] == '@') search = 0;
            row--;
            if ((row >= 0 && row < map_size && search) && map_matrix[row][aircraft_y] == '@') search = 0;
            row--;
            for (col = aircraft_y - 2; col <= aircraft_y + 2 && (row >= 0 && row < map_size && col >= 0 && col < map_size && search); col++)
                if (map_matrix[row][col] == '@') search = 0;
        } else if (direction == 'E') {
            if ((col < map_size) && map_matrix[aircraft_x][col] == '@') search = 0;
            col--;
            for (row = aircraft_x - 1; row <= aircraft_x + 1 && (row >= 0 && row < map_size && col >= 0 && col < map_size && search); row++)
                if (map_matrix[row][col] == '@') search = 0;
            col--;
            for (row = aircraft_x - 3; row <= aircraft_x + 3 && (row >= 0 && row < map_size && col >= 0 && col < map_size && search); row++)
                if (map_matrix[row][col] == '@') search = 0;
            col--;
            if ((col >= 0 && col < map_size && search) && map_matrix[aircraft_x][col] == '@') search = 0;
            col--;
            for (row = aircraft_x - 2; row <= aircraft_x + 2 && (row >= 0 && row < map_size && col >= 0 && col < map_size && search); row++)
                if (map_matrix[row][col] == '@') search = 0;
        } else if (direction == 'W') {
            if ((col >= 0) && map_matrix[aircraft_x][col] == '@') search = 0;
            col++;
            for (row = aircraft_x - 1; row <= aircraft_x + 1 && (row >= 0 && row < map_size && col >= 0 && col < map_size && search); row++)
                if (map_matrix[row][col] == '@') search = 0;
            col++;
            for (row = aircraft_x - 3; row <= aircraft_x + 3 && (row >= 0 && row < map_size && col >= 0 && col < map_size && search); row++)
                if (map_matrix[row][col] == '@') search = 0;
            col++;
            if ((col >= 0 && col < map_size && search) && map_matrix[aircraft_x][col] == '@') search = 0;
            col++;
            for (row = aircraft_x - 2; row <= aircraft_x + 2 && (row >= 0 && row < map_size && col >= 0 && col < map_size && search); row++)
                if (map_matrix[row][col] == '@') search = 0;
        }
    }
    return !search;
}

void SolveTask5(void *info, int nr_avioane, int T, int nr_pct_coord, int *X, int *Y, int N) {
    char **map_matrix = init_mat(N);
    for (int i = 0; i < nr_pct_coord; i++) {
        map_matrix[X[i]][Y[i]] = '@';
    }

    const int next = sizeof(unsigned int);
    for (int time_elapsed = 0; time_elapsed <= T; time_elapsed++) {
        void *idx = info;
        int count = 1, colapsed = 0;

        while (count <= nr_avioane) {
            int x = 0, y = 0, v = 0;
            unsigned char direction = 0, type = 0;

            x = *((unsigned short *)idx);
            idx += sizeof(unsigned short);
            y = *((unsigned short *)idx);
            idx += sizeof(unsigned short);
            direction = *((unsigned char *)idx);
            idx += sizeof(unsigned char);
            type = *((unsigned char *)idx);
            idx += 4 * sizeof(unsigned char);
            v = *((int *)idx);

            update_position(&x, &y, direction, v, time_elapsed);

            if (is_aircraft_destroyed(map_matrix, N, x, y, direction, type)) {
                colapsed++;
            }

            count++;
            idx += next;
        }
        printf("%i : %i\n", time_elapsed, colapsed);
    }

    free_mat(map_matrix, N);
}
