public class led{
  public native int intMethod(int n);
  public native boolean booleanMethod(boolean bool);
  public native String stringMethod(String str);
  public native int intArrayMethod(int[] intArray);


  public static void main(String[] args){
    System.loadLibrary("led");
	led led1 = new led();
	 
	int square = led1.intMethod(5);
	boolean bool = led1.booleanMethod(true);
	String text = led1.stringMethod("Java");
	int sum = led1.intArrayMethod(new int[]{1,2,3,4,5,8,13});
	 
	System.out.println("intMethod: " + square);
	System.out.println("booleanMethod: " + bool);
	System.out.println("stringMethod: " + text);
	System.out.println("intArrayMethod: " + sum);
	
  }
}
