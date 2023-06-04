#ifndef CTXDSTORE_H
#define CTXDSTORE_H

class CTxdSlot {
	int index;

public:
	CTxdSlot( const int &index );
	CTxdSlot( const char *name );
	CTxdSlot( const CTxdSlot &copy ) = delete;
	~CTxdSlot();

	int load( const char *name );
	void remove();
	void *addRef() const;
	void removeRef() const;
	int countRef() const;

	int getIndex() const;
};

class CTxdStore {
public:
	static void push();
	static void pop();
	static int setSlot( const CTxdSlot *slot );
	static int findSlotIndex( const char *name );
	static CTxdSlot *findSlot( const char *name );
	static void *rwTexture( const char *name, const char *maskName = nullptr );
};

#endif // CTXDSTORE_H
