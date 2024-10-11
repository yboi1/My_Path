package gee

import (
	"strings"
)

type node struct {
	pattern  string  // 匹配路由
	part     string  // 路由中的一部分
	children []*node // 子节点
	isWild   bool    // 是否精确匹配
}

func (n *node) matchChild(part string) *node {
	for _, child := range n.children {
		if child.part == part || n.isWild {
			return child
		}
	}
	return nil
}

func (n *node) matchChildren(part string) []*node {
	nodes := make([]*node, 0)
	for _, child := range n.children {
		if child.part == part || child.isWild {
			nodes = append(nodes, child)
		}
	}
	return nodes
}

// 每一层判断, 得到child 然后进行模糊判断 hello :name
func (n *node) insert(pattern string, parts []string, height int) {
	if len(parts) == height {
		n.pattern = pattern
		return
	}
	part := parts[height]
	child := n.matchChild(part)
	if child == nil {
		child = &node{part: part, isWild: part[0] == ':' || part[0] == '*'}
		n.children = append(n.children, child)
	}
	child.insert(pattern, parts, height+1)
}

/*
"/hello/:name"
{hello, 0},
{:name, 1}
*/

// hello boyi  0
func (n *node) search(parts []string, height int) *node {
	if len(parts) == height || strings.HasPrefix(n.part, "*") || n.isWild {
		if n.pattern == "" {
			return nil
		}
		return n
	}

	part := parts[height]
	children := n.matchChildren(part)

	for _, child := range children {

		result := child.search(parts, height+1)
		if result != nil {
			return result
		}
	}

	return nil
}
