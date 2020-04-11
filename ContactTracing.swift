// Contact Tracing Framework
// Preliminary - Subject to Modification and Extension
// Interface derived from documentation (retrieved 2020-04-10)
// https://www.apple.com/covid19/contacttracing
//
// Information subject to copyright.
// All rights reserved.

import Foundation

/// The type definition for the completion handler.
public typealias CTErrorHandler = (Error?) -> Void

/// Requests whether contact tracing is on or off on the device.
open class CTStateGetRequest : NSObject {


    /// This property holds the completion handler that framework invokes when the request completes. The property is cleared upon completion to break any potential retain cycles.
    open var completionHandler: CTErrorHandler?


    /// This property holds the the dispatch queue used to invoke handlers on. If this property isn't set, the framework uses the main queue.
    open var dispatchQueue: DispatchQueue?


    /// This property contains the snapshot of the state when the request was performed. It's valid only after the framework invokes the completion handler.
    open var state: Int32 { get }


    /// Asynchronously performs the request to get the state, and invokes the completion handler when it's done.
    open func perform()


    /// Invalidates a previously initiated request. If there is an outstanding completion handler, the framework will invoke it with an error.
    /// Don't reuse the request after this is called. If you require another request, create a new one.
    open func invalidate()
}

/// Changes the state of contact tracing on the device.
open class CTStateSetRequest : NSObject {


    /// This property holds the completion handler that framework invokes when the request completes. The property is cleared upon completion to break any potential retain cycles.
    open var completionHandler: CTErrorHandler?


    /// This property holds the the dispatch queue used to invoke handlers on. If this property isn't set, the framework uses the main queue.
    open var dispatchQueue: DispatchQueue?


    /// This property contains the state to set Contact Tracing to. Call the perform method to apply the state once set.
    open var state: Int32


    /// Asynchronously performs the request to get the state, and invokes the completion handler when it's done.
    open func perform()


    /// Invalidates a previously initiated request. If there is an outstanding completion handler, the framework will invoke it with an error.
    ///
    /// Don't reuse the request after this is called. If you require another request, create a new one.
    open func invalidate()
}

/// The type definition for the completion handler.
public typealias CTExposureDetectionFinishHandler = (UnsafeMutablePointer<Int32>?, Error?) -> Void

/// The type definition for the completion handler.
public typealias CTExposureDetectionContactHandler = ([Any]?, Error?) -> Void

/// Performs exposure detection bad on previously collected proximity data and keys.
open class CTExposureDetectionSession : NSObject {


    /// This property holds the the dispatch queue used to invoke handlers on. If this property isn't set, the framework uses the main queue.
    open var dispatchQueue: DispatchQueue


    /// This property contains the maximum number of keys to provide to this API at once. This property's value updates after each operation complete and before the completion handler is invoked. Use this property to throttle key downloads to avoid excessive buffering of keys in memory.
    open var maxKeyCount: Int { get }


    /// Activates the session and requests authorization for the app with the user. Properties and methods cannot be used until this completes successfully.
    open func activate(completion inCompletion: CTErrorHandler? = nil)


    /// Invalidates the session. Any outstanding completion handlers will be invoked with an error. The session cannot be used after this is called. A new session must be created if another detection is needed.
    open func invalidate()


    /// Asynchronously adds the specified keys to the session to allow them to be checked for exposure. Each call to this method must include more keys than specified by the current value of <maxKeyCount>.
    open func addPositiveDiagnosisKeys(_ inKeys: [Any], completion inCompletion: CTErrorHandler? = nil)


    /// Indicates all of the available keys have been provided. Any remaining detection will be performed and the completion handler will be invoked with the results.
    open func finishedPositiveDiagnosisKeys(completion inFinishHandler: CTExposureDetectionFinishHandler? = nil)


    /// Obtains information on each incident. This can only be called once the detector finishes. The handler may be invoked multiple times. An empty array indicates the final invocation of the hander.
    open func getContactInfo(handler inHandler: CTExposureDetectionContactHandler? = nil)
}

/// Provides a summary on exposures.
open class CTExposureDetectionSummary : NSObject {


    /// This property holds the number of keys that matched for an exposure detection.
    open var matchedKeyCount: Int { get }
}

/// The type definition for the completion handler.
public typealias CTSelfTracingInfoGetCompletion = (UnsafeMutablePointer<Int32>?, Error?) -> Void

/// Requests the daily tracing keys used by this device to share with a server.
open class CTSelfTracingInfoRequest : NSObject {


    /// This property invokes this completion handler when the request completes and clears the property to break any potential retain cycles.
    open var completionHandler: CTSelfTracingInfoGetCompletion?


    /// This property holds the the dispatch queue used to invoke handlers on. If this property isn't set, the framework uses the main queue.
    open var dispatchQueue: DispatchQueue?


    /// Asynchronously performs the request to get the state, and invokes the completion handler when it's done.
    open func perform()


    /// Invalidates a previously initiated request. If there is an outstanding completion handler, the framework will invoke it with an error.
    ///
    /// Don't reuse the request after this is called. If you require another request, create a new one.
    open func invalidate()
}

/// Contains the Daily Tracing Keys.
open class CTSelfTracingInfo : NSObject {


    /// Daily tracing keys available at the time of the request.
    open var dailyTracingKeys: [Any] { get }
}

/// Contains information about a single contact incident.
open class CTContactInfo : NSObject {


    /// How long the contact was in proximity. Minimum duration is 5 minutes and increments by 5 minutes: 5, 10, 15, etc.
    open var duration: TimeInterval { get }


    /// This property contains the time when the contact occurred. This may have reduced precision, such as within one day of the actual time.
    open var timestamp: CFAbsoluteTime { get }
}

/// The Daily Tracing Key object.
open class CTDailyTracingKey : NSObject {


    /// This property contains the Daily Tracing Key information.
    open var keyData: Data { get }
}
