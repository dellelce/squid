#ifndef _SQUID_AUTH_BASIC_USER_H
#define _SQUID_AUTH_BASIC_USER_H

#include "auth/User.h"
#include "auth/UserRequest.h"

namespace Auth
{

class Config;
class QueueNode;

namespace Basic
{

/** User credentials for the Basic authentication protocol */
class User : public Auth::User
{
public:
    MEMPROXY_CLASS(Auth::Basic::User);

    User(Auth::Config *);
    ~User();
    bool authenticated() const;
    bool valid() const;

    /** Update the cached password for a username. */
    void updateCached(User *from);
    virtual int32_t ttl() const;

    char *passwd;

    QueueNode *queue;

private:
    Auth::UserRequest::Pointer currentRequest;
};

MEMPROXY_CLASS_INLINE(Auth::Basic::User);

} // namespace Basic
} // namespace Auth

#endif /* _SQUID_AUTH_BASIC_USER_H */
