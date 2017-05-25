
public class Parhuzamossag {
	public static void main(String[] args) throws InterruptedException {
		Object lock = new Object();
		new MyPrinter("aaaaaaaaaaaaaaaaaaaaaaaaaaaa", lock).start();
		new MyPrinter("bbbbbbbbbbbbbbbbbbbbbbbbbbbb", lock).start();

//		new MyPrinter("aaaaaaaaaaaaaaaaaaaaaaaaaaaa", lock).run();
//		new MyPrinter("bbbbbbbbbbbbbbbbbbbbbbbbbbbb", lock).run();
	}

	public static void main2(String[] args) throws InterruptedException {
		Object lock = new Object();
		int[] szamlalo = { 0 };
//		int szamlalo2 = 0;

		Thread thread = new Thread(() -> {
			for (int i = 0; i < 100000; i++) {
				System.out.println("Hello vilag " + szamlalo[0]);
//				System.out.println("sz2 " + szamlalo2);
//				++szamlalo2;

				synchronized (szamlalo) {
					++szamlalo[0];
//					++szamlalo2;
				}
			}
		});
//		thread.setDaemon(true);
		thread.start();

		Thread thread2 = new Thread(() -> {
			for (int i = 0; i < 100000; i++) {
				System.out.println("abcdefg " + szamlalo[0]);
				synchronized (szamlalo) {
					szamlalo[0] += 2;
				}
			}
		});
//		thread2.setDaemon(true);
		thread2.start();

//		Runnable r = () -> {
//			for (int i = 0; i < 100000; i++) {
//				System.out.println("xyzabc " + szamlalo[0]);
////				synchronized (lock) {
////					szamlalo[0] += 2;
////				}
//			}
//		};
//
//		new Thread(r).start();
//
//		new Thread(() -> {
//			for (int i = 0; i < 100000; i++) {
//				System.out.println("abcdefg " + szamlalo[0]);
//				synchronized (lock) {
//					szamlalo[0] += 3;
//				}
//			}
//		}).start();

		thread.join();
		thread2.join();

////		// altalaban nem jo
//		thread.run();
//		thread2.run();

		System.out.println("vege " + szamlalo[0]);
	}
}



class MyPrinter extends Thread {
	private String text;
	private Object lock;

	public MyPrinter(String text, Object lock) {
		this.text = text;
		this.lock = lock;
	}

	@Override
	public void run() {
		for (int i = 0; i < 100000; i++) {
			myPrintln(text);
		}
	}

	private void myPrintln(String text2) {
//		synchronized (MyPrinter.class ) {
//		synchronized (System.out) {
		synchronized (lock) {
//		synchronized (this) {
			for (char c : text2.toCharArray()) {
				System.out.print(c);
			}
			System.out.println();
		}
	}

	private synchronized void myPrintln2(String text2) {
		for (char c : text2.toCharArray()) {
			System.out.print(c);
		}
		System.out.println();
	}
}


class MyPrinter2 implements Runnable {
	@Override
	public void run() {
	}
}

