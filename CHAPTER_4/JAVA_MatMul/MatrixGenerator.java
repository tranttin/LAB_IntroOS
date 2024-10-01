import java.io.BufferedWriter;
import java.io.FileWriter;
import java.io.IOException;
import java.util.Random;

public class MatrixGenerator {
    public static void main(String[] args) {
        if (args.length < 3) {
            System.out.println("Usage: java MatrixGenerator <filename> <rows> <columns>");
            return;
        }

        String filename = args[0];
        int rows = Integer.parseInt(args[1]);
        int cols = Integer.parseInt(args[2]);

        generateMatrix(filename, rows, cols);
    }

    private static void generateMatrix(String filename, int rows, int cols) {
        Random random = new Random();

        try (BufferedWriter writer = new BufferedWriter(new FileWriter(filename))) {
            // Ghi kích thước ma trận
            writer.write(rows + " " + cols);
            writer.newLine();

            for (int i = 0; i < rows; i++) {
                for (int j = 0; j < cols; j++) {
                    // Tạo số thực ngẫu nhiên trong khoảng [0.0, 100.0]
                    double value = random.nextDouble() * 100;
                    writer.write(String.format("%.2f", value)); // Ghi số với 2 chữ số thập phân
                    if (j < cols - 1) {
                        writer.write(" "); // Ghi dấu cách giữa các số
                    }
                }
                writer.newLine();
            }

            System.out.println("Ma trận đã được tạo và lưu vào " + filename);
        } catch (IOException e) {
            System.err.println("Lỗi khi ghi file: " + e.getMessage());
        }
    }
}
