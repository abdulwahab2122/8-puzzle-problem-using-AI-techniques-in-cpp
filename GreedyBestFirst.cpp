// Number of Misplaced Tiles

#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

struct node
{
    vector<int> state;
    int cost;
    int level;
    int blank;
    int parent;
};

struct compare
{
    bool operator()(const node& a, const node& b)
    {
        return a.cost > b.cost;
    }
};

int findBlank(vector<int> state)
{
    for (int i = 0; i < state.size(); i++)
    {
        if (state[i] == 0)
            return i;
    }
    return -1;
}
// Number of Misplaced Tiles
int misplacedTiles(vector<int> state, vector<int> goal)
{
    int cost = 0;
    for (int i = 0; i < state.size(); i++)
    {
        if (state[i] != goal[i])
            cost++;
    }
    return cost;
}

void printPath(vector<node> nodes, int goal)
{
    if (nodes[goal].parent == -1)
    {
        cout << "Initial State" << endl;
        return;
    }
    printPath(nodes, nodes[goal].parent);
    cout << "Level " << nodes[goal].level << endl;
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            cout << nodes[goal].state[i * 3 + j] << " ";
        }
        cout << endl;
    }
    cout << endl;
}

void solve(vector<int> initial, vector<int> goal)
{
    priority_queue<node, vector<node>, compare> pq;
    vector<node> nodes;
    node root;
    root.state = initial;
    root.cost = misplacedTiles(initial, goal);
    root.level = 0;
    root.blank = findBlank(initial);
    root.parent = -1;
    pq.push(root);
    nodes.push_back(root);
    while (!pq.empty())
    {
        node current = pq.top();
        pq.pop();
        if (current.cost == 0)
        {
            cout << "Solution Found" << endl;
            printPath(nodes, nodes.size() - 1);
            return;
        }
        int x = current.blank / 3;
        int y = current.blank % 3;
        int dx[] = { 1, -1, 0, 0 };
        int dy[] = { 0, 0, 1, -1 };
        for (int i = 0; i < 4; i++)
        {
            int newx = x + dx[i];
            int newy = y + dy[i];
            if (newx >= 0 && newx < 3 && newy >= 0 && newy < 3)
            {
                node child;
                child.state = current.state;
                swap(child.state[current.blank], child.state[newx * 3 + newy]);
                child.cost = misplacedTiles(child.state, goal);
                child.level = current.level + 1;
                child.blank = newx * 3 + newy;
                child.parent = nodes.size() - 1;
                pq.push(child);
                nodes.push_back(child);
            }
        }
    }
    cout << "No Solution" << endl;
}

int main()
{
    vector<int> initial;
    vector<int> goal;
    cout << "Enter Initial State" << endl;
    for (int i = 0; i < 9; i++)
    {
        int x;
        cin >> x;
        initial.push_back(x);
    }
    cout << "Enter Goal State" << endl;
    for (int i = 0; i < 9; i++)
    {
        int x;
        cin >> x;
        goal.push_back(x);
    }
    solve(initial, goal);
    return 0;
}