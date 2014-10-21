#ifndef SQUID_SRC_BASE_LOCK_H
#define SQUID_SRC_BASE_LOCK_H

/**
 * This class provides a tracking counter and presents
 * lock(), unlock() and LockCount() accessors.
 *
 * All locks must be cleared with unlock() before this object
 * is destroyed.
 *
 * Accessors provided by this interface are not private,
 * to allow class hierarchies.
 *
 * Build with -DLOCKCOUNT_DEBUG flag to enable lock debugging.
 * It is disabled by default due to the cost of debug output.
 */
class Lock
{
public:
    Lock():count_(0) {}

    virtual ~Lock() { assert(count_ == 0); }

    /// Register one lock / reference against this object.
    /// All locks must be cleared before it may be destroyed.
    void lock() const {
#if defined(LOCKCOUNT_DEBUG)
        old_debug(0,1)("Incrementing this %p from count %u\n",this,count_);
#endif
        ++count_;
    }

    /// Clear one lock / reference against this object.
    /// All locks must be cleared before it may be destroyed.
    unsigned unlock() const {
#if defined(LOCKCOUNT_DEBUG)
        old_debug(0,1)("Decrementing this %p from count %u\n",this,count_);
#endif
        assert(count_ > 0);
        return --count_;
    }

    /// Inspect the current count of references.
    unsigned LockCount() const { return count_; }

private:
    mutable unsigned count_; ///< number of references currently being tracked
};

// For clarity we provide some aliases for the tracking mechanisms
// using Lock so that we can easily see what type of smart pointers
// are to be used for the child object.
// NP: CbcPointer<> and RefCount<> pointers should be used consistently
//     for any given child class type

/// The locking interface for use on Reference-Counted classes
#define RefCountable virtual Lock

#endif /* SQUID_SRC_BASE_LOCK_H */
