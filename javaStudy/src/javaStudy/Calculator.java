package javaStudy;

public interface Calculator { // Interface
	public int plus(int i, int j);
	public int multiple(int i, int j);

	default int exec(int i, int j) {
		return i + j;
	}
	
	public static int exec2(int i, int j) {
		return i * j;
	}
}
