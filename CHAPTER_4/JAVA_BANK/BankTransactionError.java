class BankAccount {
    private int balance = 0;

    // Không dùng synchronized
    public void deposit(int amount) {
        balance += amount;
        System.out.println(Thread.currentThread().getName() + " nạp " + amount + ". Số dư hiện tại: " + balance);
    }

    // Không dùng synchronized
    public void withdraw(int amount) {
        if (balance >= amount) {
            balance -= amount;
            System.out.println(Thread.currentThread().getName() + " rút " + amount + ". Số dư hiện tại: " + balance);
        } else {
            System.out.println(Thread.currentThread().getName() + " cố gắng rút " + amount + " nhưng không đủ tiền. Số dư hiện tại: " + balance);
        }
    }

    public int getBalance() {
        return balance;
    }
}

class DepositTask implements Runnable {
    private final BankAccount account;
    private final int amount;

    public DepositTask(BankAccount account, int amount) {
        this.account = account;
        this.amount = amount;
    }

    @Override
    public void run() {
        account.deposit(amount);
    }
}

class WithdrawTask implements Runnable {
    private final BankAccount account;
    private final int amount;

    public WithdrawTask(BankAccount account, int amount) {
        this.account = account;  // Sửa lại thành đúng đối tượng BankAccount
        this.amount = amount;
    }

    @Override
    public void run() {
        account.withdraw(amount);
    }
}


public class BankTransactionError {
    public static void main(String[] args) {
        BankAccount account = new BankAccount();

        // Tạo một số lượng lớn các thread để nạp và rút tiền
        int numberOfTransactions = 10000;  // Số lượng giao dịch lớn
        Thread[] threads = new Thread[numberOfTransactions];

        // Khởi tạo nhiều thread thực hiện các giao dịch nạp và rút tiền đồng thời
        for (int i = 0; i < numberOfTransactions; i++) {
            if (i % 2 == 0) {
                threads[i] = new Thread(new DepositTask(account, 100), "Thread " + i);
            } else {
                threads[i] = new Thread(new WithdrawTask(account, 50), "Thread " + i);
            }
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
