#include <iostream>
#include <queue>
#include <vector>
using namespace std;

#define N 3

struct node
{
    node* parent;
    int mat[N][N];
    int x, y;
    int cost;
    int level;
};

int calculateCost(int initial[N][N], int final[N][N])
{
    int count = 0;
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            if (initial[i][j] != final[i][j])
                count++;
    return count;
}

node* newNode(int mat[N][N], int x, int y, int newX,
    int newY, int level, node* parent)
{
    node* node = new struct node;
    node->parent = parent;
    memcpy(node->mat, mat, sizeof node->mat);       // // Copy the state of the puzzle from the parent node to the current node
    swap(node->mat[x][y], node->mat[newX][newY]);   // // Swap the blank space with the tile
    node->cost = INT_MAX;
    node->level = level;
    node->x = newX;
    node->y = newY;
    return node;
}

struct comp
{
    bool operator()(const node* lhs, const node* rhs) const
    {
        return (lhs->cost + lhs->level) > (rhs->cost + rhs->level);
    }
};

void printMatrix(int mat[N][N])
{
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
            printf("%d ", mat[i][j]);
        printf("\n");
    }
}

void printPath(node* root)
{
    if (root == NULL)
        return;
    printPath(root->parent);
    printMatrix(root->mat);

    printf("\n");
}

void solve(int initial[N][N], int x, int y,int final[N][N])
{
    priority_queue<node*, std::vector<node*>, comp> pq;

    node* root = newNode(initial, x, y, x, y, 0, NULL);
    root->cost = calculateCost(initial, final);
    pq.push(root);

    while (!pq.empty())
    {
        node* min = pq.top();

        pq.pop();

        if (min->cost == 0)
        {
            printPath(min);
            return;
        }

        int x = min->x;
        int y = min->y;

        if (x > 0)      // Move Up
        {
            node* child = newNode(min->mat, x, y, x - 1, y,
                min->level + 1, min);
            child->cost = calculateCost(child->mat, final);
            pq.push(child);
        }

        if (x < N - 1)      // Move Down
        {
            node* child = newNode(min->mat, x, y, x + 1, y,
                min->level + 1, min);
            child->cost = calculateCost(child->mat, final);
            pq.push(child);
        }

        if (y > 0)      // Move Left
        {
            node* child = newNode(min->mat, x, y, x, y - 1,
                min->level + 1, min);
            child->cost = calculateCost(child->mat, final);
            pq.push(child);
        }

        if (y < N - 1)          // Move Right
        {
            node* child = newNode(min->mat, x, y, x, y + 1,
                min->level + 1, min);
            child->cost = calculateCost(child->mat, final);
            pq.push(child);
        }
    }
}

int main()
{
    int initial[N][N] =
    {
        {1, 2, 3},
        {5, 6, 0},
        {7, 8, 4}
    };

    int final[N][N] =
    {
        {1, 2, 3},
        {5, 8, 6},
        {0, 7, 4}
    };

    int x = 1, y = 2;       // Position of blank space in initial state

    solve(initial, x, y, final);

    return 0;
}