package org.cocos2dx.tests;

import org.cocos2dx.lib.Cocos2dxActivity;
import org.cocos2dx.lib.Cocos2dxGLSurfaceView;

import android.os.Bundle;

public class TestsDemo extends Cocos2dxActivity{
	private Cocos2dxGLSurfaceView mGLView;

    protected void onCreate(Bundle savedInstanceState){
		super.onCreate(savedInstanceState);
		
		// get the packageName,it's used to set the resource path
		String packageName = getApplication().getPackageName();
		super.setPackgeName(packageName);

        setContentView(R.layout.test_demo);
        mGLView = (Cocos2dxGLSurfaceView) findViewById(R.id.test_demo_gl_surfaceview);

        // Get the size of the mGLView after the layout happens
        mGLView.post(new Runnable() {
            
            @Override
            public void run() {
                Cocos2dxActivity.screenHeight = mGLView.getHeight();
                Cocos2dxActivity.screenWidth = mGLView.getWidth();
            }
        });
	}

	 @Override
	 protected void onPause() {		 
	     super.onPause();
	     
	     mGLView.onPause();
	 }

	 @Override
	 protected void onResume() {
	     super.onResume();
	     
	     mGLView.onResume();
	 }
	 
	 protected void onDestroy()
	 {
		 super.onDestroy();
		 
		 android.os.Process.killProcess(android.os.Process.myPid());
	 }

     static {
    	 System.loadLibrary("cocosdenshion");
    	 System.loadLibrary("chipmunk");
    	 System.loadLibrary("box2d");
    	 System.loadLibrary("cocos2d");
         System.loadLibrary("tests");
     }     
}
