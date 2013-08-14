/****************************************************************************
Copyright (c) 2010-2012 cocos2d-x.org

http://www.cocos2d-x.org

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
 ****************************************************************************/
package com.fancyblock.slotcat;

import org.cocos2dx.lib.Cocos2dxActivity;
import org.cocos2dx.lib.Cocos2dxEditText;
import org.cocos2dx.lib.Cocos2dxGLSurfaceView;
import org.cocos2dx.lib.Cocos2dxRenderer;

import android.app.ActivityManager;
import android.content.Context;
import android.content.pm.ConfigurationInfo;
import android.os.Bundle;
import android.util.Log;
import android.view.ViewGroup;
import android.widget.FrameLayout;
import android.widget.RelativeLayout;

import com.flurry.android.FlurryAgent;
import com.google.ads.AdRequest;
import com.google.ads.AdSize;
import com.google.ads.AdView;

public class SlotCat extends Cocos2dxActivity
{
    private AdView m_adView;
    private RelativeLayout m_adContainer = null;

    protected void onCreate(Bundle savedInstanceState)
    {
	super.onCreate(savedInstanceState);

	if (detectOpenGLES20())
	{
	    // get the packageName,it's used to set the resource path
	    String packageName = getApplication().getPackageName();
	    super.setPackageName(packageName);

	    // FrameLayout
	    ViewGroup.LayoutParams framelayout_params = new ViewGroup.LayoutParams(
		    ViewGroup.LayoutParams.FILL_PARENT,
		    ViewGroup.LayoutParams.FILL_PARENT);
	    FrameLayout framelayout = new FrameLayout(this);
	    framelayout.setLayoutParams(framelayout_params);

	    // Cocos2dxEditText layout
	    ViewGroup.LayoutParams edittext_layout_params = new ViewGroup.LayoutParams(
		    ViewGroup.LayoutParams.FILL_PARENT,
		    ViewGroup.LayoutParams.WRAP_CONTENT);
	    Cocos2dxEditText edittext = new Cocos2dxEditText(this);
	    edittext.setLayoutParams(edittext_layout_params);

	    // ...add to FrameLayout
	    framelayout.addView(edittext);

	    // Cocos2dxGLSurfaceView
	    mGLView = new Cocos2dxGLSurfaceView(this);

	    // ...add to FrameLayout
	    framelayout.addView(mGLView);

	    mGLView.setEGLContextClientVersion(2);
	    mGLView.setCocos2dxRenderer(new Cocos2dxRenderer());
	    mGLView.setTextField(edittext);

	    // Set framelayout as the content view
	    setContentView(framelayout);

	    // Create the adView
	    m_adView = new AdView(this, AdSize.BANNER, GlobalInfo.ADMOB_ID);
	    m_adContainer = new RelativeLayout(this);
	    this.addContentView(m_adContainer, new ViewGroup.LayoutParams(
		    ViewGroup.LayoutParams.MATCH_PARENT,
		    ViewGroup.LayoutParams.MATCH_PARENT));
	    RelativeLayout.LayoutParams params = new RelativeLayout.LayoutParams(
		    RelativeLayout.LayoutParams.WRAP_CONTENT,
		    RelativeLayout.LayoutParams.WRAP_CONTENT);
	    // set the ad position
	    params.addRule(RelativeLayout.ALIGN_PARENT_LEFT,
		    RelativeLayout.ALIGN_LEFT);
	    params.addRule(RelativeLayout.ALIGN_PARENT_BOTTOM,
		    RelativeLayout.ALIGN_BOTTOM);

	    m_adContainer.addView(m_adView, params);
	    m_adView.loadAd(new AdRequest());

	} else
	{
	    Log.d("activity", "don't support gles2.0");
	    finish();
	}
    }

    @Override
    protected void onStart()
    {
	super.onStart();

	FlurryAgent.onStartSession(this, GlobalInfo.FLURRY_ID);
    }

    @Override
    protected void onPause()
    {
	super.onPause();
	mGLView.onPause();
    }

    @Override
    protected void onResume()
    {
	super.onResume();
	mGLView.onResume();
    }

    @Override
    protected void onStop()
    {
	if (m_adView != null)
	{
	    m_adView.destroy();
	}

	FlurryAgent.onEndSession(this);

	super.onStop();
    }

    @Override
    public void onBackPressed()
    {
	super.onBackPressed();
    }

    private boolean detectOpenGLES20()
    {
	ActivityManager am = (ActivityManager) getSystemService(Context.ACTIVITY_SERVICE);
	ConfigurationInfo info = am.getDeviceConfigurationInfo();
	return (info.reqGlEsVersion >= 0x20000);
    }

    static
    {
	System.loadLibrary("game");
    }
}
