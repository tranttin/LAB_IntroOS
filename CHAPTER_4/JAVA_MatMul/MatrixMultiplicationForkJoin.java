import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.FileReader;
import java.io.FileWriter;
import java.io.IOException;
import java.util.concurrent.RecursiveTask;
import java.util.concurrent.ForkJoinPool;

public class MatrixMultiplicationForkJoin {
    private static double[][] matrixA;
    private static double[][] matrixB;
    private static double[][] resultMatrix;

    public static void main(String[] args) {
        if (args.length < 3) {
            System.out.println("Usage: java MatrixMultiplicationForkJoin <matrixAFile> <matrixBFile> <outputFile>");
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

        long startTime = System.currentTimeMillis();
        
        int rowsA = matrixA.length;
        int colsB = matrixB[0].length;
        resultMatrix = new double[rowsA][colsB];

        ForkJoinPool pool = new ForkJoinPool();
        pool.invoke(new MatrixMultiplier(0, rowsA, 0, colsB));

        long endTime = System.currentTimeMillis();
        long elapsedTime = endTime - startTime;

        writeMatrix(outputFile, resultMatrix);
        
        System.out.println("Kết quả đã được ghi vào " + outputFile);
        System.out.println("Thời gian thực thi: " + elapsedTime + " ms");
    }

    static class MatrixMultiplier extends RecursiveTask<Void> {
        private final int rowStart, rowEnd, colStart, colEnd;
        
        MatrixMultiplier(int rowStart, int rowEnd, int colStart, int colEnd) {
            this.rowStart = rowStart;
            this.rowEnd = rowEnd;
            this.colStart = colStart;
            this.colEnd = colEnd;
        }

        @Override
        protected Void compute() {
            if (rowEnd - rowStart <= 10) { // Threshold for splitting
                for (int i = rowStart; i < rowEnd; i++) {
                    for (int j = colStart; j < colEnd; j++) {
                        resultMatrix[i][j] = 0;
                        for (int k = 0; k < matrixA[0].length; k++) {
                            resultMatrix[i][j] += matrixA[i][k] * matrixB[k][j];
                        }
                    }
                }
            } else {
                int mid = (rowStart + rowEnd) / 2;
                invokeAll(new MatrixMultiplier(rowStart, mid, colStart, colEnd),
                           new MatrixMultiplier(mid, rowEnd, colStart, colEnd));
            }
            return null;
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