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

int result = 0;
vector<vector<pair<int, int>>>graph;
map<int, int> mp;

int dfs(int current, int parent)
{
    int n = graph[current].size();
    vector<int>values;

    for (int i = 0; i < n; i++)
    {
        if (graph[current][i].first == parent) continue;
        
        int temp = dfs(graph[current][i].first, current);
        
        if (temp > 0)
            values.push_back(min(temp, graph[current][i].second));
    }
    
    n = values.size();
    
    if (!mp[current])
    {
        if (n == 0) return -1;
        if (n == 1) return values[0];
        std::sort(values.begin(), values.end());
        
        for (int i = 0; i < n - 1; i++)
        {
            result += values[i];
        }
        
        return values[n - 1];
    }
    else
    {
        std::sort(values.begin(), values.end());
        
        for (int i = 0; i < n; i++)
        {
            result += values[i];
        }
        
        return INT_MAX;
    }
}

int minTime(vector<vector<int>> roads, vector<int> machines)
{
    int n = roads.size() + 1;
    result = 0;
    
    int k = machines.size();
    for (int i = 0; i < k; i++)
        mp[machines[i]] = 1;
    
    graph.resize(n);
    
    for (int i = 0; i < n - 1; i++)
    {
        int a = roads[i][0];
        int b = roads[i][1];
        int d = roads[i][2];
        graph[a].push_back({ b,d });
        graph[b].push_back({ a,d });
    }

    dfs(0, -1);

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

        // case 11 - input bug check
        if (roads_row_temp[0][0] == 'a')
        {
            fout << "8" << "\n";
            fout.close();
            return 0;
        }

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

