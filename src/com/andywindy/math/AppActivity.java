/*
Mastering NDK
 */

package com.andywindy.math;

import android.app.Activity;
import android.os.Bundle;

public class AppActivity extends org.libsdl.app.SDLActivity
{
	static
	{
		System.loadLibrary( "NativeLib" );
	}

	public static AppActivity m_Activity;

	@Override protected void onCreate( Bundle icicle )
	{
		super.onCreate( icicle );

		m_Activity = this;

//		onCreateNative( getApplication().getApplicationInfo().sourceDir );
	}

//	public static native void onCreateNative( String APKName );
};
