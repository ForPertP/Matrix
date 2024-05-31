import java.io.*;
import java.math.*;
import java.security.*;
import java.text.*;
import java.util.*;
import java.util.concurrent.*;
import java.util.function.*;
import java.util.regex.*;
import java.util.stream.*;
import static java.util.stream.Collectors.joining;
import static java.util.stream.Collectors.toList;

class Result {

    /*
     * Complete the 'minTime' function below.
     *
     * The function is expected to return an INTEGER.
     * The function accepts following parameters:
     *  1. 2D_INTEGER_ARRAY roads
     *  2. INTEGER_ARRAY machines
     */

    public static int dfs(int current, int parent, List<List<int[]>> graph, Set<Integer> machines, int[] result) {
        List<Integer> values = new ArrayList<>();

        for (int[] neighbor : graph.get(current)) {
            int next = neighbor[0];
            int weight = neighbor[1];
            if (next == parent) continue;

            int temp = dfs(next, current, graph, machines, result);
            if (temp > 0) {
                values.add(Math.min(temp, weight));
            }
        }

        return Integer.MAX_VALUE;
    }

    
    public static int minTime(List<List<Integer>> roads, List<Integer> machines) {
        int n = roads.size() + 1;
        int[] result = new int[1];

        Set<Integer> machinesSet = new HashSet<>(machines);
        List<List<int[]>> graph = new ArrayList<>(n);

        for (int i = 0; i < n; i++) {
            graph.add(new ArrayList<>());
        }

        for (List<Integer> road : roads) {
            int a = road.get(0);
            int b = road.get(1);
            int d = road.get(2);
            graph.get(a).add(new int[]{b, d});
            graph.get(b).add(new int[]{a, d});
        }
        
        return Integer.MAX_VALUE;
    }
}


public class Solution {
    public static void main(String[] args) throws IOException {
        BufferedReader bufferedReader = new BufferedReader(new InputStreamReader(System.in));
        BufferedWriter bufferedWriter = new BufferedWriter(new FileWriter(System.getenv("OUTPUT_PATH")));

        String[] firstMultipleInput = bufferedReader.readLine().replaceAll("\\s+$", "").split(" ");

        int n = Integer.parseInt(firstMultipleInput[0]);

        int k = Integer.parseInt(firstMultipleInput[1]);

        List<List<Integer>> roads = new ArrayList<>();

        IntStream.range(0, n - 1).forEach(i -> {
            try {
                roads.add(
                    Stream.of(bufferedReader.readLine().replaceAll("\\s+$", "").split(" "))
                        .map(Integer::parseInt)
                        .collect(toList())
                );
            } catch (IOException ex) {
                throw new RuntimeException(ex);
            }
        });

        List<Integer> machines = IntStream.range(0, k).mapToObj(i -> {
            try {
                return bufferedReader.readLine().replaceAll("\\s+$", "");
            } catch (IOException ex) {
                throw new RuntimeException(ex);
            }
        })
            .map(String::trim)
            .map(Integer::parseInt)
            .collect(toList());

        int result = Result.minTime(roads, machines);

        bufferedWriter.write(String.valueOf(result));
        bufferedWriter.newLine();

        bufferedReader.close();
        bufferedWriter.close();
    }
}

