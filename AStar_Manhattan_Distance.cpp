#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

struct Node
{
    vector<vector<int>> state;
    int g;              // cost of the path from the initial state to the current state
    int h;              // heuristic function
    int f;              // f(n) = g(n) + h(n)
    Node* parent;
};

struct Compare
{
    bool operator()(Node* a, Node* b)
    {
        return a->f > b->f;
    }
};

int findManhattanDistance(vector<vector<int>> state, vector<vector<int>> goal)
{
    int count = 0;
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (state[i][j] != goal[i][j])
            {
                for (int k = 0; k < 3; k++)
                {
                    for (int l = 0; l < 3; l++)
                    {
                        if (state[i][j] == goal[k][l])
                        {
                            count += abs(i - k) + abs(j - l);
                        }
                    }
                }
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

int main()
{
    vector<vector<int>> start = { {1, 2, 3}, {5, 6, 0}, {7, 8, 4} };
    vector<vector<int>> goal = { {1, 2, 3}, {5, 8, 6}, {0, 7, 4} };

    Node* root = new Node;
    root->state = start;
    root->g = 0;            
    root->h = findManhattanDistance(start, goal);       
    root->f = root->g + root->h;        
    root->parent = NULL;

    priority_queue<Node*, vector<Node*>, Compare> pq;
    pq.push(root);

    while (!pq.empty())
    {
        Node* current = pq.top();
        pq.pop();

        if (current->state == goal)
        {
            printPath(current);
            break;
        }

        int x, y;
        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                if (current->state[i][j] == 0)
                {
                    x = i;
                    y = j;
                }
            }
        }

        vector<vector<int>> moves = { {x - 1, y}, {x + 1, y}, {x, y - 1}, {x, y + 1} }; // possible moves
        for (int i = 0; i < moves.size(); i++)
        {
            if (moves[i][0] >= 0 && moves[i][0] < 3 && moves[i][1] >= 0 && moves[i][1] < 3) // check if move is valid
            {
                Node* child = new Node;
                child->state = current->state;
                swap(child->state[x][y], child->state[moves[i][0]][moves[i][1]]);
                child->g = current->g + 1;
                child->h = findManhattanDistance(child->state, goal);
                child->f = child->g + child->h;
                child->parent = current;
                pq.push(child);
            }
        }
    }
    return 0;
}