// shinglsAlg.cpp: определяет точку входа для консольного приложения.
//
#include "../headers/stdafx.h"
#include "../src/gsoap_autogenerated/shingle.nsmap"
#ifdef _WIN32_
    #include "../headers/targetver.h"
#endif
#include "../headers/ShingleApp.h"

using namespace DePlaguarism;
using namespace std;

int http_get(struct soap *soap);
void * runService(void *);


int main(int argc, char* argv[])
{
    pthread_t tid;
    setlocale(LC_ALL, "ru_RU.UTF-8");
    ShingleApp *srv = new ShingleApp();
    soap_set_imode(srv, SOAP_C_UTFSTRING);
    soap_set_omode(srv, SOAP_C_UTFSTRING);
    pthread_create(&tid, NULL, (void*(*)(void*))runService, (void*)srv);
    cout << "Application started!" << endl;
    string a;
    cin >> a;
    while (a != "exit")
        cin >> a;
    srv->stop();
    cout << "Application will be stopped then one more connection is accepted..." << endl;
    pthread_join(tid, NULL);
    delete srv;
    system("pause");
    return 0;
}

int http_get(struct soap *soap)
{
   FILE *fd = NULL;
   char *s = strchr(soap->path, '?');
   if (!s || strcmp(s, "?wsdl"))
      return SOAP_GET_METHOD;
   fd = fopen("shingle.wsdl", "rb"); // open WSDL file to copy
   if (!fd)
      return 404; // return HTTP not found error
   soap->http_content = "text/xml"; // HTTP header with text/xml content
   soap_response(soap, SOAP_FILE);
   for (;;)
   {
      size_t r = fread(soap->tmpbuf, 1, sizeof(soap->tmpbuf), fd);
      if (!r)
         break;
      if (soap_send_raw(soap, soap->tmpbuf, r))
         break; // can't send, but little we can do about that
   }
   fclose(fd);
   soap_end_send(soap);
   return SOAP_OK;
}


void * runService(void * app){
    ShingleApp * srv = (ShingleApp*)app;
    srv->fget = http_get;
    srv->log() << "Server putted up!\n" << srv->nowToStr() << '\n';
    srv->setMain();
    while (srv->run(SERVICE_PORT)){
        srv->log() << "Warning! Server is down \n" << "Server putted up!\n" << srv->nowToStr() << '\n';
    };
}
