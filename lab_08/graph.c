#include "graph.h"
#include <string.h>
#define COUNT_TESTS 10
unsigned long long get_time()
{
    struct timespec mt1;
    clock_gettime(CLOCK_REALTIME, &mt1);
    return 1000000 * mt1.tv_sec + mt1.tv_nsec / 1000;
}

int read_graph_from_file(graph_t *dst, const char *path_src)
{
    FILE *f;
    f = fopen(path_src, "r");
    if (!f)
        return 1;
    fscanf(f, "%zu", &(dst->size));
    for (size_t i = 0; i < dst->size; i++)
        for (size_t j = 0; j < dst->size; j++)
            fscanf(f, "%d", &(dst->matrix[i][j]));
    fclose(f);
    return 0;
}

void DFS(graph_t *a, bool visited[], int current) {
    visited[current] = true;
    for (size_t i = 0; i < a->size; i++)
        if (a->matrix[current][i] == 1 && !visited[i])
            DFS(a, visited, i);
}
int is_graph_connected(graph_t *a) {
    bool visited[a->size];
    for (size_t i = 0; i < a->size; i++)
        visited[i] = false;
    DFS(a, visited, 0);
    for (size_t i = 0; i < a->size; i++)
        if (!visited[i])
            return 0;
    return 1;
}
// +
void export_to_dot(FILE *f, const char *graph_name, graph_t *a)
{
    size_t print_vertex;
    fprintf(f, "digraph %s {\n", graph_name);

    for (size_t i = 0; i < a->size; i++)
    {
        print_vertex = 0;
        for (size_t j = 0; j < a->size; j++)
            if (a->matrix[i][j] != 0)
            {
                print_vertex = 1;
                fprintf(f, "%zu -> %zu;\n", i + 1, j + 1);
                // fprintf(f, "%zu -> %zu;\n", j + 1, i + 1);
            }
        if (!print_vertex)
            fprintf(f, "%zu;\n", i + 1);
    }
    fprintf(f, "}\n");
}
// -
int findMinVertex(int cost[], int visited[], int vertices)
{
    int minCost = 1000, minVertex = -1;
    int i;

    for (i = 0; i < vertices; i++)
    {
        if (visited[i] == 0 && cost[i] < minCost)
        {
            minCost = cost[i];
            minVertex = i;
        }
    }

    return minVertex;
}
// -
#define OST_FILE_DOT "./ost_graph.gv"
#define OST_FILE_PNG "./ost_graph.png"
void print_spanning_tree_dot(graph_t *a, int *parent)
{
    FILE *fp;
    fp = fopen(OST_FILE_DOT, "w");

    fprintf(fp, "graph G {\n");
    for (size_t i = 0; i < a->size; i++)
        for (size_t j = 0; j < a->size; j++)
            if (a->matrix[i][j] != 0 && parent[j] == (int) i)
                fprintf(fp, "%zu -- %zu;\n", i + 1, j + 1);
    fprintf(fp, "}\n");
    fclose(fp);
    if (system("dot -Tpng "OST_FILE_DOT" -o "OST_FILE_PNG))
        printf("Ошибка формирования файла "OST_FILE_DOT", перепроверьте данные\n");
}
// -
int minimum_spanning_tree(graph_t *g)
{
    if (g->size == 0)
        return 1;
    int parent[g->size];
    int cost[g->size];
    int visited[g->size];
    size_t i, j, count;
    int current_node;
    int minCost = 0;

    for (i = 0; i < g->size; i++)
    {
        cost[i] = 1000;
        visited[i] = 0;
    }

    parent[0] = -1;
    cost[0] = 0;

    for (count = 0; count < g->size - 1; count++)
    {
        current_node = findMinVertex(cost, visited, g->size);
        visited[current_node] = 1;

        for (j = 0; j < g->size; j++)
        {
            if (g->matrix[current_node][j] != 0 && visited[j] == 0 && g->matrix[current_node][j] < cost[j])
            {
                parent[j] = current_node;
                cost[j] = g->matrix[current_node][j];
            }
        }
    }

    for (i = 1; i < g->size; i++)
    {
        minCost += cost[i];
    }

    printf("Общая стоимость остовного дерева: %d\n", minCost);

    print_spanning_tree_dot(g, parent);
    return 0;
}

void matrix_graph_DFS(graph_t *graph, simple_path_t *cur_path_info, simple_path_t *max_path_info, int vertex)
{
    cur_path_info->visited[vertex] = true;
    cur_path_info->path[cur_path_info->size++] = vertex;

    if (cur_path_info->size > max_path_info->size)
        *max_path_info = *cur_path_info;

    for (size_t cur_vertex = 0; cur_vertex < graph->size; cur_vertex++)
        if (graph->matrix[vertex][cur_vertex] == 1 && !cur_path_info->visited[cur_vertex])
            matrix_graph_DFS(graph, cur_path_info, max_path_info, cur_vertex);

    cur_path_info->visited[vertex] = false;
    cur_path_info->size--;
}

void find_max_simple_path(graph_t *graph, simple_path_t *max_path_info)
{
    for (size_t cur_vertex = 0; cur_vertex < graph->size; ++cur_vertex)
    {
        simple_path_t cur_path_info = {NULL};
        matrix_graph_DFS(graph, &cur_path_info, max_path_info, cur_vertex);
    }
}

void print_path(simple_path_t *info)
{
    for (size_t i = 0; i < info->size; ++i)
    {
        printf("%d", info->path[i] + 1);
        if (i != info->size - 1)
            printf(" -> ");
    }
    printf("\n");
}


void table_efficiency(void)
{
    char file[100];
    graph_t a;
    simple_path_t info;
    unsigned long long start_time;
    unsigned long long finish_time;
    unsigned long long avg_time = 0;
    size_t len_table = 5 + 15 + 3;

    printf("Тестирование проведено %d раз\n", COUNT_TESTS);
    puts("Время указано в наносекундах, затраты памяти в байтах\n");
    puts("TIME");

    for (size_t i = 0; i < len_table; i++)
        printf("-");
    puts("");

    for (size_t i = 5; i <= 15; i += 5)
    {
        for (size_t j = 0; j < COUNT_TESTS; j ++)
        {
            sprintf(file, "./data/test_%zu.txt", i);
            // puts("$");
            read_graph_from_file(&a, file);

            start_time = get_time();
            find_max_simple_path(&a, &info);
            finish_time = get_time();

            avg_time += finish_time - start_time;
        }
        printf("|%5zu|%15llu|\n", i, avg_time / COUNT_TESTS);
    }

    for (size_t i = 0; i < len_table; i++)
        printf("-");
    puts("\n");

    puts("MEMORY");
    for (size_t i = 0; i < len_table; i++)
        printf("-");
    puts("");

    for (size_t i = 5; i <= 15; i += 5)
        printf("|%5zu|%15zu|\n", i, MAX_SIZE * MAX_SIZE * sizeof(int) + sizeof(size_t));

    for (size_t i = 0; i < len_table; i++)
        printf("-");
    puts("");
}
