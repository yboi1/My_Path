### select的使用方法

> int select(int nfds, fd_set *readfds, fd_set *writefds,
>                   fd_set *exceptfds, struct timeval *timeout);

> nfd:最大文件描述符加一
>
> redfds：监听读的文件描述符组
>
> timeout：最大等待时间

```
fd_set rdset;
FD_ZERO(&rdset);
FD_SET(sockfd,&rdset)  sockfd:文件描述符
```

