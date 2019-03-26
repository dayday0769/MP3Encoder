package com.cjj.mp3encoder;

/**
 * @author chenjianjun
 * @name JniManager
 * @description
 * @date 2019/3/13
 */
public class JniManager {

    private static JniManager mContext = null;

    public JniManager() {
    }

    public static JniManager getInstance() {
        if (null == mContext) {
            mContext = new JniManager();
        }
        return mContext;
    }

    // Used to load the 'mp3encoder' library on application startup.
    static {
        System.loadLibrary("mp3encoder");
    }

    /**
     * A native method that is implemented by the 'native-lib' native library,
     * which is packaged with this application.
     */
    public native String stringFromJNI();

    public native String getLameVersion();

    public native int init(String pcmPath, int audioChannels, int bitRate, int sampleRate, String mp3Path);

    public native void encode();

    public native void destroy();


}
