//
//  ZoomVideoSDKUserInfo.h
//  ZoomVideoSDK
//
//  Created by Zoom Video Communications on 2018/12/7.
//  Copyright © 2018 Zoom Video Communications, Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "ZoomVideoSDKRawDataPipe.h"
#import "ZoomVideoSDKVideoCanvas.h"

/*!
 @class ZoomVideoSDKVideoStatisticInfo
 @brief Session video statistic information of the user
*/
@interface ZoomVideoSDKVideoStatisticInfo : NSObject
/*!
 @brief frame width
 */
@property (nonatomic, assign) NSInteger     width;
/*!
 @brief frame height
 */
@property (nonatomic, assign) NSInteger     height;
/*!
 @brief frame per second
 */
@property (nonatomic, assign) NSInteger     fps;
/*!
 @brief bits per second
 */
@property (nonatomic, assign) NSInteger     bps;

@end

/*!
 @class ZoomVideoSDKShareStatisticInfo
 @brief Session share statistic information of the user
*/
@interface ZoomVideoSDKShareStatisticInfo : NSObject
/*!
 @brief frame width
 */
@property (nonatomic, assign) NSInteger     width;
/*!
 @brief frame height
 */
@property (nonatomic, assign) NSInteger     height;
/*!
 @brief frame per second
 */
@property (nonatomic, assign) NSInteger     fps;
/*!
 @brief bits per second
 */
@property (nonatomic, assign) NSInteger     bps;

@end

/*!
 @class ZoomVideoSDKVideoStatus
 @brief Video status of user
 */
@interface ZoomVideoSDKVideoStatus : NSObject
/*!
 @brief The user's video is on/off.
 */
@property (nonatomic, assign) BOOL          on;

@end

/*!
 @class ZoomVideoSDKAudioStatus
 @brief Audio status of user
 */
@interface ZoomVideoSDKAudioStatus : NSObject
/*!
 @brief The user's audio is on/off.
 */
@property (nonatomic, assign) BOOL          isMuted;
/*!
 @brief The user is talking or not.
 */
@property (nonatomic, assign) BOOL          talking;
/*!
 @brief The user's audio type.
 */
@property (nonatomic, assign) ZoomVideoSDKAudioType  audioType;

@end

/*!
 @class ZoomVideoSDKShareStatus
 @brief Share status of user
 */
@interface ZoomVideoSDKShareStatus : NSObject
/*!
 @brief The user's share status.
 */
@property (nonatomic, assign) ZoomVideoSDKReceiveSharingStatus  sharingStatus;

@end

/*!
 @class ZoomVideoSDKUser
 @brief The user's information.
 */
@interface ZoomVideoSDKUser : NSObject
/*!
 @brief The user id.
 */
- (NSUInteger)getUserID;
/*!
 @brief The user's name.
 */
- (NSString *)getUserName;
/*!
 @brief The userId in custom system. Which pass in jwt token or in SDKSessionContext.customUserId
 */
- (NSString *)getCustomUserId;
/*!
 @brief The user is host or not.
 */
- (BOOL)isHost;
/*!
 @brief The user is Manager or not.
 */
- (BOOL)isManager;
/*!
 @brief The user video status.
 */
- (ZoomVideoSDKVideoStatus *)videoStatus;
/*!
 @brief The user Audio status.
 */
- (ZoomVideoSDKAudioStatus *)audioStatus;
/*!
 @brief The user share status.
 */
- (ZoomVideoSDKShareStatus *)shareStatus;
/*!
 @brief Get video statistic info.
 */
- (ZoomVideoSDKVideoStatisticInfo *)getVideoStatisticInfo;
/*!
 @brief Get share statistic info.
 */
- (ZoomVideoSDKShareStatisticInfo *)getShareStatisticInfo;
/*!
 @brief Get video pipe.
 */
- (ZoomVideoSDKRawDataPipe *)getVideoPipe;
/*!
 @brief Get share pipe.
 */
- (ZoomVideoSDKRawDataPipe *)getSharePipe;
/*!
 @brief Get video canvas.
 */
- (ZoomVideoSDKVideoCanvas *)getVideoCanvas;
/*!
 @brief Get share canvas.
 */
- (ZoomVideoSDKVideoCanvas *)getShareCanvas;

@end
