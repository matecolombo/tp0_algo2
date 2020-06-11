#ifndef NODE_INCLUDED
#define NODE_INCLUDED

#ifndef NULL
#define NULL 0
#endif

template <class T>
class node
{
private:
	T info;
	node<T> * next;

public:
	node(){info = 0; next = NULL;};
	node(T x){info = x; next = NULL;};
	node(T x, node<T> * p): info(x), next(p){}; 		//Argumento por defecto, por defoult arranca desde el ultimo.
	node(const node<T> & n){info = n.info; next = n.next;};
	void setInfo(T x){info = x;};
	void setNext(node<T> * n){next = n;};
	T getInfo(){return info;};
	node<T> * getNext(){return next;};
	void emit(){std::cout << info << "-> ";};
};

#endif //NODE_INCLUDED

