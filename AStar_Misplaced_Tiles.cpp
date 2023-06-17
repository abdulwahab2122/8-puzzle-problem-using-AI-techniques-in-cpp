#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

struct Node
{
    vector<vector<int>> state;
    int g;
    int h;
    int f;
    Node* parent;
};

struct Compare
{
    bool operator()(Node* a, Node* b)
    {
        return a->f > b->f;
    }
};

int findMisplacedTiles(vector<vector<int>> state, vector<vector<int>> goal)
{
    int count = 0;
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (state[i][j] != goal[i][j])
            {
                count++;
            }
        }
    }
    return count;
}

void printState(vector<vector<int>> state)
{
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            cout << state[i][j] << " ";
        }
        cout << endl;
    }
}

void printPath(Node* node)
{
    if (node == NULL)
    {
        return;
    }
    printPath(node->parent);
    printState(node->state);
    cout << endl;
}

void aStarMisplacedTiles(vector<vector<int>> start, vector<vector<int>> goal)
{
    priority_queue<Node*, vector<Node*>, Compare> pq;
    Node* root = new Node;
    root->state = start;
    root->g = 0;
    root->h = findMisplacedTiles(start, goal);
    root->f = root->g + root->h;
    root->parent = NULL;
    pq.push(root);
    while (!pq.empty())
    {
        Node* node = pq.top();
        pq.pop();
        if (node->state == goal)
        {
            printPath(node);
            return;
        }
        int x, y;
        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                if (node->state[i][j] == 0)
                {
                    x = i;
                    y = j;
                    break;
                }
            }
        }
        int dx[] = { 0, 0, 1, -1 };
        int dy[] = { 1, -1, 0, 0 };
        for (int i = 0; i < 4; i++)
        {
            int newx = x + dx[i];
            int newy = y + dy[i];
            if (newx >= 0 && newx < 3 && newy >= 0 && newy < 3)
            {
                Node* child = new Node;
                child->state = node->state;
                swap(child->state[x][y], child->state[newx][newy]);
                child->g = node->g + 1;
                child->h = findMisplacedTiles(child->state, goal);
                child->f = child->g + child->h;
                child->parent = node;
                pq.push(child);
            }
        }
    }
}

int main()
{
    vector<vector<int>> start = { {1, 2, 3}, {5, 6, 0}, {7, 8, 4} };
    vector<vector<int>> goal = { {1, 2, 3}, {5, 8, 6}, {0, 7, 4} };
    aStarMisplacedTiles(start, goal);
    return 0;
}


