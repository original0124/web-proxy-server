# web-proxy-server
My web proxy server written in C

This is about Docker  
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
and, an example of creating a custom HTML file is  
```
cat > /app/index.html <<EOF
```
Finally  
```
Ctrl + P Q  
```
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
Now，you can access your content in the browser.  

```
http://"ip or domain name"/index.html
```


NFS : Network File System to share directories from a remote host for resource synchronization and load balancing.  

The server-side configuration is as follows  

```
yum install -y rpcbind nfs-utils   
```

```
systemctl start rpcbind  
systemctl enable rpcbind  
```

```
rpcinfo -p  
```

```
systemctl start nfs-server
systemctl enable nfs-server
```

```
echo '/data/ <IP>(rw)   #In the configuration file, <IP> is granted read and write access to the /data/ directory on the server.' >> /etc/exports
```

```
systemctl reload nfs-server  #Reload the configuration file  
```

```
mkdir /data #Create a network-shared directory
cat /etc/passwd #Find the user automatically created by NFS, usually is "nobody"
```

```
id nobody #View user identity information  
```

```
chown -R nobody.nobody /data  
```

The client configuration is as follows  

```
yum install nfs-utils  
```

```
showmount -e <server IP> #View the shared directories on the server  
```

```
mount -t nfs <server IP>:/data/ /mnt/ #Temporarily mount the server’s /data/ directory to local /mnt/  
```

You might encounter some troublesome issue ， you can use tcpdump to capture packets in the background and append the output to a .pcap file.    

```
tcpdump not port 22 or not port 80 >> nfs.pcap &      #Filter SSH and HTTP traffic  
```

After that, you can transfer the .pcap file to Windows using SCP, open it with Wireshark, and analyze the captured traffic to locate the cause of the issue.  


```
scp root@<server IP>:/your/path/nfs.pcap "D:/your/path"
```
