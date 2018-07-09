package javaStudy;

public class BusExam {

	public static void main(String[] args) {
		Car c  = new Bus();
		c.run();
//		c.ppangppang();
		
		Bus bus = (Bus)c;
		bus.run();
		bus.ppangppang();
	}

}
