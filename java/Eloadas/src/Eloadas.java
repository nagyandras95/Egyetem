import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.util.Arrays;
import java.util.function.IntSupplier;

import javax.swing.JButton;

public class Eloadas {
    public static void main(String[] args) {
        JButton jb = new JButton();

        int c = 12;
        String s = "asdfa";

        IntSupplier supp = () -> 5325;

        jb.addActionListener(e -> {
        	System.out.println(c);
        	System.out.println(s);
        	System.out.println(supp.getAsInt());
//        	++c;
        });

        ActionListener actionListener = new ActionListener() {
			@Override
			public void actionPerformed(ActionEvent e) {

			}
		};
		jb.addActionListener(actionListener);
		jb.addActionListener(actionListener);

        MyActionListener myActionListener = new MyActionListener();
		jb.addActionListener(myActionListener);
        jb.addActionListener(myActionListener);

        int[] t1, t2;
        int t3[], t4[];
//
//        System.out.println(t1[1]);
//        System.out.println(t2[1]);
//        System.out.println(t3[1]);
//        System.out.println(t4[1]);

        elemss = new int[4][];
        for (int[] elems : elemss) {
			System.out.println(elems);
		}

        System.out.println(elemss);

        Integer[] elems2 = new Integer[5];
        System.out.println(elems2);

        System.out.println(Arrays.toString(elems2));
    }


    static int[][] elemss;
}


class MyActionListener implements ActionListener {

	@Override
	public void actionPerformed(ActionEvent e) {
		// ...
		System.out.println(e);
	}

}
