// 代码中使用到的部分参数：
// cluster_name      (默认为ceph)
// user_name         (默认为client.admin)
// conf_read_file    (默认为/etc/ceph/ceph.conf)
// pool_name         (自己创建一个pool)
// object_name       (pool内的对象)

#include <rados/librados.hpp>
#include <string>
#include <list>
#include <iostream>

int main(int argc, const char **argv)
{
    int ret = 0;
    // Get cluster handle and connect to cluster
    std::cout << "===ceph Cluster connect begin===" << std::endl;
    std::string cluster_name("ceph");                 
    std::string user_name("client.admin");
    librados::Rados cluster;
    ret = cluster.init2(user_name.c_str(), cluster_name.c_str(), 0);
    if (ret < 0)
    {
        std::cerr << "Couldn't initialize the cluster handle! error " << ret << std::endl;
        ret = EXIT_FAILURE;
        return 1;
    }

    ret = cluster.conf_read_file("/etc/ceph/ceph.conf");
    if (ret < 0)
    {
        std::cerr << "Couldn't read the Ceph configuration file! error " << ret << std::endl;
        ret = EXIT_FAILURE;
        return 1;
    }

    ret = cluster.connect();
    if (ret < 0)
    {
        std::cerr << "Couldn't connect to cluster! error " << ret << std::endl;
        ret = EXIT_FAILURE;
        return 1;
    }


    librados::IoCtx io_ctx;
    std::string pool_name("your pool name");
    ret = cluster.ioctx_create(pool_name.c_str(), io_ctx);
    if (ret < 0)
    {
        std::cerr << "Couldn't set up ioctx! error " << ret << std::endl;
        exit(EXIT_FAILURE);
    }
    std::string object_name("your object name");
    //write to pool
    librados::bufferlist write_buf;
    std::string write_content = "Hello stranger";
    write_buf.append(write_content);
    ret = io_ctx.write_full(object_name, write_buf);
    if (ret < 0)
    {
        std::cerr << "Couldn't write object! error " << ret << std::endl;
        exit(EXIT_FAILURE);
    }
    std::cout << "===Write success.===" << std::endl; 


    //read from pool
    librados::bufferlist read_buf;
    int read_len = 4194304;
    librados::AioCompletion *read_completion = librados::Rados::aio_create_completion();
    io_ctx.aio_read(object_name, read_completion, &read_buf, read_len, 0);
    read_completion->wait_for_complete();
    read_completion->get_return_value();
    std::cout << read_buf.c_str() << std::endl;
    std::cout << "===read success===" << std::endl;


    io_ctx.close();
    cluster.shutdown();
    return 0;
}

// g++ -std=c++11 librados_test.cpp -o librados_test -lrados
// sh librados_test
// 结果会把自己写入pool内的数据读取出来并打印
//其余操作会陆续补充