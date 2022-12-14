#include "ChatServer.h"
#include <fstream>
#include <string>
#include <sstream>
#include "Epoll.h"



ChatServer::ChatServer()
{
    if(loadConfig() == -1){
        cout << "加载配置文件失败！" << endl;
    }
}



int ChatServer::loadConfig()
{
        std::ifstream fin;
        std::stringstream content;
        fin.open("/home/ekko/chatServer/config/config.conf",ios::in);
        if (!fin.is_open())
        {
            std::cout << "Failed to open " << "config.conf" << std::endl;
          
        }
        content << fin.rdbuf();
        fin.close();
        string conf = content.str();
        if (conf.empty()){
            return -1;
        }
        
        int end;
        int begin;
        int strs_size;
        begin = conf.find("port =", 0);
        end = conf.find("\n", begin);
        strs_size = 6;
        std::stringstream stream;
        stream << conf.substr(begin + strs_size, end - begin - strs_size);
        stream >> m_usPort;

        // atoi(conf.substr(begin + strs_size, end - begin - strs_size).c_str());
        return 1;
}

int ChatServer::run()
{
    printf("创建套接字\n");
	int sockfd = socket(AF_INET, SOCK_STREAM, 0);
	struct sockaddr_in addr;
	memset(&addr, 0, sizeof(struct sockaddr_in));
	addr.sin_family = AF_INET;
	addr.sin_port = htons(m_usPort);
	addr.sin_addr.s_addr = INADDR_ANY;
     printf("绑定套接字\n");
	if (bind(sockfd, (struct sockaddr*)&addr, sizeof(struct sockaddr_in)) < 0) {
		perror("bind");
		return 2;
	}
	if (listen(sockfd, 5) < 0) {
		perror("listen");
		return 3;
	}
    Epoll *ep = new Epoll(sockfd);
    ep->run();
    return 0;
}
