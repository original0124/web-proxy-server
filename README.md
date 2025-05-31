# web-proxy-server
My web proxy server written in C

This is about Docker
docker pull original0124/web-proxy-server:latest
docker run -it --rm -p 9090:9090 -e PORT=9090 -e THREADS=4 original0124/web-proxy-server

  
The compilation method is as follows. Note that the my_cgi.c file should be compiled separately.  
```
gcc -c *.c -I.  
gcc -o my_server *.o -pthread  
```

  
An example of the execution method is as follows.  
```
screen -S mysession  
./my_server 9090 4  
Ctrl + A D   
screen -ls    
screen -r mysession   
```
