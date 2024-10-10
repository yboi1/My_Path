package geecache

// 根据key选择对应的节点
type PeerPicker interface {
	PickPeer(key string) (peer PeerGetter, ok bool)
}

// 从对应的group缓存中读取key值
type PeerGetter interface {
	Get(group string, key string) ([]byte, error)
}
