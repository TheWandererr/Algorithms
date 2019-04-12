import java.io.File;
import java.io.IOException;
import java.io.PrintStream;
import java.util.AbstractMap;
import java.util.ArrayDeque;
import java.util.Scanner;

public class Main {
    private static int rows;
    private static int columns;
    private static int[][] ciliendor;
    private static int parts;

    private static void fillRow(int index, String[] row) {
        for (int j = 0; j < columns; ++j) {
            ciliendor[index][j] = Integer.parseInt(row[j]);
        }
    }

    private static void run() {
        ArrayDeque<AbstractMap.SimpleEntry<Integer, Integer>> q = new ArrayDeque<>();
        AbstractMap.SimpleEntry<Integer, Integer> indexes;
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < columns; ++j) {
                if (ciliendor[i][j] == 0) {
                    parts++;
                    indexes = new AbstractMap.SimpleEntry<>(i, j);
                    q.addFirst(indexes);
                    while (!q.isEmpty()) {
                        indexes = q.getFirst();
                        q.removeFirst();
                        int ii = indexes.getKey();
                        int jj = indexes.getValue();
                        ciliendor[ii][jj] = 1;
                        if (jj > 0 && ciliendor[ii][jj - 1] == 0) {
                            indexes = new AbstractMap.SimpleEntry<>(ii, jj-1);
                            q.addFirst(indexes);
                        }
                        if (jj < columns - 1 && ciliendor[ii][jj+1] == 0) {
                            indexes = new AbstractMap.SimpleEntry<>(ii, jj+1);
                            q.addFirst(indexes);
                        }
                        if (ii > 0) {
                            if (ciliendor[ii-1][jj] == 0) {
                                indexes = new AbstractMap.SimpleEntry<>(ii-1, jj);
                                q.addFirst(indexes);
                            }
                        } else {
                            if (ciliendor[rows-1][jj] == 0) {
                                indexes = new AbstractMap.SimpleEntry<>(rows-1, jj);
                                q.addFirst(indexes);
                            }
                        }
                        if (ii < rows - 1) {
                            if (ciliendor[ii + 1][jj] == 0) {
                                indexes = new AbstractMap.SimpleEntry<>(ii + 1, jj);
                                q.addFirst(indexes);
                            }
                        }
                        else {
                            if (ciliendor[0][jj] == 0 ) {
                                indexes = new AbstractMap.SimpleEntry<>(0, jj);
                                q.addFirst(indexes);
                            }
                        }
                    }
                }
            }
        }
    }

    private static void writeAnswer() throws IOException {
        try(PrintStream ps = new PrintStream(new File("out.txt"))) {
            ps.print(parts);
        }
    }

    public static void main(String[] args) throws Exception {
        try (Scanner sc = new Scanner(new File("in.txt"))) {
            String line;
            int index = 0;
            String arr[];
            if (sc.hasNextLine()) {
                line = sc.nextLine();
                arr = line.split("[ ]+");
                rows = Integer.parseInt(arr[0]);
                columns = Integer.parseInt(arr[1]);
            }
            ciliendor = new int[rows][columns];
            while (sc.hasNextLine()) {
                line = sc.nextLine();
                arr = line.split("[ ]+");
                Main.fillRow(index, arr);
                index += 1;
            }
            run();
            writeAnswer();
        }
    }
}