// Contact Tracing Framework
// Preliminary - Subject to Modification and Extension
// Interface derived from documentation (retrieved 2020-04-10)
// https://www.apple.com/covid19/contacttracing
//
// Information subject to copyright.
// All rights reserved.

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

#pragma mark - CTStateGetRequest

/// The type definition for the completion handler.
typedef void (^CTErrorHandler) (NSError * _Nullable inError);

/// Requests whether contact tracing is on or off on the device.
@interface CTStateGetRequest : NSObject

/// This property holds the completion handler that framework invokes when the request completes. The property is cleared upon completion to break any potential retain cycles.
@property (nullable, copy) CTErrorHandler completionHandler;

/// This property holds the the dispatch queue used to invoke handlers on. If this property isn't set, the framework uses the main queue.
@property (nullable) dispatch_queue_t dispatchQueue;

/// This property contains the snapshot of the state when the request was performed. It's valid only after the framework invokes the completion handler.
@property (readonly) CTManagerState state;

/// Asynchronously performs the request to get the state, and invokes the completion handler when it's done.
- (void) perform;

/// Invalidates a previously initiated request. If there is an outstanding completion handler, the framework will invoke it with an error.
/// Don't reuse the request after this is called. If you require another request, create a new one.
- (void) invalidate;

@end

#pragma mark - CTStateSetRequest

/// Changes the state of contact tracing on the device.
@interface CTStateSetRequest : NSObject

/// This property holds the completion handler that framework invokes when the request completes. The property is cleared upon completion to break any potential retain cycles.
@property (nullable, copy) CTErrorHandler completionHandler;

/// This property holds the the dispatch queue used to invoke handlers on. If this property isn't set, the framework uses the main queue.
@property (nullable) dispatch_queue_t dispatchQueue;

/// This property contains the state to set Contact Tracing to. Call the perform method to apply the state once set.
@property (readwrite) CTManagerState state;

/// Asynchronously performs the request to get the state, and invokes the completion handler when it's done.
- (void) perform;

/// Invalidates a previously initiated request. If there is an outstanding completion handler, the framework will invoke it with an error.
/// 
/// Don't reuse the request after this is called. If you require another request, create a new one.
- (void) invalidate;

@end

#pragma mark - CTExposureDetectionSession

/// The type definition for the completion handler.
typedef void (^CTExposureDetectionFinishHandler) (CTExposureDetectionSummary * _Nullable inSummary, NSError * _Nullable inError);

/// The type definition for the completion handler.
typedef void ( ^CTExposureDetectionContactHandler )( NSArray <CTContactInfo *> * _Nullable inContacts, NSError * _Nullable inError );

/// Performs exposure detection bad on previously collected proximity data and keys.
@interface CTExposureDetectionSession : NSObject

/// This property holds the the dispatch queue used to invoke handlers on. If this property isn't set, the framework uses the main queue.
@property dispatch_queue_t dispatchQueue;

/// This property contains the maximum number of keys to provide to this API at once. This property's value updates after each operation complete and before the completion handler is invoked. Use this property to throttle key downloads to avoid excessive buffering of keys in memory.
@property (readonly, nonatomic) NSInteger maxKeyCount;

/// Activates the session and requests authorization for the app with the user. Properties and methods cannot be used until this completes successfully.
- (void) activateWithCompletion:(nullable CTErrorHandler) inCompletion;

/// Invalidates the session. Any outstanding completion handlers will be invoked with an error. The session cannot be used after this is called. A new session must be created if another detection is needed.
- (void) invalidate;

/// Asynchronously adds the specified keys to the session to allow them to be checked for exposure. Each call to this method must include more keys than specified by the current value of <maxKeyCount>.
- (void) addPositiveDiagnosisKeys:(NSArray <CTDailyTracingKey *> *) inKeys completion:(nullable CTErrorHandler) inCompletion;

/// Indicates all of the available keys have been provided. Any remaining detection will be performed and the completion handler will be invoked with the results.
- (void) finishedPositiveDiagnosisKeysWithCompletion:(nullable CTExposureDetectionFinishHandler) inFinishHandler;

/// Obtains information on each incident. This can only be called once the detector finishes. The handler may be invoked multiple times. An empty array indicates the final invocation of the hander.
- (void) getContactInfoWithHandler:(nullable CTExposureDetectionContactHandler) inHandler;

@end

#pragma mark - CTExposureDetectionSummary

/// Provides a summary on exposures.
@interface CTExposureDetectionSummary : NSObject

/// This property holds the number of keys that matched for an exposure detection.
@property (readonly) NSInteger matchedKeyCount;

@end

#pragma mark - CTSelfTracingInfoRequest

/// The type definition for the completion handler.
typedef void ( ^CTSelfTracingInfoGetCompletion ) ( CTSelfTracingInfo * _Nullable inInfo, NSError * _Nullable inError );

/// Requests the daily tracing keys used by this device to share with a server.
@interface CTSelfTracingInfoRequest : NSObject

/// This property invokes this completion handler when the request completes and clears the property to break any potential retain cycles.
@property (nullable, copy) CTSelfTracingInfoGetCompletion completionHandler;

/// This property holds the the dispatch queue used to invoke handlers on. If this property isn't set, the framework uses the main queue.
@property (nullable) dispatch_queue_t dispatchQueue;

/// Asynchronously performs the request to get the state, and invokes the completion handler when it's done.
- (void) perform;

/// Invalidates a previously initiated request. If there is an outstanding completion handler, the framework will invoke it with an error.
///
/// Don't reuse the request after this is called. If you require another request, create a new one.
- (void) invalidate;

@end

#pragma mark - CTSelfTracingInfo

/// Contains the Daily Tracing Keys.
@interface CTSelfTracingInfo : NSObject

/// Daily tracing keys available at the time of the request.
@property (readonly, copy) NSArray <CTDailyTracingKey *> * dailyTracingKeys;

@end

#pragma mark - CTContactInfo

/// Contains information about a single contact incident.
@interface CTContactInfo : NSObject

/// How long the contact was in proximity. Minimum duration is 5 minutes and increments by 5 minutes: 5, 10, 15, etc.
@property (readonly) NSTimeInterval duration;

/// This property contains the time when the contact occurred. This may have reduced precision, such as within one day of the actual time.
@property (readonly) CFAbsoluteTime timestamp;

@end

#pragma mark - CTDailyTracingKey

/// The Daily Tracing Key object.
@interface CTDailyTracingKey : NSObject

/// This property contains the Daily Tracing Key information.
@property (readonly, copy) NSData *keyData;

@end

NS_ASSUME_NONNULL_END
