#include "IServer.h"
#include "ParallelServer.h"
#include "FileCacheManager.h"
#include "MyClientHandler.h"
#include "ISearcher.h"
#include "BestFS.h"
#include "Astar.h"

using namespace server_side;

int main(int argc, char **argv) {
    int port = atoi(argv[1]);
    IServer *server = new ParallelServer();
    ICacheManager<string, string> *cache = new FileCacheManager<string, string>();
    IClientHandler *handler = new MyClientHandler(cache);
    server->start(port, handler);
    return 0;
}
