#include <iostream>
#include <vector>
#include <string>
#include <cmath>
#include <unordered_set>
#include <climits>

using namespace std;

const int N = 3;
const vector<pair<int, int>> directions = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
const vector<char> dir_letters = {'D', 'U', 'R', 'L'};

struct Puzzle {
    vector<vector<int>> board;
    int x, y; // position of 0 
    int g; // cost so far
    string path;

    Puzzle(vector<vector<int>> b, int g_cost, string p) : board(b), g(g_cost), path(p) {
        for (int i = 0; i < N; i++)
            for (int j = 0; j < N; j++)
                if (board[i][j] == 0) {
                    x = i; y = j;
                }
    }

    int heuristic() const {
        int dist = 0;
        for (int i = 0; i < N; i++)
            for (int j = 0; j < N; j++) {
                int val = board[i][j];
                if (val != 0) {
                    int tx = (val - 1) / N;
                    int ty = (val - 1) % N;
                    dist += abs(i - tx) + abs(j - ty);
                }
            }
        return dist;
    }

    bool is_goal() const {
        int cnt = 1;
        for (int i = 0; i < N; i++)
            for (int j = 0; j < N; j++) {
                if (i == N - 1 && j == N - 1)
                    return board[i][j] == 0;
                if (board[i][j] != cnt++) return false;
            }
        return true;
    }
};

int dfs(Puzzle& current, int f_limit, int& next_limit) {
    int f = current.g + current.heuristic();
    if (f > f_limit) {
        next_limit = min(next_limit, f);
        return -1; // prune
    }

    if (current.is_goal()) return 1;

    for (int d = 0; d < 4; ++d) {
        int nx = current.x + directions[d].first;
        int ny = current.y + directions[d].second;

        if (nx >= 0 && nx < N && ny >= 0 && ny < N) {
            auto new_board = current.board;
            swap(new_board[current.x][current.y], new_board[nx][ny]);
            Puzzle neighbor(new_board, current.g + 1, current.path + dir_letters[d]);

            int result = dfs(neighbor, f_limit, next_limit);
            if (result == 1) {
                current = neighbor; // propagate the successful path
                return 1;
            }
        }
    }

    return 0;
}

string ida_star(vector<vector<int>> start) {
    Puzzle root(start, 0, "");
    int f_limit = root.heuristic();

    while (true) {
        int next_limit = INT_MAX;
        Puzzle copy = root;
        int result = dfs(copy, f_limit, next_limit);

        if (result == 1) return copy.path;
        if (next_limit == INT_MAX) return "Unsolvable";

        f_limit = next_limit;
    }
}

int main() {
    vector<vector<int>> start = {
        {0, 2, 3},
        {4, 5, 6},
        {7, 1, 8}
    };

    string result = ida_star(start);

    if (result == "Unsolvable") {
        cout << "Puzzle is unsolvable." << endl;
    } else {
        cout << "Solved in " << result.size() << " moves." << endl;
        cout << "Path: " << result << endl;
    }

    return 0;
}
