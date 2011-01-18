#ifndef __FAILOVER_HPP__
#define __FAILOVER_HPP__

#include "containers/intrusive_list.hpp"

/* base class for failover callbacks */
class failover_callback_t : 
    public intrusive_list_node_t<failover_callback_t>
{
public:
    virtual ~failover_callback_t() {}
    virtual void on_failure() = 0;
};

/* failover callback to execute an external script */
class failover_script_callback_t :
    public failover_callback_t
{
public:
    failover_script_callback_t(const char *);
    ~failover_script_callback_t();
    void on_failure();
private:
    char *script_path;
};

struct Failover_t {
public:
    Failover_t() {}
    ~Failover_t() {}

private:
    intrusive_list_t<failover_callback_t> callbacks;
    void add_callback(failover_callback_t *cb);
    void on_failure();
};

#endif  // __FAILOVER_HPP__