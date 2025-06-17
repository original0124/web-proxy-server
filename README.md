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
View mount point information  
```
df -h
```  
存储服务：NFS（Network File System）  
yum install -y rpcbind nfs-utils  
systemctl start rpcbind  
systemctl enable rpcbind  
 rpcinfo -p  
systemctl start nfs / nfs-server  
systemctl enable nfs / nfs-server  
NFS    服务端配置:  
vim /etc/exports  
/data/ <IP>(rw)   //47.237.5.147对服务端的/data/目录拥有读写权限  
/data/ <IP>(rw)  
systemctl reload nfs / nfs-server      //重新加载配置文件  
(reload : 优雅重启，不会断开已有连接)  
(resatrt:会立即断开已有连接，在nfs中会导致客户端一段时间夯住90s)  
cd /  
mkdir /data  
cat /etc/passwd 查看系统中所有的用户  
id nobody //安装nfs自动生成的用户  
chown -R nobody.nobody /data //更改/data及其子目录的所有者和所属组  
df -h /查看挂载点  
本地测试：mount -t nfs 14.103.226.23:/data/ /mnt/  
rpcinfo -p //查看nfs服务端的rpc信息  
showmount -e  //查看nfs的远程目录有哪些  
客户端：  
yum install nfs-utils  
tcpdump not port 22 or not port 80 >> nfs.pcap  
mount -t nfs 14.103.226.23:/data/ /mnt/  
防火墙的原因  
开启2049端口  

systemctl cat nfs-server //查看与服务相关的配置文件  
/var/lib/nfs/etab  //服务端完整的配置文件  
grep '/mnt' /proc/mounts  //客户端完整配置文件  
客户端永久挂载  
方法一：挂载命令写入到/etc/rc.local  
chmod +x /etc/rc.d/rc.local  
方法二：按照/etc/fstab格式要求书写  
设备   挂载点   文件系统类型   挂载参数  是否检查  是否备份  
14.103.226.23:/data/ /data nfs defaults 0 0  
服务端配置文件权限配置  
rw（读写）ro(只读)sync(同步，只要客户端上传，就把数据写到磁盘上)async(异步，客户端上传数据，nfs先临时存放在内存或各种缓存中，过一段时间写入到磁盘，并发高，数据可能丢  失)  
#NFS客户端挂载NFS服务端后，客户端root用户创建的文件在服务器端默认属于nobody(root_squash)，这叫做用户映射，也可以对所有用户进行映射(all_squash)，也可以不进行用户映射(no_all_squash)  
用户映射用于解决客户端和服务器上的不同用户所拥有的权限不同的问题  
 
