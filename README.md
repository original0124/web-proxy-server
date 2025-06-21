# web-proxy-server
```  
docker pull original0124/web-proxy-server:latest  
```
```  
docker run -it --rm -p 9090:9090 -e PORT=9090 -e THREADS=4 original0124/web-proxy-server &  
```
```
docker ps  
```
```
docker exec -it "docker ID or name" sh &  
```
```
cat > /app/index.html <<EOF
``` 
```
Ctrl + P Q  
```
```
gcc -c *.c -I.  
gcc -o my_server *.o -pthread  
```
docker:  
docker pull  
docker push  
docker bulid  
docker save -o  
docker load -i  
docker run  
docker images  
docker-compose up  
docker-compose down  
docker login  
docker tag  
docker ps  
docker stop  
docker rmi  
docker exec -it 容器ID或名字 sh  
```
screen -S mysession  
./my_server 9090 4  
Ctrl + A D   
screen -ls    
screen -r mysession   
```
```
http://"ip or domain name"/index.html
```








You might encounter some troublesome issue ， you can use tcpdump to capture packets in the background and append the output to a .pcap file.    

```
tcpdump not port 22 or not port 80 >> nfs.pcap &      #Filter SSH and HTTP traffic  
```

After that, you can transfer the .pcap file to Windows using SCP, open it with Wireshark, and analyze the captured traffic to locate the cause of the issue.  


```
scp root@<server IP>:/your/path/nfs.pcap "D:/your/path"
```
View mount point information  
```
df -h
```  

tcpdump not port 22 or not port 80 >> nfs.pcap  
mount -t nfs 14.103.226.23:/data/ /mnt/  
防火墙的原因  
开启2049端口  
