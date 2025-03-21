#ifndef MemoryManager_H
#define MemoryManager_H

class MemoryManagerImpl;

class MemoryManager {
public:
  MemoryManager();
  ~MemoryManager();
 
  // this one is easy. call the methods of MemoryManagerImpl...
  void read(); 
  void insert();
  void update();
  void del(); //delete is a keyword...
  void dump();

private:
  MemoryManagerImpl* impl;
};
#endif // !MemoryManager
