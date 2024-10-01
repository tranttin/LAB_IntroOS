import java.util.Random;

class BankAccount {
    private int balance = 0;

    public synchronized void deposit(int amount) {
        balance += amount;
        System.out.println(Thread.currentThread().getName() + " nạp " + amount + ". Số dư hiện tại: " + balance);
    }

    public synchronized void withdraw(int amount) {
        if (balance >= amount) {
            balance -= amount;
            System.out.println(Thread.currentThread().getName() + " rút " + amount + ". Số dư hiện tại: " + balance);
        } else {
            System.out.println(Thread.currentThread().getName() + " cố gắng rút " + amount + " nhưng không đủ tiền. Số dư hiện tại: " + balance);
        }
    }

    public synchronized void payOnline(int amount) {
        if (balance >= amount) {
            balance -= amount;
            System.out.println(Thread.currentThread().getName() + " thanh toán online " + amount + ". Số dư hiện tại: " + balance);
        } else {
            System.out.println(Thread.currentThread().getName() + " cố gắng thanh toán online " + amount + " nhưng không đủ tiền. Số dư hiện tại: " + balance);
        }
    }

    public synchronized void payBill(int amount) {
        if (balance >= amount) {
            balance -= amount;
            System.out.println(Thread.currentThread().getName() + " thanh toán hóa đơn " + amount + ". Số dư hiện tại: " + balance);
        } else {
            System.out.println(Thread.currentThread().getName() + " cố gắng thanh toán hóa đơn " + amount + " nhưng không đủ tiền. Số dư hiện tại: " + balance);
        }
    }

    public synchronized void payTuition(int amount) {
        if (balance >= amount) {
            balance -= amount;
            System.out.println(Thread.currentThread().getName() + " nộp học phí " + amount + ". Số dư hiện tại: " + balance);
        } else {
            System.out.println(Thread.currentThread().getName() + " cố gắng nộp học phí " + amount + " nhưng không đủ tiền. Số dư hiện tại: " + balance);
        }
    }

    public synchronized void buyDrink(int amount) {
        if (balance >= amount) {
            balance -= amount;
            System.out.println(Thread.currentThread().getName() + " mua nước " + amount + ". Số dư hiện tại: " + balance);
        } else {
            System.out.println(Thread.currentThread().getName() + " cố gắng mua nước " + amount + " nhưng không đủ tiền. Số dư hiện tại: " + balance);
        }
    }

    public int getBalance() {
        return balance;
    }
}

class BankTransactionTask implements Runnable {
    private final BankAccount account;
    private final String transactionType;
    private final int amount;
    private final Random random;

    public BankTransactionTask(BankAccount account, String transactionType, int amount) {
        this.account = account;
        this.transactionType = transactionType;
        this.amount = amount;
        this.random = new Random();
    }

    @Override
    public void run() {
        try {
            switch (transactionType) {
                case "DEPOSIT":
                    account.deposit(amount);
                    break;
                case "WITHDRAW":
                    account.withdraw(amount);
                    break;
                case "PAY_ONLINE":
                    account.payOnline(amount);
                    break;
                case "PAY_BILL":
                    account.payBill(amount);
                    break;
                case "PAY_TUITION":
                    account.payTuition(amount);
                    break;
                case "BUY_DRINK":
                    account.buyDrink(amount);
                    break;
            }
            // Tạm dừng ngẫu nhiên từ 0.5 đến 2 giây
            Thread.sleep(random.nextInt(1500) + 500);
        } catch (InterruptedException e) {
            e.printStackTrace();
        }
    }
}

public class BankTransactionDemo {
    public static void main(String[] args) {
        BankAccount account = new BankAccount();
        Random random = new Random();
        Thread[] threads = new Thread[26];

        // Thêm tiền vào tài khoản ban đầu
        account.deposit(1000); // Nạp 1000 ban đầu để có đủ số dư

        // Tạo các tác vụ ngẫu nhiên
        for (int i = 0; i < threads.length; i++) {
            String transactionType;
            int amount = random.nextInt(100) + 1; // Số tiền ngẫu nhiên từ 1 đến 100

            if (i < 4) {
                transactionType = "DEPOSIT"; // 4 lần nạp tiền
            } else if (i < 6) {
                transactionType = "WITHDRAW"; // 2 lần rút tiền
            } else if (i < 11) {
                transactionType = "PAY_TUITION"; // 2 lần nộp học phí
            } else if (i < 16) {
                transactionType = "PAY_BILL"; // 5 lần thanh toán hóa đơn
            } else {
                transactionType = "PAY_ONLINE"; // 15 lần thanh toán online
            }

            threads[i] = new Thread(new BankTransactionTask(account, transactionType, amount), "Thread " + i);
        }

        // Bắt đầu tất cả các thread
        for (Thread t : threads) {
            t.start();
        }

        // Đợi tất cả các thread hoàn thành
        for (Thread t : threads) {
            try {
                t.join();
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
        }

        // In số dư cuối cùng
        System.out.println("Số dư cuối cùng trong tài khoản: " + account.getBalance());
    }
}
