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
// Manhattan Distance
int manhattan(vector<int> state, vector<int> goal)
{
    int sum = 0;
    for (int i = 0; i < state.size(); i++)
    {
        if (state[i] != 0)
        {
            int x1 = i / 3;
            int y1 = i % 3;
            int x2 = find(goal.begin(), goal.end(), state[i]) - goal.begin();
            x2 /= 3;
            int y2 = find(goal.begin(), goal.end(), state[i]) - goal.begin();
            y2 %= 3;
            sum += abs(x1 - x2) + abs(y1 - y2);
        }
    }
    return sum;
}

int findCost(vector<int> state, vector<int> goal)
{
    return manhattan(state, goal);
}

void printPath(vector<node> tree, int goal)
{
    if (tree[goal].parent == -1)
    {
        cout << "Initial State" << endl;
        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                cout << tree[goal].state[i * 3 + j] << " ";
            }
            cout << endl;
        }
        return;
    }
    printPath(tree, tree[goal].parent);
    cout << "Level " << tree[goal].level << endl;
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            cout << tree[goal].state[i * 3 + j] << " ";
        }
        cout << endl;
    }
}

bool isVisited(vector<node> tree, vector<int> state)
{
    for (int i = 0; i < tree.size(); i++)
    {
        if (tree[i].state == state)
            return true;
    }
    return false;
}

void expandNode(vector<node>& tree, node& n, vector<int> goal)
{
    int x = n.blank / 3;
    int y = n.blank % 3;
    int dx[] = { 0, 0, 1, -1 };
    int dy[] = { 1, -1, 0, 0 };
    for (int i = 0; i < 4; i++)
    {
        int x1 = x + dx[i];
        int y1 = y + dy[i];
        if (x1 >= 0 && x1 < 3 && y1 >= 0 && y1 < 3)
        {
            node m;
            m.state = n.state;
            m.blank = x1 * 3 + y1;
            m.level = n.level + 1;
            m.parent = tree.size() - 1;
            swap(m.state[m.blank], m.state[n.blank]);
            m.cost = findCost(m.state, goal);
            if (!isVisited(tree, m.state))
                tree.push_back(m);
        }
    }
}

void solve(vector<int> initial, vector<int> goal)
{
    priority_queue<node, vector<node>, compare> pq;
    vector<node> tree;
    node n;
    n.state = initial;
    n.cost = findCost(initial, goal);
    n.level = 0;
    n.parent = -1;
    n.blank = findBlank(initial);
    tree.push_back(n);
    pq.push(n);
    while (!pq.empty())
    {
        node n = pq.top();
        pq.pop();
        if (n.state == goal)
        {
            cout << "Goal State" << endl;
            for (int i = 0; i < 3; i++)
            {
                for (int j = 0; j < 3; j++)
                {
                    cout << n.state[i * 3 + j] << " ";
                }
                cout << endl;
            }
            cout << "Cost: " << n.cost << endl;
            cout << "Level: " << n.level << endl;
            cout << "Path: " << endl;
            printPath(tree, tree.size() - 1);
            return;
        }
        expandNode(tree, n, goal);
        for (int i = tree.size() - 4; i < tree.size(); i++)
        {
            pq.push(tree[i]);
        }
    }
}

int main()
{
    vector<int> initial = { 1, 2, 3, 5, 6, 0, 7, 8, 4 };
    vector<int> goal = { 1, 2, 3, 5, 8, 6, 0, 7, 4 };
    solve(initial, goal);
    return 0;
}
