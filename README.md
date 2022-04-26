
# ZoomHost App &nbsp; <img width="35" alt="image" src="https://user-images.githubusercontent.com/81239267/160300680-5b11f386-901b-49bd-9410-3648d50b4a84.png">

App for initiating voice calls in React Native using Zoom Video SDK.

<img width="400" alt="image" src="https://user-images.githubusercontent.com/81239267/165166232-e0cdbea8-5e6a-4bc3-b2b5-6ea413fee98b.png">

- Enter the same season name to start a joint call on devices.

- Also, this application can be used to test the [rn-zoom-voice-call](https://www.npmjs.com/package/rn-zoom-voice-call) or [rn-voice-call](https://www.npmjs.com/package/rn-voice-call) packages. After starting a call, the necessary parameters for the packages can be copied by pressing the `Copy Data` button and sent to the device where the application to be tested is located.

##### APK url: [ZoomHost APK](https://drive.google.com/file/d/1hRxQQ5hgPtlm8KgcUxxrSIQ1H-VQ-iSR/view?usp=sharing)

## Build the app

    yarn install
    cd ios && pod install && cd ..

You have two options to enter the App Key and App Secret:

#### <ins>Option 1</ins>
 
Add the App Key and App Secret to the config.js.

<img width="330" alt="image" src="https://user-images.githubusercontent.com/81239267/160303031-12928cd3-3084-4868-8ba6-fbc2bd7d1680.png">

#### <ins>Option 2</ins>
 
If no App Key and App Secret have been added to the config.js, these will be requested at the application startup.
 
<img width="150" alt="image" src="https://user-images.githubusercontent.com/81239267/163490121-862a613c-39c9-4ec3-8083-0f41566a727e.png">

### <ins>Setting up developer account for App Key and App Secret</ins>

1- Create a [Zoom Account](https://zoom.us/buy/videosdk).

2- Login to [Zoom Developer Platform](https://developers.zoom.us) and then click [Build App](https://marketplace.zoom.us/develop/create).

3- Click "View Here" on the page that opens and enter the company name in the information tab.

<img width="200" alt="image" src="https://user-images.githubusercontent.com/81239267/158472724-284763be-6bf3-4490-a140-6a725c46ba72.png">

<img width="400" alt="image" src="https://user-images.githubusercontent.com/81239267/164952949-7f811af4-53de-4037-9de0-2b001b1c6aae.png">

4- In the App Credentials tab, copy the SDK Key and SDK Secret.

<img width="400" alt="image" src="https://user-images.githubusercontent.com/81239267/160302887-b44d5718-1332-4137-87f2-c0e5a0094211.png">

For more information: [Zoom.us](https://marketplace.zoom.us/docs/sdk/video/react-native/getting-started)

## Troubleshooting

<b>1- The Error Log:</b> `zoom_react-native-videosdk:compileDebugJavaWithJavac`

<img width="550" alt="image" src="https://user-images.githubusercontent.com/81239267/158476423-0a5384f8-7cb8-4ed8-aa27-ac4bf7551c6c.png">

Add the following to the node_modules/@zoom/react-native-videosdk/android/src/main/java/com/reactnativezoomvideosdk/RNZoomVideoSdkModule.java

    // Import these
    import us.zoom.sdk.ZoomVideoSDKPhoneFailedReason;
    import us.zoom.sdk.ZoomVideoSDKPhoneStatus;

    public class RNZoomVideoSdkModule extends ReactContextBaseJavaModule implements ZoomVideoSDKDelegate, LifecycleEventListener {
    
      // Add this
      @Override
      public void onInviteByPhoneStatus(ZoomVideoSDKPhoneStatus zoomVideoSDKPhoneStatus, ZoomVideoSDKPhoneFailedReason zoomVideoSDKPhoneFailedReason) { 
      }
    ...
    }

<b>2- The Warning Log:</b> `"new NativeEventEmitter()" was called with a non-null argument without the required "removeListeners" method`

<img width="575" alt="image" src="https://user-images.githubusercontent.com/81239267/160304087-78e4946d-3185-4f5e-9d80-b919abab18be.png">

Add the following to the node_modules/@zoom/react-native-videosdk/android/src/main/java/com/reactnativezoomvideosdk/RNZoomVideoSdkModule.java

    public class RNZoomVideoSdkModule extends ReactContextBaseJavaModule implements ZoomVideoSDKDelegate, LifecycleEventListener {
  
    // Add this
    @ReactMethod
    public void addListener(String eventName) {}

    // Add this
    @ReactMethod
    public void removeListeners(Integer count) {}
    ...
    }