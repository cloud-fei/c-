#include<stdio.h>
#include<curl/curl.h>

void MainWindow::on_pushButton_3_clicked()
{
    CURL* curl;
    CURLcode res;

    const char* filename = "httptest.txt";
    FILE* fs;

    if ((fs = fopen(filename, "w")) == NULL)  
            return;

    struct curl_slist *headers = NULL;
    headers = curl_slist_append(headers, "Accept: Agent-007");

    curl_global_init(CURL_GLOBAL_ALL);

    curl = curl_easy_init();
    if(curl){
//ftp
//        curl_easy_setopt(curl, CURLOPT_URL, "ftp://172.38.180.192");
//        curl_easy_setopt(curl, CURLOPT_USERPWD, "user001/123qwe......");

        //http
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);// 改协议头
        curl_easy_setopt(curl, CURLOPT_URL,"http://www.baidu.com");
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, fs); //将返回的http头输出到fp指向的文件
        curl_easy_setopt(curl, CURLOPT_HEADERDATA, fs); //将返回的html主体数据输出到fp指向的文件

        res = curl_easy_perform(curl);
        if(res != CURLE_OK){
            qDebug() << "Fail to curl URL!";
        }
        fclose(fs);
        curl_easy_cleanup(curl);

    }

    curl_global_cleanup();
    return;
}