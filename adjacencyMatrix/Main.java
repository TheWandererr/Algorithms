import java.io.File;
import java.io.PrintStream;
import java.util.Scanner;

public class Main {


    public static void main(String[] args) {

        try (Scanner sc = new Scanner(new File("input.txt"))) {
            String line;
            int n, m;
            String[] nums;
            if (sc.hasNextLine()) {
                line = sc.nextLine();
                nums = line.split("[ \n]");
                n = Integer.parseInt(nums[0]);
                m = Integer.parseInt(nums[1]);
            } else {
                return;
            }
            int[] start = new int[m];
            int[] end = new int[m];
            int i = 0;
            while (sc.hasNextLine()) {
                nums = sc.nextLine().split("[ \n]");
                start[i] = Integer.parseInt(nums[0]) - 1;
                end[i] = Integer.parseInt(nums[1]) - 1;
                i++;
            }
            int [][] matrix = new int[n][n];
            for (i = 0; i < m; i++) {
                matrix[start[i]][end[i]] = 1;
                matrix[end[i]][start[i]] = 1;
            }
            try(PrintStream ps = new PrintStream("output.txt")){
                for (i = 0; i < n; i++) {
                    for (int j = 0; j < n;j++){
                        ps.print(matrix[i][j] + " ");
                    }
                    ps.println();
                }
            }
        } catch (Exception e) {
            System.out.println("Error");
        }

    }
}
