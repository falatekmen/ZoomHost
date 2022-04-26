//
//  ZoomVideoSDK.h
//  ZoomVideoSDK
//

#import <UIKit/UIKit.h>
#import <Foundation/Foundation.h>
#import "ZoomVideoSDKUser.h"
#import "ZoomVideoSDKDelegate.h"
#import "ZoomVideoSDKConstants.h"
#import "ZoomVideoSDKAudioHelper.h"
#import "ZoomVideoSDKVideoHelper.h"
#import "ZoomVideoSDKUserHelper.h"
#import "ZoomVideoSDKVideoCanvas.h"
#import "ZoomVideoSDKRawDataPipe.h"
#import "ZoomVideoSDKShareHelper.h"
#import "ZoomVideoSDKLiveStreamHelper.h"
#import "ZoomVideoSDKChatHelper.h"
#import "ZoomVideoSDKPhoneHelper.h"
#import "ZoomVideoSDKCmdChannel.h"
#import "ZoomVideoSDKRecordingHelper.h"

/*!
 @class ZoomVideoSDKInitParams
 @brief Parameter class use to initialize the ZoomVideoSDK.
 */
@interface ZoomVideoSDKInitParams : NSObject
/*!
 @brief [Required] The domain of ZoomVideoSDK.
 */
@property (nonatomic, copy) NSString * _Nullable domain;
/*!
 @brief [Optional] The Prefix of Log file name.
 */
@property (nonatomic, copy) NSString * _Nullable logFilePrefix;
/*!
 @brief [Optional] If you use screen share, you need create group id in your apple developer account, and setup here.
 */
@property (nonatomic, copy) NSString * _Nullable  appGroupId;
/*!
 @brief [Optional] enable/disable log of SDK. log path AppData/tmp
 */
@property (nonatomic, assign) BOOL                          enableLog;
/*!
 @brief [Optional] The video rawdata memory mode. Default is ZoomVideoSDKRawDataMemoryModeStack
 */
@property (nonatomic, assign) ZoomVideoSDKRawDataMemoryMode  videoRawdataMemoryMode;
/*!
 @brief [Optional] The share rawdata memory mode. Default is ZoomVideoSDKRawDataMemoryModeStack
 */
@property (nonatomic, assign) ZoomVideoSDKRawDataMemoryMode  shareRawdataMemoryMode;
/*!
 @brief [Optional] The audio rawdata memory mode. Default is ZoomVideoSDKRawDataMemoryModeStack
 */
@property (nonatomic, assign) ZoomVideoSDKRawDataMemoryMode  audioRawdataMemoryMode;
@end

/*!
 @class ZoomVideoSDKVideoOptions
 @brief The video option of join session
 */
@interface ZoomVideoSDKVideoOptions : NSObject

/*!
 @brief Local video on or off
 */
@property (assign, nonatomic) BOOL localVideoOn;

@end

/*!
 @class ZoomVideoSDKAudioOptions
 @brief The audio option of join session
 */
@interface ZoomVideoSDKAudioOptions : NSObject

/*!
 @brief Local audio connect or not
 */
@property (assign, nonatomic) BOOL connect;

/*!
 @brief Local audio mute or not
 */
@property (assign, nonatomic) BOOL mute;
@end

/*!
 @class ZoomVideoSDKSessionContext
 @brief A Class contains the session information.
 */
@interface ZoomVideoSDKSessionContext : NSObject
/*!
 @brief [Required] Session Name.
 sessionName The string length must be less than 150.
 Supported character scopes are: Letters, numbers, spaces, and the following characters:
 "!", "#", "$", "%", "&", "(", ")", "+", "-", ":", ";", "<", "=", ".", ">", "?", "@", "[", "]", "^", "_", "{", "}", "|", "~", ","
 */
@property (nonatomic, copy) NSString * _Nullable sessionName;
/*!
 @brief [Optional] Session Password.
 */
@property (nonatomic, copy) NSString * _Nullable sessionPassword;
/*!
 @brief [Required] User Name.
 */
@property (nonatomic, copy) NSString * _Nullable userName;
/*!
 @brief [Required] JWT token to join session.
 */
@property (nonatomic, copy) NSString * _Nullable token;
/*!
 @brief [Optional] The amount of time in minutes after which an idle session will end.
 Default value: 40
 If the value is less than 0, the session will stay alive indefinitely.
 When there is only one user remaining in a session, that session is considered idle.
 */
@property (nonatomic, assign) NSInteger sessionIdleTimeoutMins;
/*!
 @brief [Optional]  Audio Option.
 */
@property (nonatomic, strong) ZoomVideoSDKAudioOptions * _Nullable audioOption;
/*!
 @brief [Optional] Video Option.
 */
@property (nonatomic, strong) ZoomVideoSDKVideoOptions * _Nullable videoOption;

/*!
@brief [Optional] Session external video source delegate.
*/
@property (nonatomic, assign) id<ZoomVideoSDKVideoSource> _Nullable externalVideoSourceDelegate;

/*!
@brief [Optional] Session pre-processer delegate.
*/
@property (nonatomic, assign) id<ZoomVideoSDKVideoSourcePreProcessor> _Nullable preProcessorDelegate;

/*!
@brief [Optional] Session external audio source delegate.
*/
@property (nonatomic, assign) id<ZoomVideoSDKVirtualAudioMic> _Nullable virtualAudioMicDelegate;

/*!
@brief [Optional] Session virtual speaker.
*/
@property (nonatomic, assign) id<ZoomVideoSDKVirtualAudioSpeaker> _Nullable virtualAudioSpeakerDelegate;
@end

/*!
 @class ZoomVideoSDKSessionAudioStatisticInfo
 @brief Session audio statistic information
*/
@interface ZoomVideoSDKSessionAudioStatisticInfo : NSObject
/// session send frequency
@property(nonatomic, assign, readonly) NSInteger  sendFrequency;
/// session send latency
@property(nonatomic, assign, readonly) NSInteger  sendLatency;
/// session send jitter
@property(nonatomic, assign, readonly) NSInteger  sendJitter;
/// session send packet loss average value
@property(nonatomic, assign, readonly) CGFloat    sendPacketLossAvg;
///session send packet loss max value
@property(nonatomic, assign, readonly) CGFloat    sendPacketLossMax;

/// session receive frequency
@property(nonatomic, assign, readonly) NSInteger  recvFrequency;
/// session receive latency
@property(nonatomic, assign, readonly) NSInteger  recvLatency;
/// session receive jitter
@property(nonatomic, assign, readonly) NSInteger  recvJitter;
/// session receive packet loss average value
@property(nonatomic, assign, readonly) CGFloat    recvPacketLossAvg;
///session receive packet loss max value
@property(nonatomic, assign, readonly) CGFloat    recvPacketLossMax;
@end

/*!
@brief The Session video or share statistic information
*/

@interface ZoomVideoSDKSessionASVStatisticInfo : NSObject
/// session send frame width
@property(nonatomic, assign, readonly) NSInteger  sendFrameWidth;
/// session send frame height
@property(nonatomic, assign, readonly) NSInteger  sendFrameHeight;
/// session send fps
@property(nonatomic, assign, readonly) NSInteger  sendFps;
/// session send latency
@property(nonatomic, assign, readonly) NSInteger  sendLatency;
/// session send jitter
@property(nonatomic, assign, readonly) NSInteger  sendJitter;
/// session send packet loss average value
@property(nonatomic, assign, readonly) CGFloat    sendPacketLossAvg;
/// session send packet loss max value
@property(nonatomic, assign, readonly) CGFloat    sendPacketLossMax;

/// session receive frame width
@property(nonatomic, assign, readonly) NSInteger  recvFrameWidth;
/// session receive frame height
@property(nonatomic, assign, readonly) NSInteger  recvFrameHeight;
/// session receive fps
@property(nonatomic, assign, readonly) NSInteger  recvFps;
/// session receive latency
@property(nonatomic, assign, readonly) NSInteger  recvLatency;
/// session receive jitter
@property(nonatomic, assign, readonly) NSInteger  recvJitter;
/// session receive packet loss average value
@property(nonatomic, assign, readonly) CGFloat    recvPacketLossAvg;
/// session receive packet loss max value
@property(nonatomic, assign, readonly) CGFloat    recvPacketLossMax;
@end


/*!
 @brief Zoom Video SDK session.
 */
@interface ZoomVideoSDKSession : NSObject

/*!
@brief Get the session name.
*/
- (NSString * _Nullable)getSessionName;

/*!
@brief Get the session id.
@warning only host can get the session id
*/
- (NSString * _Nullable)getSessionID;

/*!
@brief Get the session password
*/
- (NSString * _Nullable)getSessionPassword;

/*!
@brief Get the session host name
*/
- (NSString * _Nullable)getSessionHostName;

/*!
@brief Get the session host user object
*/
- (ZoomVideoSDKUser * _Nullable)getSessionHost;

/*!
@brief Get the session all remote user list(except me).
*/
- (NSArray <ZoomVideoSDKUser *>* _Nullable)getRemoteUsers;

/*!
@brief Get my self user object in session
*/
- (ZoomVideoSDKUser * _Nullable)getMySelf;

/*!
@brief Get the session audio statistic information.
*/
- (ZoomVideoSDKSessionAudioStatisticInfo * _Nullable)getSessionAudioStatisticInfo;

/*!
@brief Get the session video statistic information.
*/
- (ZoomVideoSDKSessionASVStatisticInfo * _Nullable)getSessionVideoStatisticInfo;
/*!
@brief Get the session share statistic information.
*/
- (ZoomVideoSDKSessionASVStatisticInfo * _Nullable)getSessionShareStatisticInfo;

@end

/*!
 @class ZoomVideoSDK
 @brief Initialize the class to acquire all the services.
 @warning Access to the class and all the other components of the VideoSDK by merging <ZoomVideoSDK/ZoomVideoSDK.h> into source code.
 @warning The user can only obtain SDK configuration by initializing the class.
 */
@interface ZoomVideoSDK : NSObject

/*!
 @brief The delegate of ZoomVideoSDK, all callback of receiving conversation events.
 */
@property (nullable, assign, nonatomic) id<ZoomVideoSDKDelegate> delegate;

/*!
 @brief Singleton object of ZoomVideoSDK.
 */
+ (ZoomVideoSDK * _Nullable)shareInstance;

/*!
 @brief Call the function to initialize VideoSDK.
 @warning The instance will be instantiated only once over the lifespan of the application.
 @param context Initialize the parameter configuration of the SDK, please See [ZoomVideoSDKInitParams]
 */
- (ZoomVideoSDKERROR)initialize:(ZoomVideoSDKInitParams * _Nonnull)context;

/*!
@brief Notify common layer that application will resign active. Call the systematical method and then call the appWillResignActive via applicationWillResignActive.
@warning It is necessary to call the method in AppDelegate "- (void)applicationWillResignActive:(UIApplication *)application".
*/
- (void)appWillResignActive;

/*!
 @brief Notify common layer that application did become active. Call the appDidBecomeActive via applicationDidBecomeActive.
 @warning It is necessary to call the method in AppDelegate "- (void)applicationDidBecomeActive:(UIApplication *)application".
 */
- (void)appDidBecomeActive;

/*!
 @brief Notify common layer that application did enter background. Call the appDidEnterBackgroud via applicationDidEnterBackground.
 @warning It is necessary to call the method in AppDelegate "- (void)applicationDidEnterBackground:(UIApplication *)application".
 */
- (void)appDidEnterBackgroud;

/*!
 @brief Notify common layer that application will terminate. Call the appWillTerminate via applicationWillTerminate.
 @warning It is necessary to call the method in AppDelegate "- (void)applicationWillTerminate:(UIApplication *)application".
 */
- (void)appWillTerminate;

/*!
 @brief Use it to join a session with parameters in a SDKSessionContext.See [SDKSessionContext]
 @param context The context which contains the parameters.
 @return The state of join session, started or failed.
 */
- (ZoomVideoSDKSession * _Nullable)joinSession:(ZoomVideoSDKSessionContext * _Nonnull)context;

/*!
 @brief Use it to leave session.
 @param end Yes means end session, otherwize means leave session.
 @warning only host can end session. You can get the isHost information from in-Session 'userInfo'.
 @return The result of it.
 */
- (ZoomVideoSDKERROR)leaveSession:(BOOL)end;

/*!
 @brief Use it to get session information.
 @return Session information See [SDKSessionInfo].
 */
- (ZoomVideoSDKSession * _Nullable)getSession;

/*!
 @brief Whether it is in the session.
 @return Is in session or not.
 */
- (BOOL)isInSession;

/*!
 @brief Current SDK version.
 @return The version of SDK.
 */
- (NSString * _Nullable)getSDKVersion;

/*!
 @brief Instance of ZoomVideoSDKAudioHelper. See [ZoomVideoSDKAudioHelper].
 @return The object of ZoomVideoSDKAudioHelper.
 */
- (ZoomVideoSDKAudioHelper * _Nonnull)getAudioHelper;

/*!
 @brief Instance of ZoomVideoSDKVideoHelper. See [ZoomVideoSDKVideoHelper].
 @return The object of ZoomVideoSDKVideoHelper.
 */
- (ZoomVideoSDKVideoHelper * _Nonnull)getVideoHelper;

/*!
 @brief Instance of ZoomVideoSDKUserHelper. See [ZoomVideoSDKUserHelper].
 @return The object of ZoomVideoSDKUserHelper.
 */
- (ZoomVideoSDKUserHelper * _Nonnull)getUserHelper;

/*!
 @brief Instance of ZoomVideoSDKShareHelper. See [ZoomVideoSDKShareHelper].
 @return The object of ZoomVideoSDKShareHelper.
 */
- (ZoomVideoSDKShareHelper * _Nonnull)getShareHelper;

/*!
 @brief Instance of ZoomVideoSDKLiveStreamHelper. See [ZoomVideoSDKLiveStreamHelper].
 @return The object of ZoomVideoSDKLiveStreamHelper.
 */
- (ZoomVideoSDKLiveStreamHelper * _Nonnull)getLiveStreamHelper;

/*!
 @brief Instance of ZoomVideoSDKChatHelper. See [ZoomVideoSDKChatHelper].
 @return The object of ZoomVideoSDKChatHelper.
 */
- (ZoomVideoSDKChatHelper * _Nonnull)getChatHelper;

/*!
 @brief Instance of ZoomVideoSDKPhoneHelper. See [ZoomVideoSDKPhoneHelper].
 @return The object of ZoomVideoSDKPhoneHelper.
 */
- (ZoomVideoSDKPhoneHelper * _Nonnull)getPhoneHelper;

/*!
 @brief Get an instance to access the command channel.
 @return A [ZoomVideoSDKCmdChannel] instance.
 */
- (ZoomVideoSDKCmdChannel * _Nonnull)getCmdChannel;

/*!
 @brief Get the helper class instance to access cloud recording.
 @return A [ZoomVideoSDKRecordingHelper] instance.
 */
- (ZoomVideoSDKRecordingHelper * _Nonnull)getRecordingHelper;
@end
