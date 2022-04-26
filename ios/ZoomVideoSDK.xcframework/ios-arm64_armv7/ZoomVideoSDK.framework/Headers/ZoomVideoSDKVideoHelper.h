//
//  ZoomVideoSDKVideoHelper.h
//  ZoomVideoSDK
//
//  Created by Zoom Video Communications on 2018/12/6.
//  Copyright © 2018 Zoom Video Communications, Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

/*!
 @class ZoomVideoSDKVideoHelper
 @brief A class to operate the video action.
 */
@interface ZoomVideoSDKVideoHelper : NSObject

/*!
 @brief Start send video.
 @return the result of it.
 */
- (ZoomVideoSDKERROR)startVideo;

/*!
 @brief Stop send video.
 @return the result of it.
 */
- (ZoomVideoSDKERROR)stopVideo;

/*!
 @brief Rotate my video. When the device onConfigurationChanged.
 @return the result of it.
 @warning the function only for internal video source, it's not work for capture video source.
 */
- (BOOL)rotateMyVideo:(UIDeviceOrientation)rotation;

/*!
 @brief Set to Switch the camera of the current user in local device.
 */
- (void)switchCamera;

@end
