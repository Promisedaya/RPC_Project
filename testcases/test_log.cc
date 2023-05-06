#include "/home/pjt/WORKSPACE/RPC_Project/rocket/common/log.h"
#include <pthread.h>
#include "/home/pjt/WORKSPACE/RPC_Project/rocket/common/config.h"

void *fun(void *)
{
    DEBUGLOG("debug this is thread in %s \n", "fun");
    INFOLOG("info this is thread in %s \n", "fun");
    return NULL;
}

int main()
{
    rocket::Config::SetGlobalConfig("../conf/rocket.xml");

    pthread_t thread;
    pthread_create(&thread, NULL, &fun, NULL);

    DEBUGLOG("test debug log %s", "11");
    INFOLOG("test info log %s", "11");
    return 0;
}