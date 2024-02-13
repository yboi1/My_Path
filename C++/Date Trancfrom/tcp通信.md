## tcp通信

#### Socket客户端

##### Init

```
1.socket(AF_INET,SO_STREAM,0);
2.setsockopt(m_Mfd,SOL_SOCKET,SO_REUSEADDR,&size_t,sizeof(size_t));
3.bind(m_Mfd,&servaddr,sizeof(servaddr));
4.listen(m_Mfd,SOMAXCONN)
```

