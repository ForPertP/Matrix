#include <bits/stdc++.h>

using namespace std;

string ltrim(const string &);
string rtrim(const string &);
vector<string> split(const string &);

/*
 * Complete the 'minTime' function below.
 *
 * The function is expected to return an INTEGER.
 * The function accepts following parameters:
 *  1. 2D_INTEGER_ARRAY roads
 *  2. INTEGER_ARRAY machines
 */

int dfs(int current, int parent, const vector<vector<pair<int, int>>>& graph, const unordered_set<int>& machines, int& result)
{
    vector<int> values;

    for (const auto& neighbor : graph[current]) {
        int next = neighbor.first;
        int weight = neighbor.second;
        if (next == parent) continue;

        int temp = dfs(next, current, graph, machines, result);
        if (temp > 0) {
            values.push_back(min(temp, weight));
        }
    }

    if (machines.find(current) == machines.end()) {
        if (values.empty()) return -1;
        if (values.size() == 1) return values[0];

        std::sort(values.begin(), values.end());

        for (size_t i = 0; i < values.size() - 1; i++) {
            result += values[i];
        }

        return values.back();
    } else {
        for (const int& value : values) {
            result += value;
        }

        return INT_MAX;
    }
}


int minTime(const vector<vector<int>>& roads, const vector<int>& machines)
{
    int n = roads.size() + 1;
    int result = 0;

    unordered_set<int> machines_set(machines.begin(), machines.end());
    vector<vector<pair<int, int>>> graph(n);

    for (const auto& road : roads) {
        int a = road[0];
        int b = road[1];
        int d = road[2];
        graph[a].push_back({b, d});
        graph[b].push_back({a, d});
    }

    dfs(0, -1, graph, machines_set, result);

    return result;
}


int main()
{
    ofstream fout(getenv("OUTPUT_PATH"));

    string first_multiple_input_temp;
    getline(cin, first_multiple_input_temp);

    vector<string> first_multiple_input = split(rtrim(first_multiple_input_temp));

    int n = stoi(first_multiple_input[0]);

    int k = stoi(first_multiple_input[1]);

    vector<vector<int>> roads(n - 1);

    for (int i = 0; i < n - 1; i++) {
        roads[i].resize(3);

        string roads_row_temp_temp;
        getline(cin, roads_row_temp_temp);

        vector<string> roads_row_temp = split(rtrim(roads_row_temp_temp));

        for (int j = 0; j < 3; j++) {
            int roads_row_item = stoi(roads_row_temp[j]);

            roads[i][j] = roads_row_item;
        }
    }

    vector<int> machines(k);

    for (int i = 0; i < k; i++) {
        string machines_item_temp;
        getline(cin, machines_item_temp);

        int machines_item = stoi(ltrim(rtrim(machines_item_temp)));

        machines[i] = machines_item;
    }

    int result = minTime(roads, machines);

    fout << result << "\n";

    fout.close();

    return 0;
}

string ltrim(const string &str) {
    string s(str);

    s.erase(
        s.begin(),
        find_if(s.begin(), s.end(), not1(ptr_fun<int, int>(isspace)))
    );

    return s;
}

string rtrim(const string &str) {
    string s(str);

    s.erase(
        find_if(s.rbegin(), s.rend(), not1(ptr_fun<int, int>(isspace))).base(),
        s.end()
    );

    return s;
}

vector<string> split(const string &str) {
    vector<string> tokens;

    string::size_type start = 0;
    string::size_type end = 0;

    while ((end = str.find(" ", start)) != string::npos) {
        tokens.push_back(str.substr(start, end - start));

        start = end + 1;
    }

    tokens.push_back(str.substr(start));

    return tokens;
}
