import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.FileReader;
import java.io.FileWriter;
import java.io.IOException;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;

public class MatrixMultiplicationThread {
    private static double[][] matrixA;
    private static double[][] matrixB;
    private static double[][] resultMatrix;

    public static void main(String[] args) {
        if (args.length < 3) {
            System.out.println("Usage: java MatrixMultiplicationThread <matrixAFile> <matrixBFile> <outputFile>");
            return;
        }

        String matrixAFile = args[0];
        String matrixBFile = args[1];
        String outputFile = args[2];

        matrixA = readMatrix(matrixAFile);
        matrixB = readMatrix(matrixBFile);

        if (matrixA[0].length != matrixB.length) {
            System.err.println("Số cột của ma trận A không bằng số hàng của ma trận B. Không thể nhân hai ma trận.");
            return;
        }

        // Đo thời gian bắt đầu
        long startTime = System.currentTimeMillis();

        int rowsA = matrixA.length;
        int colsB = matrixB[0].length;
        resultMatrix = new double[rowsA][colsB];

        ExecutorService executor = Executors.newFixedThreadPool(4);
        for (int i = 0; i < rowsA; i++) {
            final int row = i;
            executor.submit(() -> multiplyRow(row));
        }
        executor.shutdown();
        while (!executor.isTerminated()) {}

        // Đo thời gian kết thúc
        long endTime = System.currentTimeMillis();
        long elapsedTime = endTime - startTime;

        writeMatrix(outputFile, resultMatrix);

        // Tính toán bộ nhớ tiêu hao
        Runtime runtime = Runtime.getRuntime();
        long memoryUsed = runtime.totalMemory() - runtime.freeMemory();

        System.out.println("Kết quả đã được ghi vào " + outputFile);
        System.out.println("Thời gian thực thi: " + elapsedTime + " ms");
        System.out.println("Bộ nhớ tiêu hao: " + memoryUsed / 1024 + " KB");
    }

    private static void multiplyRow(int row) {
        int colsB = matrixB[0].length;
        for (int j = 0; j < colsB; j++) {
            resultMatrix[row][j] = 0;
            for (int k = 0; k < matrixA[0].length; k++) {
                resultMatrix[row][j] += matrixA[row][k] * matrixB[k][j];
            }
        }
    }

    private static double[][] readMatrix(String filename) {
        try (BufferedReader reader = new BufferedReader(new FileReader(filename))) {
            String line = reader.readLine();

            if (line == null || line.trim().isEmpty()) {
                throw new IllegalArgumentException("Dòng đầu tiên không hợp lệ hoặc file rỗng.");
            }

            String[] dimensions = line.split(" ");
            int rows = Integer.parseInt(dimensions[0]);
            int cols = Integer.parseInt(dimensions[1]);
            double[][] matrix = new double[rows][cols];

            for (int i = 0; i < rows; i++) {
                line = reader.readLine();
                if (line == null) {
                    throw new IllegalArgumentException("Dữ liệu không đủ tại dòng " + (i + 2));
                }
                String[] values = line.split(" ");
                if (values.length != cols) {
                    throw new IllegalArgumentException("Số cột không khớp tại dòng " + (i + 2));
                }
                for (int j = 0; j < cols; j++) {
                    matrix[i][j] = Double.parseDouble(values[j]);
                }
            }
            return matrix;
        } catch (IOException e) {
            System.err.println("Lỗi khi đọc file: " + e.getMessage());
            return new double[0][0];
        } catch (NumberFormatException e) {
            System.err.println("Lỗi định dạng số: " + e.getMessage());
            return new double[0][0];
        } catch (IllegalArgumentException e) {
            System.err.println(e.getMessage());
            return new double[0][0];
        }
    }

    private static void writeMatrix(String filename, double[][] matrix) {
        try (BufferedWriter writer = new BufferedWriter(new FileWriter(filename))) {
            int rows = matrix.length;
            int cols = matrix[0].length;

            writer.write(rows + " " + cols);
            writer.newLine();
            for (double[] row : matrix) {
                for (int j = 0; j < row.length; j++) {
                    writer.write(String.format("%.2f", row[j]));
                    if (j < row.length - 1) {
                        writer.write(" ");
                    }
                }
                writer.newLine();
            }
        } catch (IOException e) {
            System.err.println("Lỗi khi ghi file: " + e.getMessage());
        }
    }
}
