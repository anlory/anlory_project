

public class Uart {
  static {
    System.loadLibrary("uart_jni");
  }


  public static native int openDev(int num);
  public static native int closeDev();
  public static native int writeBuf(int fd, String writeBuf, int len);
  public static native String readBuf(int fd);



}
