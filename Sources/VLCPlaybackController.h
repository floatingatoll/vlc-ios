/*****************************************************************************
 * VLCPlaybackController.h
 * VLC for iOS
 *****************************************************************************
 * Copyright (c) 2013-2015 VideoLAN. All rights reserved.
 * $Id$
 *
 * Authors: Felix Paul Kühne <fkuehne # videolan.org>
 *          Tobias Conradi <videolan # tobias-conradi.de>
 *
 * Refer to the COPYING file of the official project for license.
 *****************************************************************************/

#import "VLCEqualizerView.h"

extern NSString *const VLCPlaybackControllerPlaybackDidStart;
extern NSString *const VLCPlaybackControllerPlaybackDidPause;
extern NSString *const VLCPlaybackControllerPlaybackDidResume;
extern NSString *const VLCPlaybackControllerPlaybackDidStop;
extern NSString *const VLCPlaybackControllerPlaybackDidFail;
extern NSString *const VLCPlaybackControllerPlaybackMetadataDidChange;
extern NSString *const VLCPlaybackControllerPlaybackPositionUpdated;

@class VLCPlaybackController;
@class VLCMetaData;

@protocol VLCPlaybackControllerDelegate <NSObject>
@optional
- (void)playbackPositionUpdated:(VLCPlaybackController *)controller;
- (void)mediaPlayerStateChanged:(VLCMediaPlayerState)currentState
                      isPlaying:(BOOL)isPlaying
currentMediaHasTrackToChooseFrom:(BOOL)currentMediaHasTrackToChooseFrom
        currentMediaHasChapters:(BOOL)currentMediaHasChapters
          forPlaybackController:(VLCPlaybackController *)controller;
- (void)prepareForMediaPlayback:(VLCPlaybackController *)controller;
- (void)showStatusMessage:(NSString *)statusMessage forPlaybackController:(VLCPlaybackController *)controller;
- (void)displayMetadataForPlaybackController:(VLCPlaybackController *)controller metadata:(VLCMetaData *)metadata;

@end

@interface VLCPlaybackController : NSObject <VLCEqualizerViewDelegate>

@property (nonatomic, readonly) VLCMediaListPlayer *listPlayer;
@property (nonatomic, readonly) VLCMediaPlayer *mediaPlayer;

@property (nonatomic, strong) UIView *videoOutputView;

@property (nonatomic, strong) NSURL *successCallback;
@property (nonatomic, strong) NSURL *errorCallback;

@property (nonatomic, retain) VLCMediaList *mediaList;

#if TARGET_OS_IOS
/* returns nil if currently playing item is not a MLFile, e.g. a url */
@property (nonatomic, strong, readonly) MLFile *currentlyPlayingMediaFile;
#endif

@property (nonatomic, weak) id<VLCPlaybackControllerDelegate> delegate;

@property (nonatomic, readonly) VLCMediaPlayerState mediaPlayerState;
@property (nonatomic, readonly) VLCMetaData *metadata;

@property (nonatomic, readonly) NSInteger mediaDuration;
@property (nonatomic, readonly) BOOL isPlaying;
@property (nonatomic, readwrite) VLCRepeatMode repeatMode;
@property (nonatomic, assign, getter=isShuffleMode) BOOL shuffleMode;
@property (nonatomic, readwrite) float playbackRate; // default = 1.0
@property (nonatomic, readwrite) float audioDelay; // in seconds, default = 0.0
@property (nonatomic, readwrite) float subtitleDelay; // in seconds, default = 0.0
@property (nonatomic, readonly) BOOL currentMediaHasChapters;
@property (nonatomic, readonly) BOOL currentMediaHasTrackToChooseFrom;
@property (nonatomic, readonly) BOOL activePlaybackSession;
@property (nonatomic, readwrite) BOOL fullscreenSessionRequested;
@property (nonatomic, readonly) NSDictionary *mediaOptionsDictionary;
@property (nonatomic, readonly) NSTimer* sleepTimer;

+ (VLCPlaybackController *)sharedInstance;

- (void)startPlayback;
- (void)stopPlayback;

- (void)playPause;
- (void)forward;
- (void)backward;
- (void)switchAspectRatio;
- (BOOL)updateViewpoint:(CGFloat)yaw pitch:(CGFloat)pitch roll:(CGFloat)roll fov:(CGFloat)fov absolute:(BOOL)absolute;
- (NSInteger)currentMediaProjection;
- (void)recoverDisplayedMetadata;
- (void)recoverPlaybackState;

- (void)setNeedsMetadataUpdate;
- (void)scheduleSleepTimerWithInterval:(NSTimeInterval)timeInterval;

- (void)playMediaList:(VLCMediaList *)mediaList firstIndex:(NSInteger)index subtitlesFilePath:(NSString *)subsFilePath;

@end
