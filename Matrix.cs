using System.CodeDom.Compiler;
using System.Collections.Generic;
using System.Collections;
using System.ComponentModel;
using System.Diagnostics.CodeAnalysis;
using System.Globalization;
using System.IO;
using System.Linq;
using System.Reflection;
using System.Runtime.Serialization;
using System.Text.RegularExpressions;
using System.Text;
using System;

class Result
{

    /*
     * Complete the 'minTime' function below.
     *
     * The function is expected to return an INTEGER.
     * The function accepts following parameters:
     *  1. 2D_INTEGER_ARRAY roads
     *  2. INTEGER_ARRAY machines
     */

    public static int Dfs(int current, int parent, List<List<Tuple<int, int>>> graph, HashSet<int> machines, ref int result)
        int dfs(int current, int parent, const Vector<Vector<Pair<int, int>>>& graph, const unordered_set<int>& machines, int& result)
        int dfs(int current, int parent, const vector<vector<pair<int, int>>>& graph, const unordered_set<int>& machines, int& result)
{
    {
        List<int> values = new List<int>();

        foreach (var neighbor in graph[current])
        {
            int next = neighbor.Item1;
            int weight = neighbor.Item2;
            if (next == parent) continue;

            int temp = Dfs(next, current, graph, machines, ref result);
            if (temp > 0)
            {
                values.Add(Math.Min(temp, weight));
            }
        }

        if (!machines.Contains(current))
        {
            if (!values.Any()) return -1;
            if (values.Count == 1) return values[0];

            values.Sort();

            for (int i = 0; i < values.Count - 1; i++)
            {
                result += values[i];
            }

            return values.Last();
        }
        else
        {
            foreach (var value in values)
            {
                result += value;
            }

            return int.MaxValue;
        }
    }

    public static int minTime(List<List<int>> roads, List<int> machines)
    {
        int n = roads.Count + 1;
        int result = 0;

        HashSet<int> machinesSet = new HashSet<int>(machines);
        List<List<Tuple<int, int>>> graph = new List<List<Tuple<int, int>>>(new List<Tuple<int, int>>[n]);

        for (int i = 0; i < n; i++)
        {
            graph[i] = new List<Tuple<int, int>>();
        }

        foreach (var road in roads)
        {
            int a = road[0];
            int b = road[1];
            int d = road[2];
            graph[a].Add(new Tuple<int, int>(b, d));
            graph[b].Add(new Tuple<int, int>(a, d));
        }

        Dfs(0, -1, graph, machinesSet, ref result);

        return result;
    }
}


class Solution
{
    public static void Main(string[] args)
    {
        TextWriter textWriter = new StreamWriter(@System.Environment.GetEnvironmentVariable("OUTPUT_PATH"), true);

        string[] firstMultipleInput = Console.ReadLine().TrimEnd().Split(' ');

        int n = Convert.ToInt32(firstMultipleInput[0]);

        int k = Convert.ToInt32(firstMultipleInput[1]);

        List<List<int>> roads = new List<List<int>>();

        for (int i = 0; i < n - 1; i++)
        {
            roads.Add(Console.ReadLine().TrimEnd().Split(' ').ToList().Select(roadsTemp => Convert.ToInt32(roadsTemp)).ToList());
        }

        List<int> machines = new List<int>();

        for (int i = 0; i < k; i++)
        {
            int machinesItem = Convert.ToInt32(Console.ReadLine().Trim());
            machines.Add(machinesItem);
        }

        int result = Result.minTime(roads, machines);

        textWriter.WriteLine(result);

        textWriter.Flush();
        textWriter.Close();
    }
}
